# Linear Regressor

A linear regression implementation C++ (C++20), with a GUI for loading data, training a model, and visualizing results. 

## Features

- **Interactive GUI** built with Dear ImGui + SFML
- **Dataset loading** via a built-in file dialog
- **Live plotting** dynamic graph update with ImPlot

## Project Structure

```
linear-regressor/
├── CMakeLists.txt
├── include/            #Header Files
└── src/
    ├── main.cpp        # Entry Point
    ├── gui.cpp         # User Interface
    ├── dataset.cpp     # Data loading
    ├── matrix.cpp      # Matrix dot product
    ├── model.cpp       # Regression Model
    ├── loss.cpp        # Loss functions
    ├── optimizer.cpp   # Optimizers
    ├── scaler.cpp      # Feature scaling
    ├── trainer.cpp     # Training loop
    └── exceptions.cpp  # Custom exception
```

## Requirements

- A C++20 compatible compiler
- [CMake](https://cmake.org/) 3.22 or newer
- Git
- An internet connection on the first build
- On Linux, SFML's system dependencies (X11, OpenGL, etc.). Kindly install them before CMake or as CMake gives errors.

## Dependencies

All fetched automatically through CMake `FetchContent`:

| Library | Version | Purpose |
|---|---|---|
| [SFML](https://github.com/SFML/SFML) | 3.0.2 | GUI Backend |
| [Dear ImGui](https://github.com/ocornut/imgui) | v1.91.9b | GUI widgets |
| [ImGui-SFML](https://github.com/SFML/imgui-sfml) | v3.0 | ImGui backend for SFML |
| [ImPlot](https://github.com/epezent/implot) | v0.17 | Plotting |
| [ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog) | master | File picker |

## Build & Run

```bash
git clone https://github.com/SharmaGka-Beta/linear-regressor.git
cd linear-regressor
```

```bash
mkdir build && cd build
cmake ..
cmake --build ./
```

```bash
./bin/LinearRegressor
```

## Usage

1. Launch the application.
2. Resize widgets accordingly.
3. Use the file dialog to load a dataset.
4. 2D datasets will be plotted alongside.
5. Configure training options and start training.
6. Watch the loss and fitted line update in the plots.