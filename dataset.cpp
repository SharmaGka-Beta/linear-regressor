#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Dataset{

    private:

        vector<vector<string>> dataset;
    
    public:

        void setDataset(string fileName){

            ifstream file(fileName);

            if (!file.is_open()){
                cout << "Could not open file!";
                return;
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

        void printDataset(){

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
