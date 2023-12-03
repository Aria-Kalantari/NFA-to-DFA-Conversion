#include "DFA.h"
#include <iostream>

using namespace std;

DFA::DFA(State* initialState, vector<char> alphabet) : initialState(initialState),
                                                       alphabet(alphabet) { }

string DFA::isInDFA(string& x) const
{
    State* state = initialState;

    if(x == "$")
    {
        if(state->accepted == true)
            return "Yes";
        else
            return "No";
    }

    for(int i = 0; i < x.length(); ++i)
    {  
        if(!isInAlphabet(x[i]))
            return "No";        

        state = state->moves[x[i]];
    }
    
    if(state->accepted == true)
        return "Yes";
    else
        return "No";
}

bool DFA::isInAlphabet(const char x) const
{
    for(int i = 0; i < alphabet.size(); ++i)
        if(alphabet[i] == x)
            return true;
    return false;
}

DFA::~DFA() { }