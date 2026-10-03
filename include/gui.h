#pragma once

class Gui{
    private:

        int state = 0;
        void renderState();
        void loadFile();


    public:
        void run();
};