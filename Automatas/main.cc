#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "automatas.h"
#include "automataCreator.h"
#include "streams.h"


int main(int argc, char **argv){

    Automata_Manager manager;
    manager.setFiles();
    char option,tInput;
    std::string input, state;
    std::vector<std::string> visitedNodes;
    std::vector<std::string> trans;
    std::pair<std::string, char> cleanInput;
    bool isStackAutomata;
    FSAutomata FSautomata;
    StackAutomata Stackautomata;
    do{
        std::cout << "--------- Tipo de automata ---------\n";
        std::cout << "1. AFD - AFND\n";
        std::cout << "2. PDA\n";
        std::cout << "Selecciona opcion: ";
        std::cin >> option;
        std::cin.ignore();
        if(option == '1')
            isStackAutomata = false;
        else if(option == '2')
            isStackAutomata = true;
    } while(option != '1' && option != '2');

    while(true) {
        if(!isStackAutomata){
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
            std::cin >> option;
            std::cin.ignore();
            if(option == 'q')
                break;
            switch(option){
                case '1':
                    FSautomata.describeAutomata(std::cout);
                    break;
                case '2':
                    std::cout << "Ingresar transición: ";
                    std::getline(std::cin, input);
                    cleanInput = cleanTransitionInput(input);
                    trans = FSautomata.carryOutTransition(cleanInput.first, cleanInput.second);
                    for(int i = 0; i < trans.size(); ++i){
                        std::cout << input << " = " << trans[i] << "\n";
                    }
                    break;
                case '3':
                    std::cout << "Ingrese la cadena a analizar: ";
                    std::cin >> input;
                    std::cin.ignore();
                    FSautomata.acceptWord(input);
                    break;
                case '4':
                    FSautomata.describeAutomata(std::cout);
                    if(!FSautomata.isAutomataND()){
                        std::cout << "El automata cumple con las caracteristicas de un AFD.\n";
                        std::cout << "Todas las transiciones tienen un camino determinista.\n";
                    }
                    else{
                        std::cout << "El autómata representa un AFND.\n";
                        std::cout << "Las transiciones ambiguas son las siguientes:\n";
                        printAmbiguousTransitions(FSautomata.findAmbiguousTransitions());
                    }
                    break;
                case '5':
                    FSautomata = buildFSAutomataFromTerminal();
                    break;
                case '6':
                    std::cout << "Archivo de salida: ";
                    std::cin >> input;
                    std::cin.ignore();
                    saveAutomatatoFile(FSautomata, input);
                    manager.addFile(input);
                    manager.saveFiles();
                    break;
                case '7':
                    std::cout << "Nombre del archivo: ";
                    std::cin >> input;
                    std::cin.ignore();
                    FSautomata = buildFSAutomataFromFile(input);
                    break;
                case '8':
                    printModifyAutomataMenu();
                    std::cin >> option;
                    std::cin.ignore();
                    switch (option)
                    {
                    case '1':
                        FSautomata.addTransition();
                        break;
                    case '2':
                        FSautomata.modifyInitialState();
                        break;
                    case '3':
                        FSautomata.addFinalState();
                        break;
                    case '4':
                        FSautomata.deleteFinalState();
                        break;
                    case '5':
                        FSautomata.addSymboltoAlphabet();
                        break;
                    case '6':
                        FSautomata.deleteTransition();
                        break;
                    }
                    break;
                case '9':
                    std::cout << "Automatas construidos: \n";
                    manager.showFiles();
                    break;
                case '0':
                    auto words = FSautomata.generateWords();
                    std::cout << "Palabras\n";
                    for(const auto &word: words){
                        std::cout << word << "\n";
                    }
                    break;
                
                }
            std::cout << "\n\n";
        }
        else {
            
            std::cout << "---------- Menu ----------\n";
            std::cout << "1. Mostrar nomenclatura\n";
            std::cout << "2. Verificar palabra por estado final\n";
            std::cout << "3. Verificar palabra por pila vacia\n";
            std::cout << "4. Crear automata\n";
            std::cout << "5. Guardar automata\n";
            std::cout << "6. Importar automata de archivo\n";
            std::cout << "7. Administrador de automatas\n";
            std::cout << "Para salir presione q\n";
            std::cout << "Seleccionar opcion: ";
            std::cin >> option;
            std::cin.ignore();
            if(option == 'q')
                break;

            switch(option){
                case '1':
                    Stackautomata.describeAutomata(std::cout);
                    break;
                case '2':
                    std::cin >> input;
                    std::cin.ignore();
                    Stackautomata.acceptWordByFinalState(input);
                    break;
                case '3':
                    std::cin >> input;
                    std::cin.ignore();
                    Stackautomata.acceptWordByEmptyStack(input);
                    break;
                case '4':
                    Stackautomata = buildStackAutomataFromTerminal();
                    break;
                case '5':
                    std::cout << "Archivo de salida: ";
                    std::cin >> input;
                    std::cin.ignore();
                    saveAutomatatoFile(Stackautomata, input);
                    manager.addFile(input);
                    manager.saveFiles();
                    break;
                case '6':
                    std::cout << "Nombre del archivo: ";
                    std::cin >> input;
                    std::cin.ignore();
                    Stackautomata = buildStackAutomataFromFile(input);
                    break;
                case '7':
                    std::cout << "Automatas construidos: \n";
                    manager.showFiles();
                    break;
            }
        }
    }
    return 0;
};
