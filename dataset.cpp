#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "exceptions.h"

using namespace std;

class Dataset{

    private:

        vector<vector<string>> dataset;
        vector<string> headers;

        bool hasHeaders(string filename){

            ifstream file(filename);

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

            while(getline(file, line)){

                stringstream lineStream(line);
                string value;

                vector <string> row;

                while(getline(lineStream, value, ',')){
                    row.push_back(value);
                }

                dataset.push_back(row);
            }

            file.close();
        }

        void printDataset() const{

            int sz = dataset.size();
            for(int i = 0; i < sz; i++){
                int rowSize = dataset[i].size();
                for(int j = 0; j < rowSize; j++){

                    cout << dataset[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
};
