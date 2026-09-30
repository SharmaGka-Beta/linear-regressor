#pragma once

#include <vector>

using namespace std;

class LossFunction{

    public:
        virtual double computeLoss(vector <int>, vector <int>) = 0;
};

class MSELoss : virtual public LossFunction{

    public:
        virtual double computeLoss(vector <int>, vector <int>) override;
};