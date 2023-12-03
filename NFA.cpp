#include "NFA.h"
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

NFA::NFA(const int Q, const vector<char>& alphabet, const int initialState, const vector<int>& acceptingStates, const vector<vector<vector<char>>>& transitions)
    : Q(Q),
      alphabet(alphabet),
      initialState(initialState),
      acceptingStates(acceptingStates),
      transitions(transitions) { }

bool NFA::isAcceptingState(const int state) const
{
    int size = this->acceptingStates.size();
    for(int i = 0; i < size; ++i)
        if(state == this->acceptingStates[i])
            return true;
    return false;
}

vector<int> NFA::deltaStar(const int q, const char x)
{
    vector<int> result;

    for(int i = 0; i < Q; ++i)
        for(int j = 0; j < transitions[q][i].size(); ++j)
            if(!transitions[q][i].empty())
                if(transitions[q][i][j] == x)
                    result.push_back(i);

    return result;
}

DFA NFA::convertToDFA(void)
{
    std::set<std::vector<int>> DFAstates;
    queue<State*> stateQueue;

    State* DFAinitialState = new State;
    DFAinitialState->data.push_back(this->initialState);
    DFAstates.insert(DFAinitialState->data);
    
    DFAinitialState->accepted = isAcceptingState(this->initialState);

    stateQueue.push(DFAinitialState);

    map<vector<int>, State*> vectorToState;
    vectorToState[DFAinitialState->data] = DFAinitialState;

    while(!stateQueue.empty())
    {
        State* state = stateQueue.front();
        stateQueue.pop();
        
        for(char sigma : alphabet)
        {
            vector<int> newData;                           
            set<int> setNewData;                           
            for(int i = 0; i < state->data.size(); ++i)    
            {                                              
                vector<int> targets;                       
                targets = deltaStar(state->data[i], sigma);                  
                for(int j = 0; j < targets.size(); ++j)
                    setNewData.insert(targets[j]);
            }
            for(int thisOne : setNewData)
                newData.push_back(thisOne);

            if(!isInQ(DFAstates, newData))
            {
                State* newState = new State;
                newState->data = newData;
                stateQueue.push(newState);
                DFAstates.insert(newData);
                state->moves[sigma] = newState;
                vectorToState[newData] = newState;
                for(int i = 0; i < newState->data.size(); ++i)
                {
                    if(isAcceptingState(newState->data[i]))
                    {
                        newState->accepted = true;
                        break;
                    }
                    else
                        newState->accepted = false;
                }
                if(newState->data.empty())
                    newState->accepted = false;
            }
            else
            {
                state->moves[sigma] = vectorToState[newData];
            }
        }
    }

    DFA dfa(DFAinitialState, alphabet);
    return dfa;
}

bool NFA::isInQ(set<vector<int>> DFAstates, vector<int>& data) const
{
    for(vector<int> thisOne : DFAstates)
        if(thisOne == data)
            return true;
    return false;
}

NFA::~NFA() { }