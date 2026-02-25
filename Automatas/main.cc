#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"
#include "automataCreator.h"
#include "streams.h"


int main(int argc, char **argv){

    Automata automata;
    char opcion,tInput;
    std::string input, state;
    std::vector<std::string> visitedNodes;
    std::pair<std::string, char> cleanInput;

    while(true){
        std::cout << "---------- Menu ----------\n";
        std::cout << "1. Mostrar nomenclatura\n";
        std::cout << "2. Ejecutar transicion\n";
        std::cout << "3. Verificar palabra\n";
        std::cout << "4. Verificar si es AFD o AFND\n";
        std::cout << "5. Crear automata\n";
        std::cout << "6. Guardar automata\n";
        std::cout << "Para salir presione q\n";
        std::cout << "Seleccionar opcion: ";

        std::cin >> opcion;
        std::cin.ignore();
        if(opcion == 'q')
            break;
        switch(opcion){
            case '1':
                automata.describeAutomata(std::cout);
                break;
            case '2':
                std::cout << "Ingresar transición: ";
                std::getline(std::cin, input);
                cleanInput = cleanTransitionInput(input);
                std::cout << input << " = " << automata.carryOutTransition(cleanInput.first, cleanInput.second) << "\n";
                break;
            case '3':
                std::cout << "Ingrese la cadena a analizar: ";
                std::cin >> input;
                visitedNodes =  automata.acceptWord(input);
                printVisitedNodes(visitedNodes);
                break;
            case '4':
                automata.describeAutomata(std::cout);
                if(!automata.isAutomataND()){
                    std::cout << "El automata cumple con las caracteristicas de un AFD.\n";
                    std::cout << "Todas las transiciones tienen un camino determinista.\n";
                }
                else{
                    std::cout << "El autómata representa un AFND.\n";
                    std::cout << "Las transiciones ambiguas son las siguientes:\n";
                    printAmbiguousTransitions(automata.findAmbiguousTransitions());
                }
                break;
            case '5':
                automata = buildAutomataFromTerminal();
                break;
            case '6':
                saveAutomatatoFile(automata, "exampleAutomata.txt");
            break;
        }
        std::cout << "\n\n";
    }

    return 0;
};


