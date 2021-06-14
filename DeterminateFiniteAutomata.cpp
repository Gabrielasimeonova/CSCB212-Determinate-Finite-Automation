#include <cstring>
#include <iostream>
#include "DeterminateFiniteAutomata.h"
#include "AutomatonStateException.h"
#include "DeterminateFiniteAutomataInt.h"
#include "DeterminateFiniteAutomataChar.h"


template<typename T>
DeterminateFiniteAutomata<T>::DeterminateFiniteAutomata() {
	this->states = new State * [1];
	this->states[0] = new State[1];
	this->beginningState = new State();
}

template<typename T>
DeterminateFiniteAutomata<T>::DeterminateFiniteAutomata(State** states, unsigned statesCount, T* alphabet,
	unsigned alphabetCount, int** transitions) {
	this->states = states;
	this->statesCount = statesCount;
	this->alphabet = alphabet;
	this->alphabetCount = alphabetCount;
	this->transitions = transitions;
}

template<typename T>
DeterminateFiniteAutomata<T>::DeterminateFiniteAutomata(State** states, unsigned statesCount) : statesCount(
	statesCount) {
	this->states = states;
}

template<typename T>
DeterminateFiniteAutomata<T>::DeterminateFiniteAutomata(const DeterminateFiniteAutomata<T>& other) {
	this->states = other.states;
}

template<typename T>
DeterminateFiniteAutomata<T>::~DeterminateFiniteAutomata() {
	if (this->states != nullptr) {
		delete[] this->states;
	}
}

template<typename T>
DeterminateFiniteAutomata<T>& DeterminateFiniteAutomata<T>::operator=(const DeterminateFiniteAutomata<T>& rhs) {
	if (this != &rhs) {
		this->states = rhs.states;
	}

	return *this;
}

template<typename T>
DeterminateFiniteAutomata<T>& DeterminateFiniteAutomata<T>::operator^(DeterminateFiniteAutomata<T>& rhs) {
	for (int i = 0; i < rhs.statesCount; i++) {
		rhs.states[i]->getIsFinalState()
			? rhs.states[i]->setIsFinalState(false)
			: rhs.states[i]->setIsFinalState(true);
	}
	return rhs;
}

template<typename T>
std::ostream& operator<<(std::ostream& ostream, const DeterminateFiniteAutomata<T>& rhs) {
	return rhs.writer(ostream);
}

template<typename T>
std::istream& operator>>(std::istream& istream, DeterminateFiniteAutomata<T>& rhs) {
	return rhs.read(istream);
}

template<typename T>
std::ostream& DeterminateFiniteAutomata<T>::writer(std::ostream& ostream) const {

	ostream << "Състояния на автомата: \n";
	for (int i = 0; i < this->statesCount; i++) {
		ostream << "\t"
			<< this->states[i]->getName()
			<< " "
			<< (this->states[i]->getIsBeginningState() ? "[НАЧАЛО]" : "")
			<< (this->states[i]->getIsFinalState() ? "[КРАЙ]" : "")
			<< "\n";
	}

	ostream << "Азбука на автомата: ";
	for (int i = 0; i < this->alphabetCount; i++) {
		ostream << this->alphabet[i] << " ";
	}
	ostream << "\n";


	ostream << "Преходи на автомата: \n";
	for (int i = 0; i < this->statesCount; i++) {
		State* state = this->states[i];

		for (int j = 0; j < this->alphabetCount; j++) {
			int nextStateIndex = this->transitions[i][j];

			ostream << "\t("
				<< state->getName() << ", "
				<< this->alphabet[j] << ") -> "
				<< this->states[nextStateIndex]->getName()
				<< "\n";

		}
	}

	return ostream;
}

template<typename T>
std::istream& DeterminateFiniteAutomata<T>::read(std::istream& istream) {
	bool isReadingFromFile = false;

	if (typeid(istream) != typeid(std::cin)) {
		isReadingFromFile = true;
		std::cout << "Четене от файл ... " << std::endl << std::endl;
	}

	initStates(istream, isReadingFromFile);
	initBeginningState(istream, isReadingFromFile);
	initFinalState(istream, isReadingFromFile);
	initAlphabet(istream, isReadingFromFile);
	initTransitions(istream, isReadingFromFile);

	return istream;
}

template<typename T>
void DeterminateFiniteAutomata<T>::initStates(std::istream& istream, bool isReadingFromfile) {
	print("Посочете броя на състоянията: ", isReadingFromfile);
	istream >> this->statesCount;
	istream.ignore();

	print("Посочете всяко състояние: \n", isReadingFromfile);
	this->states = new State * [this->statesCount];

	for (unsigned i = 0; i < this->statesCount; i++) {
		states[i] = new State();
		print("Състояние [", isReadingFromfile);
		print(i + 1, isReadingFromfile);
		print("]: ", isReadingFromfile);
		istream >> *states[i];
		states[i]->setIndex(i);
	}
}

template<typename T>
void DeterminateFiniteAutomata<T>::initBeginningState(std::istream& istream, bool isReadingFromFile) {
	print("Посочете началното състояние: ", isReadingFromFile);
	istream.ignore();
	char* stateName = new char[51];
	istream.getline(stateName, 50);

	State* state = findState(stateName);

	if (state == nullptr) {
		std::cout << "Посоченото състояние не съществува: " << stateName << std::endl;
		//throw AutomatonStateException("Посоченото състояние не съществува: ", stateName);
	}

	state->setIsBeginningState(true);
	this->setBeginningState(state);
}

template<typename T>
void DeterminateFiniteAutomata<T>::initFinalState(std::istream& istream, bool isReadingFromFile) {
	print("Посочете броя на крайните състояния: ", isReadingFromFile);
	int numberOfFinalStates;
	istream >> numberOfFinalStates;

	for (int i = 0; i < numberOfFinalStates; i++) {
		char* stateName = new char[50];
		istream >> stateName;

		State* state = findState(stateName);

		if (state == nullptr) {
			std::cout << "Посоченото състояние нe съществува: " << stateName << std::endl;
			//throw AutomatonStateException("Посоченото състояние не съществува: ", stateName);
		}

		state->setIsFinalState(true);
	}

}

template<typename T>
void DeterminateFiniteAutomata<T>::initAlphabet(std::istream& istream, bool isReadingFromFile) {
	print("Посочете броя на символите в азбуката: ", isReadingFromFile);
	istream >> this->alphabetCount;
	istream.ignore();

	print("Посочете всеки символ в азбуката: \n", isReadingFromFile);

	this->alphabet = new T[this->alphabetCount];
	for (unsigned i = 0; i < this->alphabetCount; i++) {
		print("Символ [", isReadingFromFile);
		print(i + 1, isReadingFromFile);
		print("]: ", isReadingFromFile);

		istream >> alphabet[i];
	}
}

template<typename T>
void DeterminateFiniteAutomata<T>::initTransitions(std::istream& istream, bool isReadingFromFile) {
	print("Посочете преходите:\n", isReadingFromFile);
	istream.ignore();

	this->transitions = new int* [this->statesCount];

	for (int i = 0; i < this->statesCount; i++) {

		this->transitions[i] = new int[this->alphabetCount];
		State* state = this->states[i];

		for (int j = 0; j < this->alphabetCount; j++) {
			int symbol = this->alphabet[j];

			print("(", isReadingFromFile);
			print(state->getName(), isReadingFromFile);
			print(", ", isReadingFromFile);
			print(symbol, isReadingFromFile);
			print(") -> ", isReadingFromFile);

			char* stateName = new char[50];
			istream >> stateName;

			State* foundState = findState(stateName);
			if (foundState == nullptr) {
				std::cout << "Посоченoто състояние не съществува: " << stateName << std::endl;
				//throw AutomatonStateException("Посоченото състояние не съществува: ", stateName);
			}

			this->transitions[i][j] = foundState->getIndex();
			delete[] stateName;
		}
	}
}

template<typename T>
void DeterminateFiniteAutomata<T>::print(char* message, bool isReadingFromFile) {
	if (!isReadingFromFile) {
		std::cout << message;
	}
}

template<typename T>
void DeterminateFiniteAutomata<T>::print(int message, bool isReadingFromFile) {
	if (!isReadingFromFile) {
		std::cout << message;
	}
}

template<typename T>
unsigned int DeterminateFiniteAutomata<T>::getStatesCount() const {
	return statesCount;
}

template<typename T>
void DeterminateFiniteAutomata<T>::setStatesCount(unsigned int statesCount) {
	DeterminateFiniteAutomata<T>::statesCount = statesCount;
}

template<typename T>
State** DeterminateFiniteAutomata<T>::getStates() const {
	return states;
}

template<typename T>
void DeterminateFiniteAutomata<T>::setStates(State** states) {
	DeterminateFiniteAutomata<T>::states = states;
}

template<typename T>
State* DeterminateFiniteAutomata<T>::getBeginningState() const {
	return beginningState;
}

template<typename T>
void DeterminateFiniteAutomata<T>::setBeginningState(State* beginningState) {
	DeterminateFiniteAutomata<T>::beginningState = beginningState;
}

template<typename T>
State* DeterminateFiniteAutomata<T>::findState(char* stateName) {
	for (int i = 0; i < this->statesCount; i++) {
		if (strcmp(this->states[i]->getName(), stateName) == 0) {
			return this->states[i];
		}
	}
	return nullptr;
}

template<typename T>
int DeterminateFiniteAutomata<T>::findStateIndex(State** states, unsigned statesCount, char* stateName) {
	for (int i = 0; i < statesCount; i++) {
		if (strcmp(states[i]->getName(), stateName) == 0) {
			return i;
		}
	}
	return -1;
}

template<typename T>
bool DeterminateFiniteAutomata<T>::unionPredicate(State* state1, State* state2) {
	return state1->getIsFinalState() || state2->getIsFinalState();
}

template<typename T>
bool DeterminateFiniteAutomata<T>::intersectionPredicate(State* state1, State* state2) {
	return state1->getIsFinalState() && state2->getIsFinalState();
}

template
class DeterminateFiniteAutomata<int>;

template
class DeterminateFiniteAutomata<char>;