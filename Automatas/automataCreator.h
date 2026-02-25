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

Automata buildAutomataFromFile();
Automata buildAutomataFromTerminal();
std::set<std::string> getStates();
std::pair<std::string, std::unordered_map<char, std::vector<std::string>>> getTransition();
std::set<char> getAlphabet();
#endif