#include "gui.h"
#include "dataset.h"
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
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "SFML - Linear Regressor");

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
        state = GuiState::Ready;
    }
    ImGui::End();
}

void Gui::ready(){

    ImGui::Begin("Ready");

    if(ImGui::Button("Start Training")){
        state = GuiState::Training;
    }

    if(dataset -> getColumnCount() == 2){
        vector <double> plot;
        for(auto const& row: X){
            plot.push_back(row[0]);
        }

        if (ImPlot::BeginPlot("Dataset")){
            ImPlot::PlotScatter(
                "Data",
                plot.data(),
                Y.data(),
                static_cast<int>(Y.size())
            );

            ImPlot::EndPlot();
        }
    }
    else{
        ImGui::Text("Plot availible only for 2D regression :(");
    }
    ImGui::End();
}
