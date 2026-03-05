#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <queue>
#include <vector>
#include "automatas.h"
#include "automataCreator.h"
#include "streams.h"
#include "generateChains.h"


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

std::vector<std::string> Automata::carryOutTransition(std::string currentState, char input){
    auto it = transitions.find(currentState);
    if(it == transitions.end())
        return {};

    auto it_ = it->second.find(input);
    if(it_ == it->second.end())
        return {};

    return it_->second;
}


void Automata::acceptWord(std::string word){
    std::string currentState = initialState;
    std::string currentString = "", finalExplanation = "";
    bool error = false;

    std::vector<std::string> visitedNodes;
    std::vector<std::string> nextStates;

    std::cout << "Analizar cadena: " << word << "\n";

    visitedNodes.push_back(currentState);

    for(const char &c : word){

        currentString.push_back(c);
        std::cout << currentString << ":\n";

        if(alphabet.find(c) == alphabet.end()){
            finalExplanation = "Alfabeto no reconocido: Cadena rechazada";
            error = true;
            break;
        }

        nextStates = carryOutTransition(currentState, c);

        if(nextStates.empty()){
            finalExplanation = "Transicion invalida: cadena rechazada";
            error = true;
            break;
        }
        if(nextStates.size() > 1){
            for(const auto &state : nextStates){
                std::cout << currentState << "->" << state << "\n";
            }
            std::cout << "\n";
        }

        std::string nextState = nextStates[0];

        currentState = nextState;
        visitedNodes.push_back(currentState);

        printVisitedNodes(visitedNodes);
    }

    if(!error){
        if(finalStates.find(currentState) != finalStates.end()){
            finalExplanation = currentState + " es un estado final: Cadena aceptada";
        }
        else{
            finalExplanation = currentState + " no es un estado final: Cadena Rechazada";
        }
    }

    std::cout << "Cadena: \"" << word << "\" analizada, " << finalExplanation << "\n";
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
            if(trans.size() > 1)  
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

void Automata::deleteTransition(){
    std::string input;
    std::cout << "Inserta transicion a eliminar:\n";
    std::getline(std::cin, input);
    std::pair<std::string, char> pair = cleanTransitionInput(input);
    std::string newState = input.substr(input.find("=") + 2);
    std::vector<std::string> &dic = Automata::transitions.find(pair.first)->second.find(pair.second)->second;
    dic.erase(std::remove(dic.begin(), dic.end(), newState), dic.end());
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


std::vector<std::string> Automata::generateWords(){
    std::unordered_map<std::string,int> visits;
    std::vector<std::string> results;
    for (auto& [state, trans] : transitions) {
        states.insert(state);

        for (auto& [c, nextStates] : trans) {
            for (auto& s : nextStates)
                states.insert(s);
        }
    }
    for (auto& s : states)
        visits[s] = 0;

    backtrack(
        Automata::initialState,
        Automata::transitions,
        visits,
        Automata::finalStates,
        "",
        results
    );

    return results;
}

void Automata::addTransition(){
    std::string line;
    std::cout << "Inserte transicion:\n";
    std::getline(std::cin, line);
    std::pair<std::string, char> pair = cleanTransitionInput(line);
    std::string newState = line.substr(line.find("=") + 2);
    insertTransitiontoMap(Automata::transitions, pair, {newState});
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