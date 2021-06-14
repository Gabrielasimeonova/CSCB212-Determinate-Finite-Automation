#include "DeterminateFiniteAutomataChar.h"
#include "AutomatonStateException.h"

DeterminateFiniteAutomataChar::DeterminateFiniteAutomataChar() : DeterminateFiniteAutomata() {

}

DeterminateFiniteAutomataChar::DeterminateFiniteAutomataChar(State** states, unsigned int statesCount, char* alphabet,
    unsigned int alphabetCount, int** transitions)
    : DeterminateFiniteAutomata(states, statesCount, alphabet, alphabetCount, transitions) {}

DeterminateFiniteAutomataChar::DeterminateFiniteAutomataChar(const DeterminateFiniteAutomataChar& other) {
    // TODO: Handle
}

DeterminateFiniteAutomataChar::~DeterminateFiniteAutomataChar() {

}

DeterminateFiniteAutomataChar& DeterminateFiniteAutomataChar::operator=(const DeterminateFiniteAutomataChar& other) {
    if (this != &other) {
        DeterminateFiniteAutomata<char>::operator=(other);
    }
    return *this;
}

std::ostream& DeterminateFiniteAutomataChar::writer(std::ostream& ostream) const {
    return DeterminateFiniteAutomata::writer(ostream);
}

std::istream& DeterminateFiniteAutomataChar::read(std::istream& istream) {
    return DeterminateFiniteAutomata::read(istream);
}


bool DeterminateFiniteAutomataChar::process(const char* word) const {
    size_t len = strlen(word);

    State* currentState = this->beginningState;

    for (int i = 0; i < len; i++) {
        char symbol = word[i];
        int index = getSymbolIndex(symbol);

        if (index == -1) {
            std::cout << "Посоченият символ не съществува: " << symbol << std::endl;
            //throw AutomatonStateException("Посоченият символ не съществува: ", symbol);
        }

        int stateIndex = this->transitions[currentState->getIndex()][index];

        currentState = this->states[stateIndex];
    }

    return currentState->getIsFinalState();
}

int DeterminateFiniteAutomataChar::getSymbolIndex(char symbol) const {
    for (int i = 0; i < this->alphabetCount; i++) {
        if (symbol == this->alphabet[i]) {
            return i;
        }
    }
    return -1;
}

DeterminateFiniteAutomata<char>*
DeterminateFiniteAutomataChar::construct(State** states, unsigned statesCount, char* alphabet, unsigned alphabetCount, int** transitions) const {
    DeterminateFiniteAutomataChar* result = new DeterminateFiniteAutomataChar(states, statesCount, alphabet, alphabetCount, transitions);
    states[0]->setIsBeginningState(true);
    result->setBeginningState(states[0]);
    return result;
}