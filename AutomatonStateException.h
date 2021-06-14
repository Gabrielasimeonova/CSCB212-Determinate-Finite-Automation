#ifndef _AUTOMATONSTATEEXCEPTION_H
#define _AUTOMATONSTATEEXCEPTION_H


#include <exception>

class AutomatonStateException : public std::exception {

public:

    AutomatonStateException(char* message, const char* detail);
    AutomatonStateException(char* message, int detail);

    ~AutomatonStateException() override;


    const char* what() const noexcept override;

private:
    char* message = new char[256];
    char* detailChar = new char[128];
    int detailInt = -1;

};


#endif 