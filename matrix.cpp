#include <vector>

#include "matrix.h"

using namespace std;


double Matrix::dot(vector<double>& mat1, vector<double>& mat2){
    double result = 0;
    int sz = mat1.size();
    for(int i = 0; i < sz; i++){
        result += mat1[i] * mat2[i];
    }

    return result;
}
