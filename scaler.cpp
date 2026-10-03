#include <vector>
#include <cmath>

#include "exceptions.h"

using namespace std;

class Scaler{

    private:
        vector<double> mean;
        vector<double> sigma;
        bool fitted = false;

    public:

        void fit(vector<vector<double>>& X){
            if (X.empty()){
                throw CustomException("Cannot fit an empty dataset!");
            }

            int rows = X.size();
            int cols = X[0].size();

            mean.assign(cols, 0.0);
            sigma.assign(cols, 0.0);

            for(auto& row: X){
                for(int i = 0; i < cols; i++){
                    mean[i] += row[i];
                }
            }

            for(int i = 0; i < cols; i++){
                mean[i] /= rows;
            }


            for(auto& row: X){
                for(int i = 0; i < cols; i++){
                    sigma[i] += (row[i] - mean[i])*(row[i] - mean[i]);
                }
            }
            for(int i = 0; i < cols; i++){
                sigma[i] = sqrt(sigma[i] / rows);

                if (sigma[i] == 0){
                    sigma[i] = 1;
                }
            }
            fitted = true;

        }

        vector<vector<double>> transform(vector<vector<double>>& X){
            if(!fitted){
                throw CustomException("Fit before transforming!");
            }

            vector<vector<double>> temp = X;
            for(auto& row: temp){
                for(int i = 0; i < (int)temp[0].size(); i++){
                    row[i] = (row[i] - mean[i]) / sigma[i];
                }
            }
            return temp;
        }

        void fit(vector<double>& Y){
            if(Y.empty()){
                throw CustomException("Cannot fit on an empty dataset!");
            }

            mean.assign(1, 0.0);
            sigma.assign(1, 0.0);

            int rows = Y.size();
            for(int i = 0; i < rows; i++){
                mean[0] += Y[i];
            }
            mean[0] /= rows;

            for(int i = 0; i < rows; i++){
                sigma[0] += (Y[i] - mean[0]) * (Y[i] - mean[0]);
            }
            sigma[0] = sqrt(sigma[0] / rows);

            if(sigma[0] == 0){
                sigma[0] = 1;
            }
            fitted = true;
        }

        vector<double> transform(vector<double>& Y){
            if(!fitted){
                throw CustomException("Fit before transforming!");
            }
            vector<double> temp = Y;
            for(int i = 0; i < (int)temp.size(); i++){
                temp[i] = (temp[i] - mean[0]) / sigma[0];
            }
            return temp;
        }
};