#ifndef GENERATE_CHAINS_H
#define GENERATE_CHAINS_H

#include <vector>
#include <string>
#include <set>
#include <time.h>
#include <stdlib.h>
#include "automatas.h"

void backtrack(
    const std::string& state,
    TransitionMap& transitions,
    std::unordered_map<std::string,int>& visits,
    std::set<std::string>& finalStates,
    std::string str,
    std::vector<std::string>& results);

#endif