#pragma once

#include "model.h"

#include <vector>
#include <string>

const inline vector<string> optimizers = {"SGD", "Momentum", "Adam"};

class Optimizer{
    public:
        virtual void update(Model&, vector<double>&, double) = 0;
        virtual ~Optimizer() = default;
};

class SGDOptimizer : public Optimizer{

    private:
        double learningRate;

    public:
        SGDOptimizer(double);
        SGDOptimizer();

        void update(Model&, vector<double>&, double);
};

class MomentumOptimizer : public Optimizer{

    private:
        double learningRate;
        double beta;
        vector<double> velocity;
        double biasVelocity;

    public:
        MomentumOptimizer(double, double);
        MomentumOptimizer();

        void update(Model&, vector<double>&, double) override;
};


