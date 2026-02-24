#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"
#include "display.h"
using namespace std;

int main(int argc, char **argv){

    Automata automata;
    char opcion,tInput;
    string input, state;
    vector<string> visitedNodes;
    pair<string, char> cleanInput;

    automata.alphabet = {'a', 'b', 'c'};
    automata.states = {"q0", "q1", "q2", "q3", "q4"};
    automata.transitions = {
        {"q0", {{'a', {"q1"}}}},
        {"q1", {{'c', {"q2"}}}},
        {"q2", {{'a', {"q3"}}, {'b', {"q2"}}, {'c', {"q2"}}}},
        {"q3", {{'a', {"q3"}}, {'b', {"q4"}}, {'c', {"q2"}}}},
        {"q4", {{'a', {"q3"}}, {'b', {"q2"}}, {'c', {"q2"}}}}
    };
    automata.initialState = "q0";
    automata.finalStates = {"q4"};

    while(true){
        cout << "---------- Menu ----------\n";
        cout << "1. Mostrar nomenclatura\n";
        cout << "2. Ejecutar transicion\n";
        cout << "3. Verificar palabra\n";
        cout << "4. Verificar si es AFD o AFND\n";
        cout << "Para salir presione q\n";
        cout << "Seleccionar opcion: ";

        cin >> opcion;
        cin.ignore();
        if(opcion == 'q')
            break;
        switch(opcion){
            case '1':
                automata.describeAutomata();
                break;
            case '2':
                cout << "Ingresar transición: ";
                getline(cin, input);
                cleanInput = cleanTransitionInput(input);
                cout << input << " = " << automata.carryOutTransition(cleanInput.first, cleanInput.second) << "\n";
                break;
            case '3':
                cout << "Ingrese la cadena a analizar: ";
                cin >> input;
                visitedNodes =  automata.acceptWord(input);
                printVisitedNodes(visitedNodes);
                break;
            case '4':
                automata.describeAutomata();
                if(!automata.isAutomataND()){
                    cout << "El automata cumple con las caracteristicas de un AFD.\n";
                    cout << "Todas las transiciones tienen un camino determinista.\n";
                }
                else{
                    cout << "El autómata representa un AFND.\n";
                    cout << "Las transiciones ambiguas son las siguientes:\n";
                    printAmbiguousTransitions(automata.findAmbiguousTransitions());
                }
                break;
        }
        cout << "\n\n";
    }

    return 0;
};


