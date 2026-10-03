#include "trainer.h"
#include "model.h"
#include "optimizer.h"
#include "loss.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

using namespace std;


Trainer::Trainer(Model& m, LossFunction& lf, Optimizer& o) : model(m), lossFunction(lf), optimizer(o){}

void Trainer::train(vector<vector<double>>& X, vector<double>& Y, int epochs){
    
    vector<int> order((int)X.size());
    iota(order.begin(), order.end(), 0);
    mt19937 rng(42);

    for(int epoch = 0; epoch < epochs; epoch++){
        shuffle(order.begin(), order.end(), rng);

        for(int i: order){
            vector<vector<double>> xi = {X[i]};
            vector<double> yi = {Y[i]};
            
            vector <double> predicted = model.predict(xi);
            vector <double> lossGradient = lossFunction.computeGradient(predicted, yi);
            vector <double> weightGrads = model.getWeightGrad(lossGradient, xi);
            double biasGrad = model.getBiasGrad(lossGradient);

            optimizer.update(model, weightGrads, biasGrad);
        }

        vector <double> pred = model.predict(X);
        double loss = lossFunction.computeLoss(pred, Y);
        cout << "Epoch: " << epoch << "    " << "Loss: " << loss << endl;
    }
}


