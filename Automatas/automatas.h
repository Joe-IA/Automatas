#ifndef AUTOMATAS_H
#define AUTOMATAS_H

#include <utility>
#include <string>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>


struct Automata{
    std::set<std::string> states;
    std::set<std::string> finalStates;
    std::string initialState;
    std::set<char> alphabet;
    std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions;

    void printTransitions();
    void printAlphabet();
    void describeAutomata();
    std::string carryOutTransition(std::string currentState, char input);
    bool isAutomataND();
    std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>> findAmbiguousTransitions();
    std::vector<std::string> acceptWord(std::string word);
    void printStates(std::set<std::string> statesSet, std::string stateType);
};

#endif