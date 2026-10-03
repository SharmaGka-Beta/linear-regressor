#pragma once

#include "dataset.h"

#include <vector>
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

        vector<vector<double>> X;
        vector<double> Y;

        unique_ptr<Dataset> dataset;

        void renderState();
        void loadFile();
        void selectTarget();
        void ready();


    public:
        void run();
};