#pragma once

#include "dataset.h"

#include <string>
#include <memory>

using namespace std;


enum GuiState{
    FileLoading,
    TargetSelection,
    Ready,
    Training,
    Prediction
};

class Gui{
    private:

        int state = GuiState::FileLoading;
        string fileName;
        int targetColumn = 0;

        unique_ptr<Dataset> dataset;

        void renderState();
        void loadFile();
        void selectTarget();


    public:
        void run();
};