#pragma once

#include <vector>

using namespace std;

class LossFunction{

    public:
        virtual double computeLoss(vector <double>&, vector <double>&) = 0;
        virtual vector <double> computeGradient(vector <double>&, vector<double>&) = 0;
        virtual ~LossFunction() = default;
};

class MSELoss : virtual public LossFunction{

    public:
        virtual double computeLoss(vector <double>&, vector <double>&) override;
        virtual vector <double> computeGradient(vector <double>&, vector<double>&);
};

class MAELoss : virtual public LossFunction{

    public:
        virtual double computeLoss(vector <double>&, vector <double>&) override;
        virtual vector <double> computeGradient(vector <double>&, vector<double>&);
};



