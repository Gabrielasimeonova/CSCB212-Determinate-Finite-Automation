#pragma once
#ifndef AUTOMATA_PROJECT_DETERMINATEFINITEAUTOMATAINT_H
#define AUTOMATA_PROJECT_DETERMINATEFINITEAUTOMATAINT_H


#include "DeterminateFiniteAutomata.h"

class DeterminateFiniteAutomataInt : public DeterminateFiniteAutomata<int> {

public:
    DeterminateFiniteAutomataInt();
    DeterminateFiniteAutomataInt(State** states, unsigned int statesCount, int* alphabet, unsigned int alphabetCount, int** transitions);
    DeterminateFiniteAutomataInt(const DeterminateFiniteAutomataInt& other);
    virtual ~DeterminateFiniteAutomataInt();
    DeterminateFiniteAutomataInt& operator=(const DeterminateFiniteAutomataInt& rhs);

    bool process(const char* word) const override;

    DeterminateFiniteAutomata<int>*
        construct(State** states, unsigned statesCount, int* alphabet, unsigned alphabetCount, int** transitions) const override;


    std::ostream& writer(std::ostream& ostream) const override;
    std::istream& read(std::istream& istream) override;

protected:
    int getSymbolIndex(char symbol) const;

};


#endif 