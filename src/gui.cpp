#include "gui.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>

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

    }
    ImGui::End();
}
