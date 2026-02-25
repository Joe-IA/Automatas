#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"
#include "streams.h"


void Automata::printAlphabet(std::ostream & os){
    os << "Alphabet: {";
    for(auto it = alphabet.begin(); it != alphabet.end(); ++it){
        os << *it;
        if(next(it) != alphabet.end())
            os << ", ";
    }
    os << "}\n";
}

void Automata::printTransitions(std::ostream & os){
    os << "δ: {\n";
    for(const auto &pair: transitions){
        std::string key = pair.first;
        for(const auto &stateChangePair: transitions[key]){
            char input = stateChangePair.first;
            for(const std::string &newState: stateChangePair.second){
                os << "T: (" << key << ", " << input << ") = " << newState << "\n";
            }
        }
    }
    os << "}\n";
}

void Automata::describeAutomata(std::ostream & os){
    printStates(states, "Q", os);
    printAlphabet(os);
    printTransitions(os);
    os << "s: " << initialState << "\n";
    printStates(finalStates, "F", os);
}

std::string Automata::carryOutTransition(std::string currentState, char input){
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



std::vector<std::string> Automata::acceptWord(std::string word){
    std::string currentState = initialState, nextState, currentString = "", finalExplanation = "";
    bool error = false;
    std::vector<std::string> visitedNodes;
    std::cout << "Estado inicial: " << currentState << "\n";
    std::cout << "Analizar cadena: " << word << "\n";
    std::cout << "-----\n";
    visitedNodes.push_back(currentState);
    for(const char &c: word){
        nextState = carryOutTransition(currentState, c);
        std::cout << "Estado actual: " << currentState << "\n";
        std::cout << "Entrada: " << c << "\n";
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
        std::cout << "Estado Destino: " << nextState << "\n";
        currentState = nextState;
        visitedNodes.push_back(currentState);
        currentString.push_back(c);
        std::cout << "Cadena Actual: " << currentString << "\n";
        std::cout << "----\n";
    }
    std::cout << "-----\n";
    if(!error){
        if(finalStates.find(currentState) != finalStates.end()){
            finalExplanation = currentState + " es un estado final: Cadena aceptada";
        }
        else{
            finalExplanation = currentState + " no es un estado final: Cadena Rechazada";
        }
    }
    std::cout << "Cadena: " << '"' << word << '"' << " analizada, " << finalExplanation << "\n";
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

std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>> Automata::findAmbiguousTransitions(){
    std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>> ambiguosTransitions;
    std::pair<std::string, char> innerPair;
    for(const auto &[key, value]: transitions){
        for(const auto &[input, trans]: transitions.find(key)->second){
            innerPair = {key, input};
            if(transitions.size() > 1)  
            ambiguosTransitions.push_back({innerPair, trans});
        }
    }
    return ambiguosTransitions;
}

void Automata::printStates(std::set<std::string> statesSet, std::string stateType, std::ostream & os){
    os << stateType << ":  {";
    for(auto it = statesSet.begin(); it != statesSet.end(); ++it){
        os << *it;
        if(next(it) != statesSet.end())
            os << ", ";
    }
    os << "}\n";
}

void Automata::modifyInitialState(){
    std::string state;
    std::cout << "Ingresa el nuevo estado inicial: ";
    std::cin >> state;
    std::cin.ignore();
    if(isValidState(state))
        Automata::initialState = state;
    else
        throw std::runtime_error("El estado no es un estado valido");
    
}

void Automata::addFinalState(){
    std::string state;
    std::cout << "Ingrese el nuevo estado final: ";
    std::cin >> state;
    std::cin.ignore();
    if(isValidState(state))
        Automata::finalStates.insert(state);
    else
        throw std::runtime_error("El estado no es un estado valido");
}

void Automata::addSymboltoAlphabet(){
    char symbol;
    std::cout << "Ingrese el nuevo simbolo: ";
    std::cin >> symbol;
    std::cin.ignore();
    Automata::alphabet.insert(symbol);
}

bool Automata::isValidState(std::string state){
    if(Automata::states.find(state) == Automata::states.end())
        return false;
    return true;
}

bool Automata::isValidFinalState(std::string state){
    if(Automata::finalStates.find(state) == Automata::finalStates.end())
        return false;
    return true;
}

void Automata::deleteFinalState(){
    std::string state;
    std::cout << "Ingrese el estado final a eliminar: ";
    std::cin >> state;
    std::cin.ignore();
    if(isValidFinalState(state))
        Automata::finalStates.erase(state);
    else
        throw std::runtime_error("El estado no es un estado final");
}

void Automata::addTransition(){
    std::string line;
    std::vector<std::string> arr;
    std::cout << "Inserte transicion:\n";
    std::getline(std::cin, line);
    std::pair<std::string, char> pair = cleanTransitionInput(line);
    std::string newState = line.substr(line.find("=") + 2);
    if(Automata::transitions.find(pair.first) == Automata::transitions.end()){
        arr.push_back(newState);
        Automata::transitions.insert({pair.first, {{pair.second, arr}}});
        arr.clear();
    }
    else if(Automata::transitions.find(pair.first)->second.find(pair.second) == Automata::transitions.find(pair.first)->second.end()){
        arr.push_back(newState);
        Automata::transitions.find(pair.first)->second.insert({pair.second, arr});
        arr.clear();
    }
    else{
        Automata::transitions.find(pair.first)->second.find(pair.second)->second.push_back(newState);
    }
}

void Automata_Manager::setFiles(){
    std::string content = readFile("Automata_manager.txt");
    Automata_Manager::files = splitlines(content);
}

void Automata_Manager::saveFiles(){
    std::string contents  = "";
    for(const std::string &file : Automata_Manager::files){
        contents += file;
        contents.push_back('\n');
    }
    savetoFile(contents, "Automata_manager.txt");
}

void Automata_Manager::showFiles(){
    for(const std::string &file: Automata_Manager::files){
        std::cout << file << "\n";
    }
}