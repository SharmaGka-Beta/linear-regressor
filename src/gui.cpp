#include "gui.h"
#include "trainer.h"
#include "model.h"
#include "optimizer.h"
#include "loss.h"
#include "dataset.h"
#include "scaler.h"
#include "exceptions.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>
#include <ImGuiFileDialog.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

void Gui::run(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML - Linear Regressor");

    (void)ImGui::SFML::Init(window);
    ImPlot::CreateContext();

    window.setFramerateLimit(60);

    sf::Clock deltaClock;

    while(window.isOpen()){

        while(const auto event = window.pollEvent()){

            ImGui::SFML::ProcessEvent(window, *event);
            if (event -> is <sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>()){
                sf::FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
                window.setView(sf::View(visibleArea));
            }
        }

        ImGui::SFML::Update(
            window,
            deltaClock.restart()
        );

        renderState();

        window.clear();

        ImGui::SFML::Render(window);

        window.display();
    }
    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();
}

void Gui::renderState(){

    if (state == GuiState::FileLoading){
        loadFile();
    }
    else if(state == GuiState::TargetSelection){
        selectTarget();
    }
    else if(state == GuiState::Ready){
        ready();
    }
    else if(state == GuiState::Training){
        training();
    }
    else if(state == GuiState::Prediction){
        prediction();
    }
}

void Gui::loadFile(){

    ImGui::Begin("Choose File");
    if(ImGui::Button("Load CSV")){

        IGFD::FileDialogConfig config;
        config.path = ".";

        ImGuiFileDialog::Instance()->OpenDialog(
            "ChooseCSV",
            "Choose CSV File",
            ".csv",
            config
        );
    }
    if (showExcep){
        ImGui::Text("%s", excMessage.c_str());
    }
    if (ImGuiFileDialog::Instance()->Display("ChooseCSV")){
        if (!(ImGuiFileDialog::Instance()->IsOk())){

            ImGuiFileDialog::Instance()->Close();
            ImGui::End();
            return;

        }

        fileName = ImGuiFileDialog::Instance()->GetFilePathName();
        ImGuiFileDialog::Instance()->Close();

        try{
            dataset = make_unique<Dataset>(fileName);

            if ((dataset -> getHeaders()).size() > 0){
                showExcep = false;
                state = GuiState::TargetSelection;
            }
            else{
                targetColumn = dataset -> getColumnCount() - 1;
                X = dataset -> getFeatures(targetColumn);
                Y = dataset -> getTargets(targetColumn);
                for(auto const& row: X){
                    plotX.push_back(row[0]);
                }
                showExcep = false;
                state = GuiState::Ready;
            }
        }
        catch(const CustomException& exc){
            showExcep = true;
            excMessage = exc.what();
        }
    }
    ImGui::End();
}

void Gui::selectTarget(){
    vector<string>& headers = dataset -> getHeaders();


    ImGui::Begin("Select Target");

    if (ImGui::BeginCombo("Target", headers[targetColumn].c_str())){
        for(int i = 0; i < (int)headers.size(); i++){

            bool isSelected = (i == targetColumn);

            if (ImGui::Selectable(headers[i].c_str(), isSelected)) {
                targetColumn = i;
            }

            if(isSelected){
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if(ImGui::Button("Ok")){
        X = dataset -> getFeatures(targetColumn);
        Y = dataset -> getTargets(targetColumn);
        for(auto const& row: X){
            plotX.push_back(row[0]);
        }
        state = GuiState::Ready;
    }

    if (ImGui::Button("Restart")){
        ImGui::End();
        clearAll();
        return;
    }
    ImGui::End();
}

void Gui::ready(){

    ImGui::Begin("Ready");

    ImGui::InputInt("Epochs", &epochs);
    ImGui::InputDouble("Learning Rate", &learningRate);


    if (ImGui::BeginCombo("Loss", losses[selectedLoss].c_str())){
        for(int i = 0; i < (int)losses.size(); i++){

            bool isSelected = (i == selectedLoss);

            if (ImGui::Selectable(losses[i].c_str(), isSelected)) {
                selectedLoss = i;
            }

            if(isSelected){
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if (ImGui::BeginCombo("Optimizer", optimizers[selectedOptimizer].c_str())){
        for(int i = 0; i < (int)optimizers.size(); i++){

            bool isSelected = (i == selectedOptimizer);

            if (ImGui::Selectable(optimizers[i].c_str(), isSelected)) {
                selectedOptimizer = i;
            }

            if(isSelected){
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if (showExcep){
        ImGui::Text("%s", excMessage.c_str());
    }

    if(ImGui::Button("Start Training")){

        scalerX = make_unique<Scaler>();
        scalerY = make_unique<Scaler>();
        model = make_unique<Model>((int)X[0].size());

        if (losses[selectedLoss] == "MSE"){
            loss = make_unique<MSELoss>();
        }
        else if(losses[selectedLoss] == "MAE"){
            loss = make_unique<MAELoss>();
        }
        else if(losses[selectedLoss] == "Huber"){
            loss = make_unique<HuberLoss>();
        }
        if (optimizers[selectedOptimizer] == "SGD"){
            optimizer = make_unique<SGDOptimizer>(learningRate);
        }
        trainer = make_unique<Trainer>(*model, *loss, *optimizer);

        try{

            scalerX -> fit(X);
            scalerY -> fit(Y);
            
            scaledX = scalerX -> transform(X);
            scaledY = scalerY -> transform(Y);
            currentEpoch = 0;
            currentLoss = 0;
            showExcep = false;
            excMessage.clear();

            state = GuiState::Training;
            
        }
        catch(const CustomException& excep){
            showExcep = true;
            excMessage = excep.what();
            
        }

    }

    if (ImGui::Button("Restart")){
        ImGui::End();
        clearAll();
        return;
    }

    if(dataset -> getColumnCount() == 2){

        if (ImPlot::BeginPlot("Dataset")){
            ImPlot::PlotScatter(
                "Data",
                plotX.data(),
                Y.data(),
                static_cast<int>(Y.size())
            );

            ImPlot::EndPlot();
        }
    }
    else{
        ImGui::Text("Plot available only for 2D regression :(");
    }
    ImGui::End();
}

void Gui::training(){

    ImGui::Begin("Training");

    if (currentEpoch < epochs){

        currentLoss = trainer -> trainOneEpoch(scaledX, scaledY);
        currentEpoch++;
    }

    ImGui::Text("Epoch: %d / %d", currentEpoch, epochs);
    ImGui::Text("Loss: %.6f", currentLoss);

    vector <double> predictions = model -> predict(scaledX);
    vector <double> real = scalerY -> invert(predictions);

    if (ImGui::Button("Restart")){
        ImGui::End();
        clearAll();
        return;
    }

    if (dataset -> getColumnCount() == 2){
        if (ImPlot::BeginPlot("Regression")){

            ImPlot::PlotScatter(
                "Data",
                plotX.data(),
                Y.data(),
                static_cast<int>(plotX.size())
            );

            ImPlot::PlotLine(
                "Regression",
                plotX.data(),
                real.data(),
                static_cast<int>(plotX.size())
            );
            

            ImPlot::EndPlot();
        }
    }
    else{
        ImGui::Text("Plot available only for 2D regression :(");
    }


    ImGui::End();

    if(currentEpoch >= epochs){

        inputs = vector<vector<double>>(1, vector<double>(X[0].size(), 0.0));

        vector <double> weights = model -> getWeights();
        double bias = model -> getBias();

        const vector<double>& meanX = scalerX -> getMean();
        double meanY = (scalerY -> getMean())[0];

        const vector<double>& sigmaX = scalerX -> getSigma();
        double sigmaY = (scalerY -> getSigma())[0];

        finalWeights.resize(weights.size());

        for (int i = 0; i < (int)weights.size(); i++){
            finalWeights[i] = weights[i] * sigmaY / sigmaX[i];
        }

        finalBias = meanY + sigmaY * bias;
        for (int i = 0; i < static_cast<int>(finalWeights.size()); ++i){
            finalBias -= finalWeights[i] * meanX[i];
        }


        state = GuiState::Prediction;
    }
}

void Gui::prediction(){
    
    ImGui::Begin("Predictions");
    vector <string> headers = dataset -> getHeaders();

    ImGui::Text("Loss: %f", currentLoss);

    ImGui::Text("%s = ", headers[targetColumn].c_str());

    ImGui::SameLine();

    int index = 0;
    for(int i = 0; i < (int)headers.size(); i++){
        if (i == targetColumn){
            continue;
        }
        ImGui::Text("(%f * %s) + ", finalWeights[index], headers[i].c_str());
        ImGui::SameLine();
        index++;
    }

    ImGui::Text("(%f)", finalBias);
    
    index = 0;

    for(int i = 0; i < (int)headers.size(); i++){
        if (i == targetColumn){
            continue;
        }
        ImGui::InputDouble(headers[i].c_str(), &inputs[0][index]);
        index++;
    }

    if(showPreds){
        vector <string> headers = dataset -> getHeaders();
        ImGui::Text("%s: %f", headers[targetColumn].c_str(), preds[0]);
    }

    if (ImGui::Button("Predict")){

        vector<vector<double>> scaledInputs = (*scalerX).transform(inputs);
        vector<double> scaledPred = (*model).predict(scaledInputs);
        preds = (*scalerY).invert(scaledPred);
        showPreds = true;
    
    }

    if (ImGui::Button("Restart")){
        ImGui::End();
        clearAll();
        return;
    }
    if (dataset -> getColumnCount() == 2){

        vector <double> predictions = model -> predict(scaledX);
        vector <double> real = scalerY -> invert(predictions);

        if (ImPlot::BeginPlot("Regression")){

            ImPlot::PlotScatter(
                "Data",
                plotX.data(),
                Y.data(),
                static_cast<int>(plotX.size())
            );

            ImPlot::PlotLine(
                "Regression",
                plotX.data(),
                real.data(),
                static_cast<int>(plotX.size())
            );
            

            ImPlot::EndPlot();
        }
    }
    else{
        ImGui::Text("Plot available only for 2D regression :(");
    }

    ImGui::End();
}

void Gui::clearAll(){

    state = GuiState::FileLoading;
    fileName.clear();
    targetColumn = 0;
    currentEpoch = 0;
    currentLoss = 0;
    epochs = 100;
    learningRate = 0.01;
    showPreds = false;
    selectedLoss = 0;
    selectedOptimizer = 0;
    showExcep = false;
    excMessage.clear();

    X.clear();
    Y.clear();
    scaledX.clear();
    scaledY.clear();
    plotX.clear();
    inputs.clear();
    preds.clear();

    finalWeights.clear();
    finalBias = 0;

    dataset.reset();
    scalerX.reset();
    scalerY.reset();
    model.reset();
    loss.reset();
    optimizer.reset();
    trainer.reset();
}

