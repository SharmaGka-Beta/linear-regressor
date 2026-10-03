cmake_minimum_required(VERSION 3.22)

project(LinearRegressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON 
    EXCLUDE_FROM_ALL
)

FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b
    GIT_SHALLOW ON
)

FetchContent_Declare(
    ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG 3.0
    GIT_SHALLOW ON 
)

FetchContent_Declare(
    ImPlot
    GIT_REPOSITORY https://github.com/epezent/implot.git
    GIT_TAG v0.17
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(ImGui)
FetchContent_MakeAvailable(ImGui-SFML)
FetchContent_MakeAvailable(ImPlot)

add_executable(LinearRegressor
                        src/main.cpp
                        src/dataset.cpp
                        src/exceptions.cpp
                        src/loss.cpp
                        src/matrix.cpp
                        src/model.cpp
                        src/optimizer.cpp
                        src/scaler.cpp
                        src/trainer.cpp)

target_include_directories(LinearRegressor
                            PRIVATE
                                include
                                ${implot_SOURCE_DIR}) 
                                
target_sources(LinearRegressor
                PRIVATE
                    ${implot_SOURCE_DIR}/implot.cpp
                    ${implot_SOURCE_DIR}/implot_items.cpp)
                                
target_link_libraries(LinearRegressor
                            PRIVATE
                                SFML::Graphics
                                SFML::Window
                                SFML::System
                                ImGui-SFML::ImGui-SFML)

