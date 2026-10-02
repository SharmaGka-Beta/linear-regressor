#pragma once

#include <vector>
#include <string>

using namespace std;

class Dataset{

    private:

        vector<vector<double>> dataset;
        vector <string> headers;

        bool hasHeaders(string);
        int getTargetIndex(string name);

    public:

        Dataset(string);

        void setDataset(string);
        void printDataset();
};