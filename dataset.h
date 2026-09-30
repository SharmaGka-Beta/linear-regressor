#pragma once

#include <vector>
#include <string>

using namespace std;

class Dataset{

    private:

        vector<vector<string>> dataset;

    public:

        Dataset(string);

        void setDataset(string);
        void printDataset();
};