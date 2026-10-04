#include "loss.h"

#include <vector>
#include <cmath>

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

double MAELoss::computeLoss(vector <double>& predictions, vector <double>& actual){

    double loss = 0;
    int size = predictions.size();

    for(int i = 0; i < size; i++){
        loss += fabs((predictions[i] - actual[i]));
    }

    loss /= size;
    return loss;
}

vector<double> MAELoss::computeGradient(vector<double>& predictions, vector<double>& actual){

    int size = predictions.size();
    vector<double> gradients(size, 0.0);

    for(int i = 0; i < size; i++){
        if(predictions[i] > actual[i]){
            gradients[i] = 1.0 / size;
        }
        else if(predictions[i] < actual[i]){
            gradients[i] = -1.0 / size;
        }
        else{
            gradients[i] = 0.0;
        }
    }

    return gradients;
}

double HuberLoss::computeLoss(vector <double>& predictions, vector <double>& actual){

    double delta = 1.0;
    int size = predictions.size();
    double loss=0;

    for(int i = 0; i < size; i++){
        double error = predictions[i]-actual[i];
        
        if(fabs(error)<=delta){
            loss=loss + (error*error)/2;
        }
        else{
            loss = loss + (delta*(fabs(error) - (delta/2)));
        }
    }
    loss /= size;
    return loss;
}

vector<double> HuberLoss::computeGradient(vector<double>& predictions, vector<double>& actual){

    int size = predictions.size();
    vector<double> gradients(size, 0.0);
    double delta = 1.0;

    for(int i = 0; i < size; i++){
        double error = predictions[i]-actual[i];

        if(fabs(error)<=delta){
            gradients[i] = error/size;
        }
        else{
            if(error > 0){
                gradients[i] = delta / size;
            } 
            else{
                gradients[i] = -delta / size;
            }
        }
    }
    return gradients;
}
