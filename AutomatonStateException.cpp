#include <cstring>
#include "AutomatonStateException.h"

AutomatonStateException::~AutomatonStateException() {

}

AutomatonStateException::AutomatonStateException(char* message, const  char* detail) :
    message(new char[strlen(message + 1)]),
    detailChar(new char[strlen(message + 1)]) {
    strcpy(this->message, message);
    strcpy(this->detailChar, detail);

}

AutomatonStateException::AutomatonStateException(char* message, int detail) :
    message(new char[strlen(message + 1)]),
    detailInt(detail) {
    strcpy(this->message, message);
}

const char* AutomatonStateException::what() const noexcept {
    if (this->detailInt != -1) {
        return strcat(this->message, reinterpret_cast<const char*>(&this->detailInt));
    }
    return strcat(this->message, this->detailChar);
}