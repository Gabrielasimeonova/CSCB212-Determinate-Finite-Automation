#include "DeterminateFiniteAutomataInt.h"
#include "AutomatonStateException.h"

DeterminateFiniteAutomataInt::DeterminateFiniteAutomataInt() : DeterminateFiniteAutomata<int>() {

}

DeterminateFiniteAutomataInt::DeterminateFiniteAutomataInt(State** states, unsigned int statesCount, int* alphabet,
    unsigned int alphabetCount, int** transitions)
    : DeterminateFiniteAutomata(states, statesCount, alphabet, alphabetCount, transitions) {}

DeterminateFiniteAutomataInt::DeterminateFiniteAutomataInt(const DeterminateFiniteAutomataInt& other) {
    // TODO: Handle
}

DeterminateFiniteAutomataInt::~DeterminateFiniteAutomataInt() {
    if (this->alphabet != nullptr) {
        delete[] this->alphabet;
    }

    if (this->transitions != nullptr) {
        delete[] this->transitions;
    }
}

DeterminateFiniteAutomataInt& DeterminateFiniteAutomataInt::operator=(const DeterminateFiniteAutomataInt& rhs) {
    if (this != &rhs) {
        DeterminateFiniteAutomata<int>::operator=(rhs);
    }
    return *this;
}

std::ostream& DeterminateFiniteAutomataInt::writer(std::ostream& ostream) const {
    return DeterminateFiniteAutomata<int>::writer(ostream);
}

std::istream& DeterminateFiniteAutomataInt::read(std::istream& istream) {
    DeterminateFiniteAutomata<int>::read(istream);

    return istream;
}

bool DeterminateFiniteAutomataInt::process(const char* word) const {
    size_t len = strlen(word);

    State* currentState = this->beginningState;

    for (int i = 0; i < len; i++) {
        char symbol = word[i];
        int index = getSymbolIndex(symbol);

        if (index == -1) {
            std::cout << "Посоченият символ нe съществува: " << symbol << std::endl;
           // throw AutomatonStateException("Посоченият символ на съществува: ", symbol);
        }

        int stateIndex = this->transitions[currentState->getIndex()][index];

        currentState = this->states[stateIndex];
    }

    return currentState->getIsFinalState();
}

int DeterminateFiniteAutomataInt::getSymbolIndex(char symbol) const {
    int symbolToInt = symbol - '0';
    for (int i = 0; i < this->alphabetCount; i++) {
        if (symbolToInt == this->alphabet[i]) {
            return i;
        }
    }
    return -1;
}

DeterminateFiniteAutomata<int>*
DeterminateFiniteAutomataInt::construct(State** states, unsigned statesCount, int* alphabet, unsigned alphabetCount, int** transitions) const {
    DeterminateFiniteAutomataInt* result = new DeterminateFiniteAutomataInt(states, statesCount, alphabet, alphabetCount, transitions);
    states[0]->setIsBeginningState(true);
    result->setBeginningState(states[0]);
    return result;
}