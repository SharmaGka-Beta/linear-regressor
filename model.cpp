#include <vector>
#include "matrix.h"

using namespace std;

class Model{

    private:
        vector<double> weights;
        double bias;

    public:

        Model(size_t size) : weights(size, 0.0), bias(0.0){}

        vector <double> predict(vector<vector<double>> inputs){

            vector <double> predictions;

            int sz = inputs.size();

            for(int i = 0; i < sz; i++){

                vector<double> row1 = inputs[i];
                double prediction = Matrix::multiply(row1, weights) + bias;
                predictions.push_back(prediction);
            }
            return predictions;
        }

        void setParams(vector<double>newWeights, double newBias){
            weights = newWeights;
            bias = newBias;
        }
};