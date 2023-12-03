#ifndef NFA_H
#define NFA_H

#pragma once

#include <vector>
#include <set>
#include <string>

#include "DFA.h"

class NFA
{
public:
    explicit NFA(const int, const std::vector<char>&, const int, const std::vector<int>&, const std::vector<std::vector<std::vector<char>>>&);

    bool isAcceptingState(const int) const;

    std::vector<int> deltaStar(const int, const char);
    
    DFA convertToDFA(void);

    ~NFA();

private:
    int Q;
    std::vector<char> alphabet;
    int initialState;
    std::vector<int> acceptingStates;
    std::vector<std::vector<std::vector<char>>> transitions;

    bool isInQ(std::set<std::vector<int>>, std::vector<int>&) const;
};

#endif