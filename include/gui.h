#pragma once

#include "dataset.h"

#include <string>

using namespace std;

class Gui{
    private:

        int state = 0;
        string fileName;
        int targetColumn;

        unique_ptr<Dataset> dataset;

        void renderState();
        void loadFile();


    public:
        void run();
};