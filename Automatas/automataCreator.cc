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
        auto [state, in, newStatesList] = getTransition();
        std::pair<std::string, char> pair = {state, in};
        insertTransitiontoMap(automata.transitions, pair, newStatesList);
        std::cout << "Transición registrada, ¿Ingresar otra transición? (y | n): ";
        std::cin >> input;
        std::cin.ignore();
        if(input == "n")
            break;
    } while(true);
    return automata;
}

Automata buildAutomataFromFile(std::string fileName){
    Automata automata;
    std::string fileContent = readFile(fileName);
    std::vector<std::string> lines = splitlines(fileContent);
    automata.states = buildStateSet(lines[0]);
    automata.alphabet = buildAlphabetSet(lines[1]);
    size_t counter = 3;
    auto [transitions, newCounter] = buildTransitionMap(counter, lines);
    automata.transitions = transitions;
    automata.initialState = lines[newCounter].substr(3);
    newCounter++;
    automata.finalStates = buildStateSet(lines[newCounter]);
    return automata;
}

std::set<std::string> getStates(){
    std::string states;
    std::getline(std::cin, states);
    std::vector<std::string> statesList = cleanCSInput(states);
    std::set<std::string> statesSet(statesList.begin(), statesList.end());
    return statesSet;    
}

std::tuple<std::string, char, std::vector<std::string>> getTransition(){
    std::string transition;
    std::getline(std::cin, transition);
    std::pair<std::string, char> input = cleanTransitionInput(transition);
    std::string substring = transition.substr(transition.find("=") + 2);
    std::vector<std::string> transitionsList = cleanCSInput(substring);
    return {input.first, input.second, transitionsList};
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

std::set<std::string> buildStateSet(std::string stateString){
    std::vector<std::string> stateList;
    stateString = cleansetNotation(stateString);
    stateList = cleanCSInput(stateString);
    std::set<std::string> stateSet(stateList.begin(), stateList.end());
    return stateSet;
}

std::set<char> buildAlphabetSet(std::string alphabetString){
    std::vector<std::string> alphabetList;
    std::set<char> alphabetSet;
    alphabetString = cleansetNotation(alphabetString);
    alphabetList = cleanCSInput(alphabetString);
    for(const std::string &str : alphabetList){
        alphabetSet.insert(str[0]);
    }
    return alphabetSet;
}

std::pair<TransitionMap, size_t> buildTransitionMap(size_t counter, std::vector<std::string> lines){
    TransitionMap transitions;
    while(lines[counter] != "}"){
        std::string currentLine = lines[counter];
        std::pair<std::string, char> pair = cleanTransitionInput(currentLine);
        std::string newState = currentLine.substr(currentLine.find("=") + 2);
        insertTransitiontoMap(transitions, pair, {newState});
        counter++;
    }
    counter++;
    return {transitions, counter};
}

void insertTransitiontoMap(TransitionMap &transitions, std::pair<std::string, char> pair, std::vector<std::string> newStates){
    if(transitions.find(pair.first) == transitions.end()){
        transitions.insert({pair.first, {{pair.second, newStates}}});
    }
    else if(transitions.find(pair.first)->second.find(pair.second) == transitions.find(pair.first)->second.end()){
        transitions.find(pair.first)->second.insert({pair.second, newStates});
    }
    else{
        for(const std::string newState: newStates){
            transitions.find(pair.first)->second.find(pair.second)->second.push_back(newState);
        }
    }
        
}