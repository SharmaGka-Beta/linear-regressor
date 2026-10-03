cmake_minimum_required(VERSION 3.22)

project(LinearRegressor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
                                include)       

