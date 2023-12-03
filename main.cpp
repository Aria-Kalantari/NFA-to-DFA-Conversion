#include "$NFA.cpp"
#include "NFA.cpp"
#include "FA.cpp"
#include "DFA.cpp"
#include <iostream>

using namespace std;

int main(void)
{
    int Q;
    cin >> Q;
    
    int numOfAlphabets;
   cin >> numOfAlphabets;

    int numOfAcceptingStates;
    cin >> numOfAcceptingStates;

    int numOfTransitions;
    cin >> numOfTransitions;

    int numOfTestCases;
    cin >> numOfTestCases;

    vector<char> alphabet(numOfAlphabets);
    for(int i = 0; i < numOfAlphabets; ++i)
        cin >> alphabet[i];
    
    int initialState;
    cin >> initialState;

    vector<int> acceptingStates(numOfAcceptingStates);
    for(int i = 0; i < numOfAcceptingStates; ++i)
        cin >> acceptingStates[i];
    
    vector<vector<vector<char>>> transitions(Q, vector<vector<char>>(Q));
    for(int i = 0; i < numOfTransitions; ++i)
    {
        int from;
        char with;
        int to;
        cin >> from;
        cin >> with;
        cin >> to;

        transitions[from][to].push_back(with);
    }

    vector<string>testCases(numOfTestCases);
    for(int i = 0; i < numOfTestCases; ++i)
        cin >> testCases[i];

    FA fa(Q, alphabet, initialState, acceptingStates, transitions);
    if(fa.is$NFA())
    {
        $NFA enfa(Q, alphabet, initialState, acceptingStates, transitions);

        NFA nfa = enfa.convertToNFA();

        DFA dfa = nfa.convertToDFA();

        cout << "------------------------------------------------------------------------------------------" << endl;

        for(int i = 0; i < numOfTestCases; ++i)
            cout << dfa.isInDFA(testCases[i]) << endl;
    }
    else
    {
        NFA nfa(Q, alphabet, initialState, acceptingStates, transitions);

        DFA dfa = nfa.convertToDFA();

        cout << "------------------------------------------------------------------------------------------" << endl;

        for(int i = 0; i < numOfTestCases; ++i)
            cout << dfa.isInDFA(testCases[i]) << endl;
    }
}