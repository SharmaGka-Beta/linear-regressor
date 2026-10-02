#include <vector>

using namespace std;

class LossFunction{

    public:
        virtual double computeLoss(vector <double>&, vector <double>&) = 0; 
        virtual vector <double> computeGradient(vector <double>& predictions, vector<double>& actual) = 0;
        virtual ~LossFunction() = default;
};

class MSELoss : public LossFunction{

    public:
        virtual double computeLoss(vector <double>& predictions, vector <double>& actual) override{

            double loss = 0;
            int sz = predictions.size();

            for(int i = 0; i < sz; i++){
                loss += (predictions[i] - actual[i]) * (predictions[i] - actual[i]);
            }

            loss /= sz;
            return loss;
        }

        virtual vector <double> computeGradient(vector <double>& predictions, vector<double>& actual) override{

            int sz = predictions.size();
            vector <double> gradients(sz, 0.0);
            for(int i = 0; i < sz; i++){
                gradients[i] = 2.0 * (predictions[i] - actual[i]) / sz;
            }

            return gradients;
        }
};