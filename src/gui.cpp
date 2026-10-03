#include "gui.h"
#include "dataset.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>
#include <ImGuiFileDialog.h>
#include <iostream>

void Gui::run(){
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "SFML - Linear Regressor");

    (void)ImGui::SFML::Init(window);

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

    if (state == 0){
        loadFile();
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
                state = 1;
            }
            else{
                targetColumn = dataset -> getColumnCount() - 1;
            }
        }
        catch(...){
            
        }
    }
}
