#include <exception>
#include <string>

using namespace std;

class CustomException : public exception{

    private:
        string exc;

    public:
        CustomException(string e) : exc(e){}

        const char* what() const noexcept override{
            return exc.c_str();
        }
};