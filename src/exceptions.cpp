#include <exception>
#include <string>

#include "exceptions.h"

using namespace std;


CustomException::CustomException(string e) : exc(e){}

const char* CustomException::what() const noexcept{
    return exc.c_str();
}
