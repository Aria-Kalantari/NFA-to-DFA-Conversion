#include "FA.h"
#include <vector>

using namespace std;

FA::FA(const int Q, const vector<char>& alphabet, const int initialState, const vector<int>& acceptingStates, const vector<vector<vector<char>>>& transitions)
    : Q(Q),
      alphabet(alphabet),
      initialState(initialState),
      acceptingStates(acceptingStates),
      transitions(transitions) { }

bool FA::is$NFA(void) const
{
    for(int i = 0; i < Q; ++i)
        for(int j = 0; j < Q; ++j)
            for(int k = 0; k < transitions[i][j].size(); ++k)
                if(this->transitions[i][j][k] == '$')
                    return true;
    return false;
}

bool FA::isNFA(void) const { return !this->is$NFA(); }

FA::~FA() { }