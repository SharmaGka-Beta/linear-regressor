#pragma once

#include <vector>

using namespace std;

class LossFunction{

    public:
        virtual double computeLoss(vector <double>, vector <double>) = 0;
};

class MSELoss : virtual public LossFunction{

    public:
        virtual double computeLoss(vector <double>, vector <double>) override;
};