#include <set>
#include <string>
#include <iostream>
#include "automataCreator.h"
#include "streams.h"

Automata buildAutomataFromTerminal(){
    Automata automata;

    std::string nodes, input = "";
    std::cout << "Creando automata...\n";
    std::cout << "Ingresar estados: \n";
    automata.states = getStates();
    std::cout << "Ingresar alfabeto:\n";
    automata.alphabet = getAlphabet();
    std::cout << "Ingresar nodo inicial s: \n";
    std::cin >> automata.initialState;
    std::cin.ignore();
    std::cout << "Ingresar nodo(s) finales: \n";
    automata.finalStates = getStates();
    do {
        std::cout << "Ingresar transición: \n";
        std::pair<std::string, std::unordered_map<char, std::vector<std::string>>> transition = getTransition();
        automata.transitions.insert({{transition.first, transition.second}});
        std::cout << "Transición registrada, ¿Ingresar otra transición? (y | n): ";
        std::cin >> input;
        std::cin.ignore();
        if(input == "n")
            break;
    } while(true);
    return automata;
}

Automata buildAutomataFromFile(){
    Automata automata;
    return automata;
}

std::set<std::string> getStates(){
    std::string states;
    std::getline(std::cin, states);
    std::vector<std::string> statesList = cleanCSInput(states);
    std::set<std::string> statesSet(statesList.begin(), statesList.end());
    return statesSet;    
}

std::pair<std::string, std::unordered_map<char, std::vector<std::string>>> getTransition(){
    std::pair<std::string, std::unordered_map<char, std::vector<std::string>>> output;
    std::string transition;
    std::getline(std::cin, transition);
    std::pair<std::string, char> input = cleanTransitionInput(transition);
    std::string substring = transition.substr(transition.find("=") + 2);
    std::vector<std::string> transitionsList = cleanCSInput(substring);
    std::unordered_map<char, std::vector<std::string>> map = {{input.second, transitionsList}};
    return {input.first, map};
}

std::set<char> getAlphabet(){
    std::set<char> alphabet;
    std::vector<std::string> separatedValues;
    std::string input;
    std::getline(std::cin, input);
    separatedValues = cleanCSInput(input);
    for(const std::string &symbol : separatedValues){
        alphabet.insert(symbol[0]);
    }
    return alphabet;

}