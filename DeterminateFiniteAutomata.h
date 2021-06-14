#ifndef AUTOMATA_PROJECT_DETERMINATEFINITEAUTOMATA_H
#define AUTOMATA_PROJECT_DETERMINATEFINITEAUTOMATA_H


#include "State.h"


template<typename T>
class DeterminateFiniteAutomata {

    friend std::ostream& operator<<(std::ostream& ostream, const DeterminateFiniteAutomata<T>& rhs) {
        return rhs.writer(ostream);
    }
    friend std::istream& operator>>(std::istream& istream, DeterminateFiniteAutomata<T>& rhs) {
        return rhs.read(istream);
    }

public:
    DeterminateFiniteAutomata();
    DeterminateFiniteAutomata(State** states, unsigned statesCount, T* alphabet, unsigned alphabetCount, int** transitions);
    explicit DeterminateFiniteAutomata(State** states, unsigned statesCount);
    DeterminateFiniteAutomata(const DeterminateFiniteAutomata<T>& other);
    virtual ~DeterminateFiniteAutomata();

    DeterminateFiniteAutomata<T>& operator=(const DeterminateFiniteAutomata<T>& rhs);
    DeterminateFiniteAutomata<T>& operator^(DeterminateFiniteAutomata<T>& rhs);
    DeterminateFiniteAutomata<T>* operator|(const DeterminateFiniteAutomata<T>& rhs);
    DeterminateFiniteAutomata<T>* operator&(const DeterminateFiniteAutomata<T>& rhs);

    virtual std::ostream& writer(std::ostream& ostream) const;
    virtual std::istream& read(std::istream& istream);

    virtual bool process(const char* word) const = 0;
    virtual DeterminateFiniteAutomata<T>* construct(State** states, unsigned statesCount, T* alphabet, unsigned alphabetCount, int** transitions) const = 0;

    unsigned int getStatesCount() const;
    void setStatesCount(unsigned int statesCount);
    State** getStates() const;
    void setStates(State** states);
    State* getBeginningState() const;
    void setBeginningState(State* beginningState);

private:

    int findStateIndex(State** states, unsigned statesCount, char* stateName);

    static bool unionPredicate(State* state1, State* state2);
    static bool intersectionPredicate(State* state1, State* state2);

protected:
    void print(char* message, bool isReadingFromFile);

    void print(int number, bool isReadingFromFile);
    void initStates(std::istream& istream, bool isReadingFromfile);
    void initBeginningState(std::istream& istream, bool isReadingFromFile);
    void initFinalState(std::istream& istream, bool isReadingFromFile);
    void initAlphabet(std::istream& istream, bool isReadingFromFile);

    void initTransitions(std::istream& istream, bool isReadingFromFile);
    unsigned alphabetCount = 0;
    T* alphabet;

    int** transitions;
    unsigned statesCount = 0;
    State** states;

    State* beginningState;
    State* findState(char* stateName);
};



#endif 
