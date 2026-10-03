#pragma once

#include <exception>
#include <string>

using namespace std;

class CustomException : public exception{

    private:
        string exc;

    public:
        CustomException(string);

        const char* what() const noexcept override;
};