#ifndef AUTOMATAS_H
#define AUTOMATAS_H

#include <utility>
#include <string>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

typedef std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> TransitionMap;
typedef std::vector<std::tuple<std::string, char, char, std::string, std::string>> TransitionMapSA;

class Automata{
    protected:
        std::set<std::string> states;
        std::set<std::string> finalStates;
        std::string initialState;
        std::set<char> alphabet;


    public:
        std::set<std::string> getStates();
        void setStates(std::set<std::string> states);
        std::set<std::string> getFinalStates();
        void setFinalStates(std::set<std::string> finalStates);
        std::string getInitialState();
        void setInitialState(std::string initialState);
        std::set<char> getAlphabet();
        void setAlphabet(std::set<char> alphabet);

        virtual void printTransitions(std::ostream & os) = 0;
        void printAlphabet(std::ostream & os);
        virtual void describeAutomata(std::ostream & os) = 0;
        virtual void printStates(std::set<std::string> statesSet, std::string stateType, std::ostream & os);
        bool isValidState(std::string state);
        bool isValidFinalState(std::string state);
};

class FSAutomata: public Automata{
    private:
        TransitionMap transitions;
        bool explore(std::string currentState, const std::string& word, int index, 
        std::vector<std::string>& path, int& furthestIndex, std::string& lastState,
        std::vector<std::string>& bestPath);
    public:
        TransitionMap &getTransitions();
        void setTransitions(TransitionMap transitions);
        void printTransitions(std::ostream &os) override;
        void describeAutomata(std::ostream & os) override;
        void acceptWord(std::string word);
        bool isAutomataND();
        std::vector<std::string> carryOutTransition(std::string currentState, char input);
        std::vector<std::pair<std::pair<std::string, char>, std::vector<std::string>>> findAmbiguousTransitions();
        std::vector<std::string> generateWords();
        void deleteTransition();
        void addTransition();
        void modifyInitialState();
        void addFinalState();
        void deleteFinalState();
        void addSymboltoAlphabet();
        void printWordConstruction(const std::string& word, const std::vector<std::string>& path);
};

class StackAutomata: public Automata{
    private:
        std::set<char> stackAlphabet;
        char stackSymbol;
        TransitionMapSA transitions;
    public:

        std::set<char> getStackAlphabet();
        void setStackAlphabet(std::set<char> stackAlphabet);
        char getStackSymbol();
        void setStackSymbol(char stackSymbol);
        TransitionMapSA &getTransitions();
        void setTransitions(TransitionMapSA transitions);


        void printTransitions(std::ostream &os) override;
        void printStackAlphabet(std::ostream &os);
        void describeAutomata(std::ostream &os) override;
        void acceptWord(std::string word, bool emptyPile);

};


class Automata_Manager{
    private:
        std::vector<std::string> files;
    public:
        void addFile(std::string file);
        void setFiles();
        void saveFiles();
        void showFiles();
};

#endif