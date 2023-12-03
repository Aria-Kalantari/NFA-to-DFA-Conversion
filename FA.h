#ifndef FA_H
#define FA_H

#pragma once

#include <vector>

class FA
{
public:
    explicit FA(const int, const std::vector<char>&, const int, const std::vector<int>&, const std::vector<std::vector<std::vector<char>>>&);

    bool is$NFA(void) const;
    bool isNFA(void) const;

    ~FA();

private:
    int Q;
    std::vector<char> alphabet;
    int initialState;
    std::vector<int> acceptingStates;
    std::vector<std::vector<std::vector<char>>> transitions;
};

#endif