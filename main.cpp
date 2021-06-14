#include <iostream>
#include "DeterminateFiniteAutomata.h"
#include "DeterminateFiniteAutomataInt.h"
#include "DeterminateFiniteAutomataChar.h"
#include <locale>
#include <fstream>

using namespace std;

void union_intersection() {
    locale::global(locale("Bulgarian"));
    DeterminateFiniteAutomata<char>* intAutomata1 = new DeterminateFiniteAutomataChar();
    DeterminateFiniteAutomata<char>* intAutomata2 = new DeterminateFiniteAutomataChar();
  
    ifstream automata1InputStream(
        "/users/x/source/repos/DFA_TextFile/Input/DFA_TestInt(1).txt");

    ifstream automata2InputStream(
        "/users/x/source/repos/DFA_TextFile/Input/DFA_TestInt(2).txt");

    try {
        automata1InputStream >> *intAutomata1;
        automata2InputStream >> *intAutomata2;
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
        return;
    }

    cout << "\t\tАвтомат 1: " << endl;
    cout << *intAutomata1 << endl;
    cout << endl << "\t\tAвтомат 2: " << endl;
    cout << *intAutomata2 << endl;

    DeterminateFiniteAutomata<char>* unionAutomata = (*intAutomata1) | (*intAutomata2);
    DeterminateFiniteAutomata<char>* intersectionAutomata = (*intAutomata1) & (*intAutomata2);

    cout << "\t\tОбединение: " << endl;
    cout << *unionAutomata << endl;
    cout << endl << "\t\tПресичане: " << endl;
    cout << *intersectionAutomata << endl;
}

int main() {

    DeterminateFiniteAutomata<char>* charAutomata = new DeterminateFiniteAutomataChar();
    DeterminateFiniteAutomata<int>* intAutomata = new DeterminateFiniteAutomataInt();

    ifstream charAutomataFile(
        "/users/x/source/repos/DFA_TextFile/Input/DFA_CHAR.txt");
    ifstream intAutomataFile(
        "/users/x/source/repos/DFA_TextFile/Input/DFA_INT.txt");

    try {
        charAutomataFile >> *charAutomata;
        intAutomataFile >> *intAutomata;

    }
    catch (std::exception& e) {
        cout << e.what() << endl;
        return -1;
    }

    char* word = new char[50];

    cout << "Моля въведете дума: ";
    while (cin >> word) {
        try {
            bool isRecognized = (*intAutomata).process(word);
            cout << word << " е " << (isRecognized ? "[ПРИЕТА]" : "[ОТХВЪРЛЕНА]") << endl;
        }
        catch (std::exception& e) {
            cout << e.what() << endl;
            cout << "Моля, опитайте с друга дума." << endl;
        }
        cout << endl << "Въведете думата тук: ";
    }

    return 0;
}