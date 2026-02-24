#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"
#include "display.h"
using namespace std;

void Automata::printAlphabet(){
    cout << "Alphabet: {";
    for(auto it = alphabet.begin(); it != alphabet.end(); ++it){
        cout << *it;
        if(next(it) != alphabet.end())
            cout << ", ";
    }
    cout << "}\n";
}

void Automata::printTransitions(){
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

void Automata::describeAutomata(){
    printStates(states, "Q");
    printAlphabet();
    printTransitions();
    cout << "s: " << initialState << "\n";
    printStates(finalStates, "F");
}

string Automata::carryOutTransition(string currentState, char input){
        if(isAutomataND())
            return "No deterministic automata";
        
        auto it = transitions.find(currentState);
        if(it == transitions.end())
            return "Non existing transition";
        auto pair = *it;
        auto it_ = pair.second.find(input);
        if (it_ == pair.second.end())
            return "Non existing transition";
        return it_->second.at(0);
}



vector<string> Automata::acceptWord(string word){
    string currentState = initialState, nextState, currentString = "", finalExplanation = "";
    bool error = false;
    vector<string> visitedNodes;
    cout << "Estado inicial: " << currentState << "\n";
    cout << "Analizar cadena: " << word << "\n";
    cout << "-----\n";
    visitedNodes.push_back(currentState);
    for(const char &c: word){
        nextState = carryOutTransition(currentState, c);
        cout << "Estado actual: " << currentState << "\n";
        cout << "Entrada: " << c << "\n";
        if(alphabet.find(c) == alphabet.end()){
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
        if(finalStates.find(currentState) != finalStates.end()){
            finalExplanation = currentState + " es un estado final: Cadena aceptada";
        }
        else{
            finalExplanation = currentState + " no es un estado final: Cadena Rechazada";
        }
    }
    cout << "Cadena: " << '"' << word << '"' << " analizada, " << finalExplanation << "\n";
    return visitedNodes;
}

bool Automata::isAutomataND(){
    for(const auto &[key, value]: transitions){
        for(const auto &[state, transition]: transitions.find(key)->second){
            if(transition.size() > 1)
                return true;
        }
    }
    return false;
}

vector<pair<pair<string, char>, vector<string>>> Automata::findAmbiguousTransitions(){
    vector<pair<pair<string, char>, vector<string>>> ambiguosTransitions;
    pair<string, char> innerPair;
    for(const auto &[key, value]: transitions){
        for(const auto &[input, trans]: transitions.find(key)->second){
            innerPair = {key, input};
            if(transitions.size() > 1)  
            ambiguosTransitions.push_back({innerPair, trans});
        }
    }
    return ambiguosTransitions;
}

