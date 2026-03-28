#ifndef AUTOMATA_CREATOR_H
#define AUTOMATA_CREATOR_H

#include <utility>
#include <string>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"

FSAutomata buildFSAutomataFromFile(std::string fileName);
FSAutomata buildFSAutomataFromTerminal();
StackAutomata buildStackAutomataFromTerminal();
StackAutomata buildStackAutomataFromFile(std::string fileName);
std::set<std::string> getStates();
std::tuple<std::string, char, std::vector<std::string>> getTransitionFS();
Transition getTransitionSA();
std::set<char> getAlphabet();
std::set<std::string> buildStateSet(std::string stateString);
std::set<char> buildAlphabetSet(std::string alphabetString);
std::pair<TransitionMap, size_t> buildTransitionMap(size_t counter, std::vector<std::string> lines);
void insertTransitiontoMap(TransitionMap &transitions, std::pair<std::string, char> pair, std::vector<std::string> newState);
std::vector<Transition> buildTransitionVector(uint8_t counter, std::vector<std::string> lines);
inline Transition createTransition(std::string input);
TuringMachine buildTMFromFile(std::string fileName);
std::vector<TMTransition> buildTMTransitionVector(size_t counter, std::vector<std::string> lines);
inline TMTransition createTMTransition(std::string input);

#endif