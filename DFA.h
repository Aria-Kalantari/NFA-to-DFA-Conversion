#ifndef DFA_H
#define DFA_H

#pragma once

#include <set>
#include <map>
#include <vector>

#include "NFA.h"

class State
{
    friend class DFA;
    friend class NFA;

public:
    State(void) = default;
    ~State() = default;

private:
    std::vector<int> data;
    std::map<char, State*> moves;
    bool accepted;
};

class DFA
{
    friend class NFA;

public:
    explicit DFA(State*, std::vector<char>);

    std::string isInDFA(std::string&) const;
    bool isInAlphabet(const char) const;

    ~DFA();

private:
    State* initialState;
    std::vector<char> alphabet;
};

#endif