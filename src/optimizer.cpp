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
MomentumOptimizer::MomentumOptimizer(double lr): learningRate(lr), beta(0.9), biasVelocity(0.0){}


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

AdamOptimizer::AdamOptimizer(double lr, double b1, double b2, double eps)
    : learningRate(lr),
      beta1(b1),
      beta2(b2),
      epsilon(eps),
      biasM(0.0),
      biasV(0.0),
      timestep(0)
{}

AdamOptimizer::AdamOptimizer(double lr)
    : learningRate(lr),
      beta1(0.9),
      beta2(0.999),
      epsilon(1e-8),
      biasM(0.0),
      biasV(0.0),
      timestep(0)
{}

AdamOptimizer::AdamOptimizer()
    : learningRate(0.001),
      beta1(0.9),
      beta2(0.999),
      epsilon(1e-8),
      biasM(0.0),
      biasV(0.0),
      timestep(0)
{}

void AdamOptimizer::update(Model& model, vector<double>& weightGrads, double biasGrad){

    vector<double> weights = model.getWeights();

    if(m.empty()){
        m = vector<double>(weightGrads.size(), 0.0);
        v = vector<double>(weightGrads.size(), 0.0);
    }

    timestep++;

    for(int i = 0; i < (int)weightGrads.size(); i++){
        m[i] = beta1*m[i] + (1.0-beta1)*weightGrads[i];
        v[i] = beta2*v[i] + (1.0-beta2)*weightGrads[i]*weightGrads[i];

        double mHat = m[i] / (1.0-pow(beta1, timestep));
        double vHat = v[i] / (1.0-pow(beta2, timestep));

        weights[i] -= learningRate*mHat/(sqrt(vHat)+epsilon);
    }

    biasM = beta1*biasM + (1.0-beta1)*biasGrad;

    biasV = beta2*biasV + (1.0-beta2)*biasGrad*biasGrad;

    double biasMHat = biasM/(1.0-pow(beta1, timestep));
    double biasVHat = biasV/(1.0-pow(beta2, timestep));

    double bias = model.getBias() - learningRate*biasMHat/(sqrt(biasVHat)+epsilon);
    model.setParams(weights, bias);
}