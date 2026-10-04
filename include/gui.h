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
        int currentEpoch = 0;
        double currentLoss = 0;
        int epochs = 100;
        double learningRate = 0.01;
        bool showPreds = false;

        vector<vector<double>> X;
        vector<double> Y;
        vector<vector<double>> scaledX;
        vector<double> scaledY;
        vector <double> plotX;
        vector <vector<double>> inputs{};
        vector<double> preds{};

        vector<double> finalWeights;
        double finalBias;

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
        void training();
        void prediction();
        void clearAll();


    public:
        void run();
};