#include <utility>
#include <string>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include "display.h"
using namespace std;

void printStates(set<string> statesSet, string stateType){
    cout << stateType << ":  {";
    for(auto it = statesSet.begin(); it != statesSet.end(); ++it){
        cout << *it;
        if(next(it) != statesSet.end())
            cout << ", ";
    }
    cout << "}\n";
}

pair<string, char> cleanTransitionInput(string input){
    size_t start = 2;
    size_t comma = input.find(",");

    string state = input.substr(start, comma - start);
    string symbol = input.substr(comma + 2);
    symbol.pop_back();
    if (symbol == "\" \""){
        symbol = " ";
    }
    pair<string, char> exit = {state, symbol[0]};
    return exit;
}

void printVisitedNodes(vector<string> nodes){
    cout << "Estados recorridos: \n";
    for (int i = 0; i < nodes.size(); ++i){
        cout << nodes[i];
        if(i < nodes.size() - 1)
            cout << " -> ";
    }
    cout << "\n";
}


void printAmbiguousTransitions(vector<pair<pair<string, char>, vector<string>>> transitions){
    for (const auto &ambState: transitions){
        string currentState = ambState.first.first;
        char input = ambState.first.second;
        vector<string> incomingStates = ambState.second;
        cout << "T(" << currentState << ", " << input << ") = {";
        for(auto it = incomingStates.begin(); it != incomingStates.end(); ++it){
            cout << *it;
            if(next(it) != incomingStates.end())
            cout << ", ";
        }
        cout << "}\n";
    }
}