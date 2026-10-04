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
        MomentumOptimizer(double);

        void update(Model&, vector<double>&, double) override;
};

class AdamOptimizer : public Optimizer{

    private:
        double learningRate;
        double beta1;
        double beta2;
        double epsilon;
        vector<double> m;
        vector<double> v;
        double biasM;
        double biasV;

        int timestep;

    public:
        AdamOptimizer(double, double, double, double);
        AdamOptimizer();
        AdamOptimizer(double);

        void update(Model&, vector<double>&, double) override;
};
