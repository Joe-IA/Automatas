#include <set>
#include <string>
#include <iostream>
#include "automataCreator.h"
#include "streams.h"


FSAutomata buildFSAutomataFromTerminal(){
    FSAutomata automata;

    std::string nodes, input = "";
    std::cout << "Creando automata...\n";
    std::cout << "Ingresar estados: \n";
    automata.setStates(getStates());
    std::cout << "Ingresar alfabeto:\n";
    automata.setAlphabet(getAlphabet());
    std::cout << "Ingresar nodo inicial s: \n";
    std::cin >> input;
    std::cin.ignore();
    automata.setInitialState(input);
    std::cout << "Ingresar nodo(s) finales: \n";
    automata.setFinalStates(getStates());
    do {
        std::cout << "Ingresar transición: \n";
        auto [state, in, newStatesList] = getTransitionFS();
        std::pair<std::string, char> pair = {state, in};
        insertTransitiontoMap(automata.getTransitions(), pair, newStatesList);
        std::cout << "Transición registrada, ¿Ingresar otra transición? (y | n): ";
        std::cin >> input;
        std::cin.ignore();
    } while(input != "n");
    return automata;
}

FSAutomata buildFSAutomataFromFile(std::string fileName){
    FSAutomata automata;
    std::string fileContent = readFile(fileName);
    std::vector<std::string> lines = splitlines(fileContent);
    automata.setStates(buildStateSet(lines[0]));
    automata.setAlphabet(buildAlphabetSet(lines[1]));
    size_t counter = 3;
    auto [transitions, newCounter] = buildTransitionMap(counter, lines);
    automata.setTransitions(transitions);
    automata.setInitialState(lines[newCounter].substr(3));
    newCounter++;
    automata.setFinalStates(buildStateSet(lines[newCounter]));
    return automata;
}

std::set<std::string> getStates(){
    std::string states;
    std::getline(std::cin, states);
    std::vector<std::string> statesList = cleanCSInput(states);
    std::set<std::string> statesSet(statesList.begin(), statesList.end());
    return statesSet;
}

std::tuple<std::string, char, std::vector<std::string>> getTransitionFS(){
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

StackAutomata buildStackAutomataFromFile(std::string fileName){
    StackAutomata automata;
    std::string fileContent = readFile(fileName);
    std::vector<std::string> lines = splitlines(fileContent);
    automata.setAlphabet(buildAlphabetSet(lines[0]));
    automata.setStackAlphabet(buildAlphabetSet(lines[1]));
    automata.setStates(buildStateSet(lines[2]));
    automata.setStackSymbol(lines[3].substr(4)[0]);
    automata.setInitialState(lines[4].substr(3));
    automata.setFinalStates(buildStateSet(lines[5]));
    automata.setTransitions(buildTransitionVector(6, lines));
    return automata;
}

StackAutomata buildStackAutomataFromTerminal(){
    StackAutomata automata;
    std::string nodes, input;
    std::cout << "Creando automata de pila... \n";
    std::cout << "Ingresar estados: \n";
    automata.setStates(getStates());
    std::cout << "Ingresar alfabeto: \n";
    automata.setAlphabet(getAlphabet());
    std::cout << "Ingresar alfabeto de pila: \n";
    automata.setStackAlphabet(getAlphabet());
    std::cout << "Ingresar simbolo de pila: ";
    std::cin >> input;
    automata.setStackSymbol(input[0]);
    std::cin.ignore();
    std::cout << "Ingresar estado inicial: ";
    std::cin >> input;
    std::cin.ignore();
    automata.setInitialState(input);
    std::cout << "Ingresar estados finales:\n";
    automata.setFinalStates(getStates());
    do{
        std::cout << "Ingresar transición: \n";
        automata.getTransitions().push_back(getTransitionSA());
        std::cout << "Transición registrada, ¿Ingresar otra transición? (y | n): ";
        std::cin >> input;
        std::cin.ignore();
    } while(input != "n");
    return automata;
}

Transition getTransitionSA(){
    std::string transition;
    std::getline(std::cin, transition);
    return createTransition(transition);
}

std::vector<Transition> buildTransitionVector(uint8_t counter, std::vector<std::string> lines){
    std::vector<Transition> transitions;
    StackOp op;
    size_t space_pos;
    std::string command, value;
    while(++counter < lines.size() && lines[counter] != "}"){
        transitions.push_back(createTransition(lines[counter]));
    }
    return transitions;
}

inline Transition createTransition(std::string input){
    std::string command, value;
    StackOp op;
    input = cleanParentheses(input);
    std::vector<std::string> tP = cleanCSInput(input);
    size_t space_pos = tP[3].find(' ');
    if(space_pos == std::string::npos){
        command = tP[3];
        value = '\0';
    }
    else{
        command = tP[3].substr(0, space_pos);
        value = tP[3].substr(space_pos + 1);
    }
    if(command == "PUSH")
        op = StackOp::PUSH;
    else if(command == "POP")
        op = StackOp::POP;
    else if(command == "NOP")
        op = StackOp::NOP;
    return {tP[0], tP[1][0], tP[2][0], op, value[0],tP[4]};
}

TuringMachine buildTMFromFile(std::string fileName){
    TuringMachine machine;
    std::string fileContent = readFile(fileName);
    std::vector<std::string> lines = splitlines(fileContent);
    machine.setInputAlphabet(buildAlphabetSet(lines[0]));
    machine.setAlphabet(buildAlphabetSet(lines[1]));
    machine.setStates(buildStateSet(lines[2]));
    machine.setInitialState(lines[4].substr(3));
    machine.setNullChar(lines[3].substr(3)[0]);
    machine.setFinalStates(buildStateSet(lines[5]));
    machine.setTransitions(buildTMTransitionVector(6, lines));
    return machine;
}

std::vector<TMTransition> buildTMTransitionVector(size_t counter, std::vector<std::string> lines){
    std::vector<TMTransition> transitions;
    while(lines[++counter] != "}"){
        transitions.push_back(createTMTransition(lines[counter]));
    }
    return transitions;
}

inline TMTransition createTMTransition(std::string input){
    TMTransition transition;
    auto [initialState, in, newState, _2BWritten, dir] = cleanTMTransition(input);
    transition = {initialState, in, newState, _2BWritten, dir};
    return transition;
}