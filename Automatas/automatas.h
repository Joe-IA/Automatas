#ifndef AUTOMATAS_H
#define AUTOMATAS_H

#include <utility>
#include <string>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

typedef std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> TransitionMap;

struct Automata{
    std::set<std::string> states;
    std::set<std::string> finalStates;
    std::string initialState;
    std::set<char> alphabet;
    TransitionMap transitions;

    void printTransitions(std::ostream & os);
    void printAlphabet(std::ostream & os);
    void describeAutomata(std::ostream & os);
    std::string carryOutTransition(std::string currentState, char input);
    bool isAutomataND();
    std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>> findAmbiguousTransitions();
    std::vector<std::string> acceptWord(std::string word);
    void printStates(std::set<std::string> statesSet, std::string stateType, std::ostream & os);
    void addTransition();
    void modifyInitialState();
    void addFinalState();
    void deleteFinalState();
    void addSymboltoAlphabet();
    bool isValidState(std::string state);
    bool isValidFinalState(std::string state);
};

struct Automata_Manager{
    std::vector<std::string> files;
    void setFiles();
    void saveFiles();
    void showFiles();
};

#endif