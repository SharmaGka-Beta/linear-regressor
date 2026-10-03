#include "loss.h"

#include <vector>

using namespace std;

double MSELoss::computeLoss(vector <double>& predictions, vector <double>& actual){

    double loss = 0;
    int sz = predictions.size();

    for(int i = 0; i < sz; i++){
        loss += (predictions[i] - actual[i]) * (predictions[i] - actual[i]);
    }

    loss /= sz;
    return loss;
}

vector <double> MSELoss::computeGradient(vector <double>& predictions, vector<double>& actual){

    int sz = predictions.size();
    vector <double> gradients(sz, 0.0);
    for(int i = 0; i < sz; i++){
        gradients[i] = 2.0 * (predictions[i] - actual[i]) / sz;
    }

    return gradients;
}
