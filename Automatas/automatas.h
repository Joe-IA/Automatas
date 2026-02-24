#ifndef AUTOMATAS_H
#define AUTOMATAS_H

#include <utility>
#include <string>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Automata{
    set<string> states;
    set<string> finalStates;
    string initialState;
    set<char> alphabet;
    unordered_map<string, unordered_map<char, vector<string>>> transitions;

    void printTransitions();
    void printAlphabet();
    void describeAutomata();
    string carryOutTransition(string currentState, char input);
    bool isAutomataND();
    vector<pair<pair<string, char>, vector<string>>> findAmbiguousTransitions();
    vector<string> acceptWord(string word);
};

#endif