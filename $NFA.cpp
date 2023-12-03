#include "$NFA.h"
#include <queue>

using namespace std;

$NFA::$NFA(const int Q, const vector<char>& alphabet, const int initialState, const vector<int>& acceptingStates, const vector<vector<vector<char>>>& transitions) 
    : Q(Q),
      alphabet(alphabet),
      initialState(initialState),
      acceptingStates(acceptingStates),
      transitions(transitions) { }

bool $NFA::isAcceptingState(const int state) const
{
    int size = this->acceptingStates.size();
    for(int i = 0; i < size; ++i)
        if(state == this->acceptingStates[i])
            return true;
    return false;
}

vector<int> $NFA::deltaStar(const int q, const char x)
{
    queue<int> current;
    current.push(q);

    set<int> result;

    vector<bool> wasChecked(Q);
    for(int i = 0; i < Q; ++i)
        wasChecked[i] = false;
    wasChecked[q] = true;

    vector<bool> wasAccepted(Q);
    for(int i = 0; i < Q; ++i)
        wasAccepted[i] = false;

    while(!current.empty())
    {
        int state = current.front();
        current.pop();

        for(int j = 0; j < Q; ++j)
        {
            if(!transitions[state][j].empty())
            {
                for(int k = 0; k < transitions[state][j].size(); ++k)
                    if(transitions[state][j][k] == '$' && wasChecked[j] == false)
                    {
                        wasChecked[j] = true;
                        current.push(j);
                    }
                for(int k = 0; k < transitions[state][j].size(); ++k)
                    if(transitions[state][j][k] == x)
                    {
                        result.insert(j);
                    }
            }
        } 
    }

    queue<int> resultQueue;
    for(int thisOne : result)
        resultQueue.push(thisOne);
    
    while(!resultQueue.empty())
    {
        int state = resultQueue.front();
        resultQueue.pop();

        for(int j = 0; j < Q; ++j)
        {
            if(!transitions[state][j].empty())
            {
                for(int k = 0; k < transitions[state][j].size(); ++k)
                    if(transitions[state][j][k] == '$')
                    {
                        result.insert(j);
                        resultQueue.push(j);
                    }
            }
        }
    }
    
    vector<int> resultVec;
    for(int thisOne : result)
        resultVec.push_back(thisOne);

    return resultVec;
}

NFA $NFA::convertToNFA(void)
{
    vector<vector<vector<char>>> newTransitions(Q, vector<vector<char>>(Q));

    for(int q = 0; q < Q; ++q)
        for(char sigma : alphabet)
        {
            vector<int> newTransition = deltaStar(q, sigma);
            for(int target : newTransition)
                newTransitions[q][target].push_back(sigma);
        }
    
    if(doesAccept$() && !isAcceptingState(initialState))
        acceptingStates.push_back(initialState);

    NFA nfa(Q, alphabet, initialState, acceptingStates, newTransitions);
    return nfa;
}

bool $NFA::doesAccept$(void) const
{   
    queue<int> $states;
    $states.push(initialState);

    vector<bool> wasChecked(Q);
    for(int i = 0; i < Q; ++i)
        wasChecked[i] = false;
    wasChecked[initialState] = true;

    while(!$states.empty())
    {
        int state = $states.front();
        $states.pop();

        if(isAcceptingState(state))
        {
            return true;
        }
        else
        {
            for(int i = 0; i < Q; ++i)
                if(!transitions[state][i].empty())
                {
                    for(int k = 0; k < transitions[state][i].size(); ++k)
                        if(transitions[state][i][k] == '$' && wasChecked[i] == false)
                        {
                            wasChecked[i] = true;
                            $states.push(i);
                        }
                }
        }
    }

    return false;
}

$NFA::~$NFA() { }