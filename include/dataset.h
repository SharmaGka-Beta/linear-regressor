#pragma once

#include <vector>
#include <string>

using namespace std;

class Dataset{

    private:

        vector<vector<double>> dataset;
        vector <string> headers;

        int getTargetIndex(string name);
        bool doesHaveHeaders = true;
        
    public:
        
        Dataset(string);
        
        void setDataset(string);
        void printDataset();

        bool hasHeaders(string);
        int getColumnCount();
        vector<string>& getHeaders();

        vector<vector<double>> getFeatures(string);
        vector<vector<double>> getFeatures(int);

        vector <double> getTargets(string);
        vector <double> getTargets(int);

};