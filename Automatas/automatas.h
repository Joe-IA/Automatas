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
};

void printStates(set<string> statesSet, string stateType);
void printAlphabet(set<char> alphabet);
void printTransitions(unordered_map<string, unordered_map<char, vector<string>>> transitions);
void describeAutomata(Automata Automata);
string carryOutTransition(Automata automata, string currentState, char input);
pair<string, char> cleanTransitionInput(string input);
vector<string> wordAccepter(Automata automata, string word);
void printVisitedNodes(vector<string> nodes);
bool isAutomataND(Automata automata);
vector<pair<pair<string, char>, vector<string>>> findAmbiguousTransitions(Automata automata);
void printAmbiguousTransitions(vector<pair<pair<string, char>, vector<string>>>transitions);

#endif