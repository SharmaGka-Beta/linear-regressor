#include "model.h"

class Optimizer{
    public:
        virtual void update(Model&, vector<double>&, double) = 0;
        virtual ~Optimizer() = default;
};

class SGDOptimizer : public Optimizer{

    private:
        double learningRate;

    public:
        SGDOptimizer(double);
        SGDOptimizer();

        void update(Model&, vector<double>&, double);
};