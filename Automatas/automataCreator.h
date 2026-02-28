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

Automata buildAutomataFromFile(std::string fileName);
Automata buildAutomataFromTerminal();
std::set<std::string> getStates();
std::tuple<std::string, char, std::vector<std::string>> getTransition();
std::set<char> getAlphabet();
std::set<std::string> buildStateSet(std::string stateString);
std::set<char> buildAlphabetSet(std::string alphabetString);
std::pair<TransitionMap, size_t> buildTransitionMap(size_t counter, std::vector<std::string> lines);
void insertTransitiontoMap(TransitionMap &transitions, std::pair<std::string, char> pair, std::vector<std::string> newState);
#endif