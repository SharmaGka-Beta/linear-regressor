#pragma once

#include <vector>

using namespace std;

class Scaler{

    private:
        vector<double> mean;
        vector<double> sigma;
        bool fitted = false;

    public:

        void fit(vector<vector<double>>&);
        void fit(vector<double>&);

        vector<vector<double>> transform(vector<vector<double>>&);
        vector<double> transform(vector<double>&);

        vector<double> invert(vector<double>&);

        vector<double>getMean();
        vector<double>getSigma();
};

