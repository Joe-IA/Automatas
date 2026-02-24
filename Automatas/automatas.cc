#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"
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


void printAlphabet(set<char> alphabet){
    cout << "Alphabet: {";
    for(auto it = alphabet.begin(); it != alphabet.end(); ++it){
        cout << *it;
        if(next(it) != alphabet.end())
            cout << ", ";
    }
    cout << "}\n";
}

void printTransitions(unordered_map<string, unordered_map<char, vector<string>>> transitions){
    cout << "δ: {\n";
    for(const auto &pair: transitions){
        string key = pair.first;
        for(const auto &stateChangePair: transitions[key]){
            char input = stateChangePair.first;
            for(const string &newState: stateChangePair.second){
                cout << "T: (" << key << ", " << input << ") = " << newState << "\n";
            }
        }
    }
    cout << "}\n";
}

void describeAutomata(Automata automata){
    printStates(automata.states, "Q");
    printAlphabet(automata.alphabet);
    printTransitions(automata.transitions);
    cout << "s: " << automata.initialState << "\n";
    printStates(automata.finalStates, "F");
}

string carryOutTransition(Automata automata, string currentState, char input){
        if(isAutomataND(automata))
            return "No deterministic automata";
        
        const auto transitions = automata.transitions;
        auto it = transitions.find(currentState);
        if(it == transitions.end())
            return "Non existing transition";
        auto pair = *it;
        auto it_ = pair.second.find(input);
        if (it_ == pair.second.end())
            return "Non existing transition";
        return it_->second.at(0);
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

vector<string> wordAccepter(Automata automata, string word){
    string currentState = automata.initialState, nextState, currentString = "", finalExplanation = "";
    bool error = false;
    vector<string> visitedNodes;
    cout << "Estado inicial: " << currentState << "\n";
    cout << "Analizar cadena: " << word << "\n";
    cout << "-----\n";
    visitedNodes.push_back(currentState);
    for(const char &c: word){
        nextState = carryOutTransition(automata, currentState, c);
        cout << "Estado actual: " << currentState << "\n";
        cout << "Entrada: " << c << "\n";
        if(automata.alphabet.find(c) == automata.alphabet.end()){
            finalExplanation = "Alfabeto no reconocido: Cadena rechazada";
            error = true;
            break;
        }
        if(nextState == "Non existing transition"){
            finalExplanation = "Transicion invalida: cadena rechazada";
            error = true;
            break;
        }
        cout << "Estado Destino: " << nextState << "\n";
        currentState = nextState;
        visitedNodes.push_back(currentState);
        currentString.push_back(c);
        cout << "Cadena Actual: " << currentString << "\n";
        cout << "----\n";
    }
    cout << "-----\n";
    if(!error){
        if(automata.finalStates.find(currentState) != automata.finalStates.end()){
            finalExplanation = currentState + " es un estado final: Cadena aceptada";
        }
        else{
            finalExplanation = currentState + " no es un estado final: Cadena Rechazada";
        }
    }
    cout << "Cadena: " << '"' << word << '"' << " analizada, " << finalExplanation << "\n";
    return visitedNodes;
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
bool isAutomataND(Automata automata){
    const auto transitions = automata.transitions;
    for(const auto &[key, value]: transitions){
        for(const auto &[state, transition]: transitions.find(key)->second){
            if(transition.size() > 1)
                return true;
        }
    }
    return false;
}

vector<pair<pair<string, char>, vector<string>>> findAmbiguousTransitions(Automata automata){
    vector<pair<pair<string, char>, vector<string>>> ambiguosTransitions;
    pair<string, char> innerPair;
    vector<string> trans;
    const auto automataTransitions = automata.transitions;
    for(const auto &[key, value]: automataTransitions){
        for(const auto &[input, transitions]: automataTransitions.find(key)->second){
            innerPair = {key, input};
            if(transitions.size() > 1)  
            ambiguosTransitions.push_back({innerPair, transitions});
            
        }
    }
    return ambiguosTransitions;
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