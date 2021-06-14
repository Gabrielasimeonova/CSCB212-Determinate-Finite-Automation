#ifndef AUTOMATA_PROJECT_STATE_H
#define AUTOMATA_PROJECT_STATE_H

#include <iostream>

class State {

    friend std::ostream& operator<<(std::ostream& ostream, const State& state);
    friend std::istream& operator>>(std::istream& istream, State& state);

public:
    State();
    explicit State(char* name, int index);
    State(const State& other);
    virtual ~State();

    std::ostream& write(std::ostream& ostream) const;
    std::istream& read(std::istream& istream);

    char* getName() const;

    int getIndex() const;
    void setIndex(int index);

    bool getIsBeginningState() const;
    void setIsBeginningState(bool isBeginningState);

    bool getIsFinalState() const;
    void setIsFinalState(bool isFinalState);

private:
    char* name = const_cast<char*>("default");
    int index = -1;

    bool isBeginningState = false;
    bool isFinalState = false;
};


#endif 