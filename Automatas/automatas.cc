#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <utility>
#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include <iomanip>
#include "automatas.h"
#include "automataCreator.h"
#include "streams.h"
#include "generateChains.h"

std::set<std::string> Automata::getStates(){
    return Automata::states;
}
void Automata::setStates(std::set<std::string> states){
    Automata::states = states;
}

std::set<std::string> Automata::getFinalStates(){
    return Automata::finalStates;
}
void Automata::setFinalStates(std::set<std::string> finalStates){
    Automata::finalStates = finalStates; 
}
std::string Automata::getInitialState(){
    return Automata::initialState; 
}
void Automata::setInitialState(std::string initialState){
    Automata::initialState = initialState;
}
std::set<char> Automata::getAlphabet(){
    return Automata::alphabet;
}
void Automata::setAlphabet(std::set<char> alphabet){
    Automata::alphabet = alphabet;
}

void Automata::printAlphabet(std::ostream & os){
    os << "Alphabet: {";
    for(auto it = alphabet.begin(); it != alphabet.end(); ++it){
        os << *it;
        if(next(it) != alphabet.end())
            os << ", ";
    }
    os << "}\n";
}

TransitionMap &FSAutomata::getTransitions(){
    return FSAutomata::transitions;
}

void FSAutomata::setTransitions(TransitionMap transitions){
    FSAutomata::transitions = transitions; 
}

void FSAutomata::printTransitions(std::ostream & os){
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

void FSAutomata::describeAutomata(std::ostream & os){
    printStates(states, "Q", os);
    printAlphabet(os);
    printTransitions(os);
    os << "s: " << initialState << "\n";
    printStates(finalStates, "F", os);
}

std::vector<std::string> FSAutomata::carryOutTransition(std::string currentState, char input){
    auto it = transitions.find(currentState);
    if(it == transitions.end())
        return {};

    auto it_ = it->second.find(input);
    if(it_ == it->second.end())
        return {};

    return it_->second;
}


void FSAutomata::acceptWord(std::string word) {
    std::cout << "Analizar cadena: " << word << "\n";

    std::vector<std::string> path;
    path.push_back(initialState);

    int furthestIndex = -1;
    std::string lastState;
    std::vector<std::string> bestPath;
    bool isaccepted = explore(initialState, word, 0, path, furthestIndex, lastState, bestPath);
    printWordConstruction(word, bestPath);

    if (!isaccepted) {
        std::cout << "\nResultado: Cadena rechazada.\n";
        std::cout << lastState << " no es un estado final\n";
    }
    else {
        std::cout << "Estado final alcanzado: " << lastState << "\n";
        std::cout << "Resultado: Cadena Aceptada!\n";
    }
}

bool FSAutomata::explore(std::string currentState,
                       const std::string& word,
                       int index,
                       std::vector<std::string>& path,
                       int& furthestIndex,
                       std::string& lastState,
                       std::vector<std::string>& bestPath) {

    if (index > furthestIndex) {
        furthestIndex = index;
        lastState = currentState;
        bestPath = path;
    }

    if (index == word.length()) {
        if (isValidFinalState(currentState)) 
            return true;
        
        return false;
    }

    char c = word[index];

    if (alphabet.find(c) == alphabet.end()) {
        std::cout << "Error: simbolo '" << c << "' no pertenece al alfabeto.\n";
        return false;
    }

    std::vector<std::string> nextStates = carryOutTransition(currentState, c);

    for (const std::string& nextState : nextStates) {

        path.push_back(nextState);

        if (explore(nextState, word, index + 1, path, furthestIndex, lastState, bestPath)) 
            return true;
        

        path.pop_back();
    }

    return false;
}

bool FSAutomata::isAutomataND(){
    for(const auto &[key, value]: transitions){
        for(const auto &[state, transition]: transitions.find(key)->second){
            if(transition.size() > 1)
                return true;
        }
    }
    return false;
}

std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>> FSAutomata::findAmbiguousTransitions(){
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

void FSAutomata::modifyInitialState(){
    std::string state;
    std::cout << "Ingresa el nuevo estado inicial: ";
    std::cin >> state;
    std::cin.ignore();
    if(isValidState(state))
        Automata::initialState = state;
    else
        throw std::runtime_error("El estado no es un estado valido");
    
}

void FSAutomata::addFinalState(){
    std::string state;
    std::cout << "Ingrese el nuevo estado final: ";
    std::cin >> state;
    std::cin.ignore();
    if(isValidState(state))
        Automata::finalStates.insert(state);
    else
        throw std::runtime_error("El estado no es un estado valido");
}

void FSAutomata::addSymboltoAlphabet(){
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

void FSAutomata::deleteTransition(){
    std::string input;
    std::cout << "Inserta transicion a eliminar:\n";
    std::getline(std::cin, input);
    std::pair<std::string, char> pair = cleanTransitionInput(input);
    std::string newState = input.substr(input.find("=") + 2);
    std::vector<std::string> &dic = FSAutomata::transitions.find(pair.first)->second.find(pair.second)->second;
    dic.erase(std::remove(dic.begin(), dic.end(), newState), dic.end());
}

void FSAutomata::deleteFinalState(){
    std::string state;
    std::cout << "Ingrese el estado final a eliminar: ";
    std::cin >> state;
    std::cin.ignore();
    if(isValidFinalState(state))
        Automata::finalStates.erase(state);
    else
        throw std::runtime_error("El estado no es un estado final");
}


std::vector<std::string> FSAutomata::generateWords(){
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
        FSAutomata::initialState,
        FSAutomata::transitions,
        visits,
        FSAutomata::finalStates,
        "",
        results
    );

    return results;
}

void FSAutomata::addTransition(){
    std::string line;
    std::cout << "Inserte transicion:\n";
    std::getline(std::cin, line);
    std::pair<std::string, char> pair = cleanTransitionInput(line);
    std::string newState = line.substr(line.find("=") + 2);
    insertTransitiontoMap(FSAutomata::transitions, pair, {newState});
}

void FSAutomata::printWordConstruction(const std::string& word, const std::vector<std::string>& path){
        std::string partial = "";

    for (int i = 1; i < path.size(); i++) {

        partial += word[i - 1];
        char symbol = word[i - 1];

        std::string from = path[i - 1];
        std::string to = path[i];

        std::cout << "\n" << partial << ":\n";

        std::vector<std::string> possible = carryOutTransition(from, symbol);
        if (possible.size() > 1) {
            for (const auto& s : possible) {
                std::cout << from << "->" << s;
                std::cout << "\n";
            }

            continue;
        }

        for (int j = 0; j <= i; j++) {

            std::cout << path[j];

            if (j < i)
                std::cout << "->";
        }

        std::cout << "\n";
    }
}


void StackAutomata::printTransitions(std::ostream &os) {
    std::string sep = ", ", op;
    os << "δ: {\n";
    for(const auto &transition: StackAutomata::transitions){
        switch (transition.stackOperation)
        {
        case StackOp::PUSH:
            op = "PUSH";
            break;
        case StackOp::NOP:
            op = "NOP";
            break;
        case StackOp::POP:
            op = "POP";
            break;
        }
        os << "(" << transition.initialState << sep << transition.input << sep << transition.stackTop << sep << op;
        os << (transition.stackOperation == StackOp::PUSH ?  std::string(" ") + transition.pushSymbol : ""); 
        os << sep << transition.newState << ")\n";
    }
    os << "}\n";
}

std::set<char> StackAutomata::getStackAlphabet(){
    return StackAutomata::stackAlphabet;
}

void StackAutomata::setStackAlphabet(std::set<char> stackAlphabet){
    StackAutomata::stackAlphabet = stackAlphabet;
}

char StackAutomata::getStackSymbol(){
    return StackAutomata::stackSymbol;
}

void StackAutomata::setStackSymbol(char stackSymbol){
    StackAutomata::stackSymbol = stackSymbol;
}

std::vector<Transition> &StackAutomata::getTransitions(){
    return StackAutomata::transitions;
}

void StackAutomata::setTransitions(std::vector<Transition> transitions){
    StackAutomata::transitions = transitions;
}

void StackAutomata::describeAutomata(std::ostream &os){
    printAlphabet(os);
    printStackAlphabet(os);
    printStates(states, "Q", os);
    os << "A0: " <<  stackSymbol << "\n"; 
    os << "s: " << initialState << "\n";
    printStates(finalStates, "F", os);
    printTransitions(os); 
}

bool StackAutomata::acceptWordByFinalState(const std::string& word) {
    std::string currentState = initialState;
    std::stack<char> stk;
    stk.push(stackSymbol);

    printStepHeader();

    std::cout << "  "
              << std::left << std::setw(8)  << "0"
              << std::setw(10) << currentState
              << std::setw(10) << word
              << std::setw(10) << stk.top()
              << std::setw(12) << "Inicio"
              << std::setw(6)  << ""
              << stackToString(stk) << "\n";

    int step = 1;

    for (size_t i = 0; i < word.size(); i++) {

        char ch = word[i];
        std::string remaining = word.substr(i + 1);

        if (stk.empty()) {
            std::cout << "  [Pila vacia] No hay transicion posible -> RECHAZADA\n";
            return false;
        }

        char topChar = stk.top();
        bool found = false;

        for (const auto& t : transitions) {

            if (t.initialState == currentState &&   
                t.input == ch &&
                t.stackTop == topChar) {

                std::string opLabel;

                if (t.stackOperation == StackOp::PUSH) {
                    stk.push(t.pushSymbol);
                    opLabel = "Push " + std::string(1, t.pushSymbol);
                }
                else if (t.stackOperation == StackOp::NOP) {
                    opLabel = "Nop";
                }
                else {
                    opLabel = "Pop";
                    stk.pop();
                }

                std::cout << "  "
                          << std::left << std::setw(8)  << step
                          << std::setw(10) << t.newState
                          << std::setw(10) << (remaining.empty() ? "ε" : remaining)
                          << std::setw(10) << topChar
                          << std::setw(12) << opLabel
                          << std::setw(6)  << t.newState
                          << stackToString(stk) << "\n";

                currentState = t.newState;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "  [Sin transicion] (" << currentState << ", "
                      << ch << ", " << topChar << ") -> RECHAZADA\n";
            return false;
        }

        step++;
    }

    bool accepted = finalStates.count(currentState) > 0;

    std::cout << "  " << std::string(60, '-') << "\n";
    std::cout << "  Estado final: " << currentState
              << "  |  Pila: " << stackToString(stk)
              << "  |  " << (accepted ? "** ACEPTADA **"
                                     : "RECHAZADA (no es estado final)") << "\n";

    return accepted;
}
bool StackAutomata::acceptWordByEmptyStack(const std::string& word) {

    std::string currentState = initialState;
    std::stack<char> stk;
    stk.push(stackSymbol);

    std::string remaining = word;

    printStepHeader();

    std::cout << "  "
              << std::left << std::setw(8)  << "0"
              << std::setw(10) << currentState
              << std::setw(10) << remaining
              << std::setw(10) << stk.top()
              << std::setw(12) << "Inicio"
              << std::setw(6)  << ""
              << stackToString(stk) << "\n";

    int step = 1;

    for (size_t i = 0; i < word.size(); i++) {

        char ch = remaining[0];
        remaining = remaining.substr(1);

        if (stk.empty()) {
            std::cout << "  [Pila vacia] No hay transicion posible -> RECHAZADA\n";
            return false;
        }

        char topChar = stk.top();
        bool found = false;

        for (const auto& t : transitions) {

            if (t.initialState == currentState &&
                t.input == ch &&
                t.stackTop == topChar) {

                std::string opLabel;

                if (t.stackOperation == StackOp::PUSH) {
                    stk.push(t.pushSymbol);
                    opLabel = "Push " + std::string(1, t.pushSymbol);
                }
                else if (t.stackOperation == StackOp::NOP) {
                    opLabel = "Nop";
                }
                else {
                    stk.pop();
                    opLabel = "Pop";
                }

                std::cout << "  "
                          << std::left << std::setw(8)  << step
                          << std::setw(10) << t.newState
                          << std::setw(10) << (remaining.empty() ? "ε" : remaining)
                          << std::setw(10) << topChar
                          << std::setw(12) << opLabel
                          << std::setw(6)  << t.newState
                          << stackToString(stk) << "\n";

                currentState = t.newState;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "  [Sin transicion] (" << currentState << ", "
                      << ch << ", " << topChar << ") -> RECHAZADA\n";
            return false;
        }

        step++;
    }

    bool accepted = stk.top() == 'z' && remaining.empty();

    std::cout << "  " << std::string(60, '-') << "\n";
    std::cout << "  Estado final: " << currentState
              << "  |  Pila: " << (stk.empty() ? "[vacia]" : stackToString(stk))
              << "  |  Entrada restante: " << (remaining.empty() ? "ε" : remaining)
              << "  |  " << (accepted ? "** ACEPTADA **"
                                     : "RECHAZADA") << "\n";

    return accepted;
}

void StackAutomata::printStackAlphabet(std::ostream &os){
    os << "Alfabeto de pila: {"; 
    for(auto it = stackAlphabet.begin(); it != stackAlphabet.end(); ++it){
        os << *it;
        if(next(it) != stackAlphabet.end())
            os << ", "; 
    }
    os << "}\n";
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

void Automata_Manager::addFile(std::string file){
    files.push_back(file);
}