#ifndef STREAMS_H
#define STREAMS_H

#include <utility>
#include <string>
#include <set>
#include <string>
#include <vector>
#include "automatas.h"

std::pair<std::string, char> cleanTransitionInput(std::string input);
std::vector<std::string> cleanCSInput(std::string input);
std::string cleansetNotation(std::string input);
void printVisitedNodes(std::vector<std::string> nodes);
void printAmbiguousTransitions(std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>>transitions);
std::string readFile(std::string name);
void saveAutomatatoFile(Automata &automata, std::string ouputFile);
std::vector<std::string> splitlines(const std::string &text);
void savetoFile(std::string content, std::string outputFile);
void printModifyAutomataMenu();
std::string cleanParentheses(std::string input);
void printStepHeader();
std::string stackToString(std::stack<char> stk);
std::tuple<std::string, char, std::string, char,  tapeDirection> cleanTMTransition(const std::string &input);
void printTape(const std::vector<char> &tape, size_t currentIndex, std::string currentState);

#endif