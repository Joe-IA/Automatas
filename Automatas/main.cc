#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"
#include "automataCreator.h"
#include "streams.h"


int main(int argc, char **argv){

    FSAutomata automata;
    Automata_Manager manager;
    manager.setFiles();
    char opcion,tInput;
    std::string input, state;
    std::vector<std::string> visitedNodes;
    std::vector<std::string> trans;
    std::pair<std::string, char> cleanInput;

    while(true){
        std::cout << "---------- Menu ----------\n";
        std::cout << "1. Mostrar nomenclatura\n";
        std::cout << "2. Ejecutar transicion\n";
        std::cout << "3. Verificar palabra\n";
        std::cout << "4. Verificar si es AFD o AFND\n";
        std::cout << "5. Crear automata\n";
        std::cout << "6. Guardar automata\n";
        std::cout << "7. Importar automata de arhcivo\n";
        std::cout << "8. Modificar automata existente\n";
        std::cout << "9. Administrador de automatas\n";
        std::cout << "0. Generar palabras\n";
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
                trans = automata.carryOutTransition(cleanInput.first, cleanInput.second);
                for(int i = 0; i < trans.size(); ++i){
                    std::cout << input << " = " << trans[i] << "\n";
                }
                break;
            case '3':
                std::cout << "Ingrese la cadena a analizar: ";
                std::cin >> input;
                std::cin.ignore();
                automata.acceptWord(input);
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
                automata = buildFSAutomataFromTerminal();
                break;
            case '6':
                std::cout << "Archivo de salida: ";
                std::cin >> input;
                std::cin.ignore();
                saveAutomatatoFile(automata, input);
                manager.addFile(input);
                manager.saveFiles();
                break;
            case '7':
                std::cout << "Nombre del archivo: ";
                std::cin >> input;
                std::cin.ignore();
                automata = buildFSAutomataFromFile(input);
                break;
            case '8':
                printModifyAutomataMenu();
                std::cin >> opcion;
                std::cin.ignore();
                switch (opcion)
                {
                case '1':
                    automata.addTransition();
                    break;
                case '2':
                    automata.modifyInitialState();
                    break;
                case '3':
                    automata.addFinalState();
                    break;
                case '4':
                    automata.deleteFinalState();
                    break;
                case '5':
                    automata.addSymboltoAlphabet();
                    break;
                case '6':
                    automata.deleteTransition();
                    break;
                }

                break;
            case '9':
                std::cout << "Automatas construidos: \n";
                manager.showFiles();
                break;
            case '0':
                auto words = automata.generateWords();
                std::cout << "Palabras\n";
                for(const auto &word: words){
                    std::cout << word << "\n";
                }
                break;
            
        }
        std::cout << "\n\n";
    }

    return 0;
};
