#include "model.h"
#include "optimizer.h"

#include <vector>
#include<cmath>

using namespace std;


SGDOptimizer::SGDOptimizer(double lr): learningRate(lr){}
SGDOptimizer::SGDOptimizer() : learningRate(0.1){}

void SGDOptimizer::update(Model& model, vector<double>& weightGrads, double biasGrad){

    vector<double> weights = model.getWeights();

    for(int i = 0; i < (int)weightGrads.size(); i++){
        weights[i] -= learningRate*weightGrads[i];
    }
    double bias = model.getBias() - learningRate*biasGrad;
    model.setParams(weights, bias);
}

MomentumOptimizer::MomentumOptimizer(double lr, double b) : learningRate(lr), beta(b), biasVelocity(0.0){}
MomentumOptimizer::MomentumOptimizer(): learningRate(0.01), beta(0.9), biasVelocity(0.0){}

void MomentumOptimizer::update(Model& model, vector<double>& weightGrads, double biasGrad){

    vector<double> weights = model.getWeights();

    if(velocity.empty()){
        velocity = vector<double>(weightGrads.size(), 0.0);
    }

    for(int i = 0; i < (int)weightGrads.size(); i++){

        velocity[i] = beta*velocity[i] + (1.0-beta)*weightGrads[i];
        weights[i] -= learningRate*velocity[i];
    }

    biasVelocity = beta*biasVelocity + (1.0-beta)*biasGrad;
    double bias = model.getBias() - learningRate*biasVelocity;
    model.setParams(weights, bias);
}

