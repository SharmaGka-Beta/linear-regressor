#include <vector>
#include "matrix.h"

using namespace std;

class Model{

    public:

        vector <double> predict(vector<double> weights, vector<vector<double>> inputs){

            vector <double> predictions;

            int sz = weights.size();

            for(int i = 0; i < sz; i++){

                vector<double> row1 = inputs[i];
                double prediction = Matrix::multiply(row1, weights);
                predictions.push_back(prediction);
            }
            return predictions;
        }
};