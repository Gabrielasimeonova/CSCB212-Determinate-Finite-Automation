#pragma once
#ifndef AUTOMATA_PROJECT_FINAL_DETERMINATEFINITEAUTOMATACHAR_H
#define AUTOMATA_PROJECT_FINAL_DETERMINATEFINITEAUTOMATACHAR_H


#include "DeterminateFiniteAutomata.h"

class DeterminateFiniteAutomataChar : public DeterminateFiniteAutomata<char> {

public:
	DeterminateFiniteAutomataChar();
	DeterminateFiniteAutomataChar(State** states, unsigned int statesCount, char* alphabet, unsigned int alphabetCount, int** transitions);
	DeterminateFiniteAutomataChar(const DeterminateFiniteAutomataChar& other);
	virtual ~DeterminateFiniteAutomataChar();
	DeterminateFiniteAutomataChar& operator=(const DeterminateFiniteAutomataChar& other);

	bool process(const char* word) const override;

	DeterminateFiniteAutomata<char>*
		construct(State** states, unsigned statesCount, char* alphabet, unsigned alphabetCount, int** transitions) const override;

	std::ostream& writer(std::ostream& ostream) const override;
	std::istream& read(std::istream& istream) override;


protected:
	int getSymbolIndex(char symbol) const;
};


#endif 