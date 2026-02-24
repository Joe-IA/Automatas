#ifndef DISPLAY_H
#define DISPLAY_H

#include <utility>
#include <string>
#include <set>
#include <string>
#include <vector>
using namespace std;

void printStates(set<string> statesSet, string stateType);
pair<string, char> cleanTransitionInput(string input);
void printVisitedNodes(vector<string> nodes);
void printAmbiguousTransitions(vector<pair<pair<string, char>, vector<string>>>transitions);

#endif