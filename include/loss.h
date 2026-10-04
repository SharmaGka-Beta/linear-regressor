#pragma once

#include <vector>
#include <string>

using namespace std;

const inline vector <string> losses = {"MSE"};

class LossFunction{

    public:
        virtual double computeLoss(vector <double>&, vector <double>&) = 0;
        virtual vector <double> computeGradient(vector <double>&, vector<double>&) = 0;
        virtual ~LossFunction() = default;
};

class MSELoss : public LossFunction{

    public:
        virtual double computeLoss(vector <double>&, vector <double>&) override;
        virtual vector <double> computeGradient(vector <double>&, vector<double>&);
};