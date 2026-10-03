#include "model.h"
#include "matrix.h"

#include <vector>

using namespace std;

Model::Model(size_t size) : weights(size, 0.0), bias(0.0){}

vector <double> Model::predict(vector<vector<double>>& inputs){

    vector <double> predictions;

    int sz = inputs.size();

    for(int i = 0; i < sz; i++){

        vector<double> row1 = inputs[i];
        double prediction = Matrix::dot(row1, weights) + bias;
        predictions.push_back(prediction);
    }
    return predictions;
}

void Model::setParams(vector<double>& newWeights, double newBias){
    weights = newWeights;
    bias = newBias;
}

vector<double> Model::getWeights(){
    return weights;
}

double Model::getBias(){
    return bias;
}

vector <double> Model::getWeightGrad(vector <double>& lossGradients, vector<vector<double>>& inputs){

    vector <double> weightGrads((int)weights.size(), 0.0);

    for(int i = 0; i < (int)lossGradients.size(); i++){
        for (int j = 0; j < (int)weights.size(); j++) {        
            weightGrads[j] += lossGradients[i] * inputs[i][j];
        }
    }
    return weightGrads;
}

double Model::getBiasGrad(vector<double>& lossGradients){

    double biasGrad = 0.0;
    for (double i : lossGradients){
        biasGrad += i;
    }
    return biasGrad;
}
