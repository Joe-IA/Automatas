#include <string>
#include <unordered_map>
#include <set>
#include "automatas.h"


void backtrack(
    const std::string& state,
    TransitionMap& transitions,
    std::unordered_map<std::string,int>& visits,
    std::set<std::string>& finalStates,
    std::string str,
    std::vector<std::string>& results) {

    visits[state]++;

    if (finalStates.count(state)) {
        results.push_back(str);
    }

    for (auto& [input, nextStates] : transitions[state]) {
        for (auto& next : nextStates) {
            if (visits[next] < 4) {
                backtrack(
                    next,
                    transitions,
                    visits,
                    finalStates,
                    str + input,
                    results
                );
            }
        }
    }

    visits[state]--;
}