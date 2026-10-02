#pragma once

#include <vector>
#include "matrix.h"

using namespace std;

class Model{

    private:
        vector<double> weights;
        double bias;

    public:

        Model(size_t size);
        vector <double> predict(vector<vector<double>>&);
        void setParams(vector<double>&, double);

        vector<double> getWeights();
        double getBias();

        vector <double> getWeightGrad(vector <double>&, vector<vector<double>>&);
        double getBiasGrad(vector<double>& lossGradients);
};