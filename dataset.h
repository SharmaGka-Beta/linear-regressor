#pragma once

#include <vector>
#include <string>

using namespace std;

class Dataset{

    private:

        vector<vector<string>> dataset;
        vector <string> headers;

        bool hasHeaders(string);

    public:

        Dataset(string);

        void setDataset(string);
        void printDataset();
};