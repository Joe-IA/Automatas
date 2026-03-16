#include <utility>
#include <string>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "streams.h"

std::pair<std::string, char> cleanTransitionInput(std::string input){
    size_t start = input.find("(") + 1;
    size_t comma = input.find(",");

    std::string state = input.substr(start, comma - start);
    size_t end = input.find(")");
    std::string symbol = input.substr(comma + 2, end - (comma + 2));
    if (symbol == "\" \""){
        symbol = " ";
    }
    std::pair<std::string, char> exit = {state, symbol[0]};
    return exit;
}
std::vector<std::string> cleanCSInput(std::string input){
    std::string nextValue;
    std::vector<std::string> values;
    for(const char &c: input){
        if(c == ','){
            values.push_back(nextValue);
            nextValue.clear();
            continue;
        }
        if(c == ' ')
            continue;
        nextValue.push_back(c);
    }
    values.push_back(nextValue);
    return values;
}

std::string cleansetNotation(std::string input){
    size_t start = input.find("{") + 1;
    std::string substring = input.substr(start);
    substring.pop_back();
    return substring;
}


void printVisitedNodes(std::vector<std::string> nodes){
    for (int i = 0; i < nodes.size(); ++i){
        std::cout << nodes[i];
        if(i < nodes.size() - 1)
            std::cout << " -> ";
    }
    std::cout << "\n";
}


void printAmbiguousTransitions(std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>> transitions){
    for (const auto &ambState: transitions){
        std::string currentState = ambState.first.first;
        char input = ambState.first.second;
        std::vector<std::string> incomingStates = ambState.second;
        std::cout << "T(" << currentState << ", " << input << ") = {";
        for(auto it = incomingStates.begin(); it != incomingStates.end(); ++it){
            std::cout << *it;
            if(next(it) != incomingStates.end())
            std::cout << ", ";
        }
        std::cout << "}\n";
    }
}

std::string readFile(std::string name){
    std::ifstream file(name);
    std::string content = "", buffer;
    while(std::getline(file, buffer)){
        content += buffer;
        content.push_back('\n');
    }
    return content;
}
std::vector<std::string> splitlines(const std::string &text){
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;
    while(std::getline(ss, line, '\n')){
        lines.push_back(line);
    }
    return lines;
}
void saveAutomatatoFile(Automata &automata, std::string outputFile){
    std::fstream file;
    
    file.open(outputFile.c_str(), std::ios::out);
    if(!file)
        throw std::runtime_error("Couldn't create the file");
    automata.describeAutomata(file);
}

void savetoFile(std::string content, std::string outputFile){
    std::fstream file;
    file.open(outputFile.c_str(), std::ios::out);
    if(!file)
        throw std::runtime_error("Couldn't create the file");
    file << content;

}
void printModifyAutomataMenu(){
    std::cout << "Modificaciones al automata:\n";
    std::cout << "1. Agregar transicion\n";
    std::cout << "2. Modificar estado inicial\n";
    std::cout << "3. Agregar estado final\n";
    std::cout << "4. Eliminar estado final\n";
    std::cout << "5. Agregar simbolo al alphabet\n";
    std::cout << "6. Eliminar Transicion\n";
    std::cout << "Ingrese opcion: ";
}
