#include "model.h"
#include <vector>

#include "optimizer.h"

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
