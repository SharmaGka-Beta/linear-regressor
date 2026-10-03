#pragma once

#include "model.h"
#include "optimizer.h"
#include "loss.h"

#include <vector>
#include <random>

using namespace std;

class Trainer{

    private:
        Model& model;
        LossFunction& lossFunction;
        Optimizer& optimizer;
    
    public:
    
        Trainer(Model&, LossFunction&, Optimizer&);

        void train(vector<vector<double>>&, vector<double>&, int);
        double trainOneEpoch(vector<vector<double>>&, vector<double>&);
        double oneEpoch(vector<int>&, mt19937&, vector<vector<double>>&, vector<double>&);

};