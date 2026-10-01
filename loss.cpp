#include <vector>

using namespace std;

class LossFunction{

    public:
        virtual double computeLoss(vector <double>, vector <double>) = 0; 
};

class MSELoss : virtual public LossFunction{

    public:
        virtual double computeLoss(vector <double> predictions, vector <double> actual) override{

            double loss = 0;
            int sz = predictions.size();

            for(int i = 0; i < sz; i++){
                loss += (predictions[i] - actual[i]) * (predictions[i] - actual[i]);
            }

            loss /= sz;
            return loss;
        }
};