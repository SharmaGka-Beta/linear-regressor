#pragma once

#include <vector>
#include <string>

using namespace std;

class Dataset{

    private:

        vector<vector<double>> dataset;
        vector <string> headers;

        int getTargetIndex(string name);
        
        public:
        
        Dataset(string);
        
        void setDataset(string);
        void printDataset();

        bool hasHeaders(string);
        int getColumnCount();
        vector<string>& getHeaders();

        vector<vector<double>> getFeatures(string);
        vector <double> getTargets(string);
};