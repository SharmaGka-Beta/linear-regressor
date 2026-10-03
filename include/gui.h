#pragma once

#include "trainer.h"
#include "model.h"
#include "optimizer.h"
#include "loss.h"
#include "dataset.h"
#include "scaler.h"

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
        vector<vector<double>> scaledX;
        vector<double> scaledY;

        unique_ptr<Dataset> dataset;
        unique_ptr<Scaler> scalerX;
        unique_ptr<Scaler> scalerY;
        unique_ptr<Model>model;
        unique_ptr<LossFunction> loss;
        unique_ptr<Optimizer> optimizer;
        unique_ptr<Trainer> trainer;

        void renderState();
        void loadFile();
        void selectTarget();
        void ready();
        void train();


    public:
        void run();
};