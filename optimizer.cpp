#include "model.h"
#include <vector>

using namespace std;

class Optimizer{
    public:
        virtual void update(Model& model, vector<double>& weightGrads, double biasGrad) = 0;
        virtual ~Optimizer() = default;
};

class SGDOptimizer : public Optimizer{

    private:
        double learningRate;

    public:
        SGDOptimizer(double lr): learningRate(lr){}
        SGDOptimizer() : learningRate(0.1){}

        void update(Model& model, vector<double>& weightGrads, double biasGrad){

            vector<double> weights = model.getWeights();

            for(int i = 0; i < (int)weightGrads.size(); i++){
                weights[i] -= learningRate*weightGrads[i];
            }
            double bias = model.getBias() - learningRate*biasGrad;
            model.setParams(weights, bias);
        }
};