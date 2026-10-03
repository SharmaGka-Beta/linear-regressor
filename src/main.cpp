#include "trainer.h"
#include "model.h"
#include "optimizer.h"
#include "loss.h"
#include "dataset.h"
#include "scaler.h"

#include <vector>
#include <iostream>

using namespace std;

int main(){
    Dataset data("data.csv");

    vector<vector<double>> X = data.getFeatures("price");
    vector<double> Y = data.getTargets("price");

    Scaler xScaler, yScaler;
    xScaler.fit(X);
    yScaler.fit(Y);

    auto xScaled = xScaler.transform(X);
    auto yScaled = yScaler.transform(Y);

    Model model((int)X[0].size());

    MSELoss loss;
    SGDOptimizer optimizer(0.01);
    Trainer trainer(model, loss, optimizer);

    trainer.train(xScaled, yScaled, 100);

    cout << "w = " << model.getWeights()[0]<< ", b = " << model.getBias() << "\n";

    double area = 1800;
    vector<vector<double>> newInput = {{area}};
    vector<vector<double>> newScaled = xScaler.transform(newInput);

    vector<double> scaledPred = model.predict(newScaled);
    vector<double> realPred   = yScaler.invert(scaledPred);

    cout << "Predicted price for " << area << ": " << realPred[0] << "\n";

}