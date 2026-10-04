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
    ImGui::End();

    if (ImGuiFileDialog::Instance()->Display("ChooseCSV")){
        if (!(ImGuiFileDialog::Instance()->IsOk())){

            ImGuiFileDialog::Instance()->Close();
            return;

        }

        fileName = ImGuiFileDialog::Instance()->GetFilePathName();
        ImGuiFileDialog::Instance()->Close();

        try{
            dataset = make_unique<Dataset>(fileName);

            if (dataset -> hasHeaders(fileName)){
                state = GuiState::TargetSelection;
            }
            else{
                targetColumn = dataset -> getColumnCount() - 1;
                X = dataset -> getFeatures(targetColumn);
                Y = dataset -> getTargets(targetColumn);
                for(auto const& row: X){
                    plotX.push_back(row[0]);
                }
                state = GuiState::Ready;
            }
        }
        catch(const CustomException& exc){
            cout << exc.what() << endl;
        }
    }
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
    ImGui::End();
}

void Gui::ready(){

    ImGui::Begin("Ready");

    ImGui::InputInt("Epochs", &epochs);
    ImGui::InputDouble("Learning Rate", &learningRate);

    int selectedLoss = 0;
    int selectedOptimizer = 0;

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

    if(ImGui::Button("Start Training")){

        scalerX = make_unique<Scaler>();
        scalerY = make_unique<Scaler>();
        model = make_unique<Model>((int)X[0].size());

        if (losses[selectedLoss] == "MSE"){
            loss = make_unique<MSELoss>();
        }
        if (optimizers[selectedOptimizer] == "SGD"){
            optimizer = make_unique<SGDOptimizer>(learningRate);
        }
        trainer = make_unique<Trainer>(*model, *loss, *optimizer);


        scalerX -> fit(X);
        scalerY -> fit(Y);

        currentEpoch = 0;
        currentLoss = 0;

        scaledX = scalerX -> transform(X);
        scaledY = scalerY -> transform(Y);

        state = GuiState::Training;
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

    if (dataset -> getColumnCount() == 2)
    {
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
        state = GuiState::Prediction;
    }
}

void Gui::prediction(){

}

