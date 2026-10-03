#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "exceptions.h"

using namespace std;

class Dataset{

    private:

        vector<vector<double>> dataset;
        vector<string> headers;

        bool hasHeaders(string fileName){

            ifstream file(fileName);

            if (!file.is_open()){
                throw CustomException("File could not be opened!");
            }

            string line;
            getline(file, line);
            stringstream lineStream(line);
            string value;

            vector <string> row; 
            while(getline(lineStream, value, ',')){
                row.push_back(value);
            }

            file.close();

            try{
                for(string i: row){
                    stod(i);
                }
                return false;
            }
            catch(...){
                return true;
            }
        }

        int getTargetIndex(string name){
            for(int i = 0; i < (int)headers.size(); i++){
                if (headers[i] == name){
                    return i;
                }
            }

            return (int)dataset[0].size() - 1;
        }
    
    public:

        Dataset(string fileName){
            setDataset(fileName);
        }

        void setDataset(string fileName){

            ifstream file(fileName);

            if (!file.is_open()){
                throw CustomException("File could not be opened!");
            }

            string line;
            if(hasHeaders(fileName)){
                getline(file, line);
                stringstream lineStream(line);

                string value;

                while(getline(lineStream, value, ',')){
                    headers.push_back(value);
                }
            }

            while(getline(file, line)){

                if(line.empty()){
                    continue;
                }

                stringstream lineStream(line);
                string value;

                vector <double> row;

                while(getline(lineStream, value, ',')){
                    row.push_back(stod(value));
                }

                dataset.push_back(row);
            }

            file.close();
        }

        void printDataset() const{

            int sz = dataset.size();

            for(int i = 0; i < (int)headers.size(); i++){
                cout << headers[i] << " ";
            }
            cout << endl;
            for(int i = 0; i < sz; i++){
                int rowSize = dataset[i].size();
                for(int j = 0; j < rowSize; j++){

                    cout << dataset[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        vector<vector<double>> getFeatures(string name){
            int targetIndex = getTargetIndex(name);

            vector<vector<double>>X;

            for(auto& row: dataset){
                vector<double> temp;
                for(int i = 0; i < (int)row.size(); i++){
                    if (i != targetIndex){
                        temp.push_back(row[i]);
                    }
                }
                X.push_back(temp);
            }

            return X;
        }

        vector <double> getTargets(string name){
            int targetIndex = getTargetIndex(name);

            vector <double> Y;

            for(auto& row: dataset){
                Y.push_back(row[targetIndex]);
            }

            return Y;
        }
};
