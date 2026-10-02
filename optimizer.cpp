#include "model.h"

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

        }
};