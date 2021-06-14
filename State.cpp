#include <cstring>
#include <iostream>
#include "State.h"


State::State() = default;

State::State(char* name, int index) : name(new char[strlen(name + 1)]), index(index) {
    strcpy(this->name, name);
}

State::State(const State & other) {
    this->name = new char[strlen(other.name + 1)];
    strcpy(this->name, other.name);

    this->index = other.index;
    this->isBeginningState = other.isBeginningState;
    this->isFinalState = other.isFinalState;
}

State::~State() {
    if (name != NULL) {
        delete[] name;
    }
}

std::ostream& operator<<(std::ostream & ostream, const State & state) {
    return state.write(ostream);
}

std::ostream& State::write(std::ostream & ostream) const {
    return ostream << name << (this->isBeginningState ? "[BEGINNING] " : "") << (this->isFinalState ? "[FINAL]" : "");
}

std::istream& operator>>(std::istream & istream, State & state) {
    return state.read(istream);
}

std::istream& State::read(std::istream & istream) {
    name = new char[51];
    istream >> name;
    return istream;
}

char* State::getName() const {
    return name;
}

int State::getIndex() const {
    return index;
}

void State::setIndex(int index) {
    State::index = index;
}

bool State::getIsBeginningState() const {
    return isBeginningState;
}

void State::setIsBeginningState(bool isBeginningState) {
    State::isBeginningState = isBeginningState;
}

bool State::getIsFinalState() const {
    return isFinalState;
}

void State::setIsFinalState(bool isFinalState) {
    State::isFinalState = isFinalState;
}