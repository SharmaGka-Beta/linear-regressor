#include "model.h"
#include "loss.h"
#include "optimizer.h"

#include <vector>

using namespace std;

class Trainer{

    private:
        Model& model;
        LossFunction& lossFunction;
        Optimizer& optimizer;
    
    public:
    
        Trainer(Model&, LossFunction&, Optimizer&);

        void train(vector<vector<double>>&, vector<double>&, int);

};