#include <bits/stdc++.h>
#include "./structs.hpp"
#include "./utils.hpp"

using namespace std;

void match(vector<candidant> candidants, candidant thisVoter)
{
    vector<string> answers = thisVoter.answers;
    vector<int> compatibility;
    for (int i = 0; i < candidants.size(); i++)
    {
        int current = 0;
        for (int j = 0; j < candidants[i].answers.size(); j++)
        {
            if (candidants[i].answers[j] == answers[j])
            {
                current++;
            }
        }
        compatibility.push_back(current);
    }
    vector<pair<int, int>> maximum;
    pair<int, int> first(INT_MIN, 0);
    maximum.push_back(first);
    for (int i = 0; i < compatibility.size(); i++)
    {
        if (compatibility[i] > maximum[0].first)
        {
            maximum.clear();
            pair<int, int> current;
            current.first = compatibility[i];
            current.second = i;
            maximum.push_back(current);
        }
        else if (compatibility[i] == maximum[0].first)
        {
            pair<int, int> current;
            current.first = compatibility[i];
            current.second = i;
            maximum.push_back(current);
        }
    }

    vector<string> optimal;
    for (int i = 0; i < maximum.size(); i++)
    {
        optimal.push_back(candidants[maximum[i].second].name);
    }

    cout << "Los candidatos mas optimos para " << thisVoter.name << " son: ";
    for (int i = 0; i < optimal.size(); i++)
    {

        cout << optimal[i] << ", ";
    }
    print(" ");
}

int main()
{
    vector<candidant> candidants = parseCandidant(readFile("db.csv"));
    vector<candidant> voters;
    char option;

    print("Oprima \"A\" para usar los votantes de la base de datos o \"B\" para un votante personalizado");
    
    cin >> option;
    
    if (option == 'A' || option == 'a')
    {
        voters = parseCandidant(readFile("participants.csv"));
    }
    else if (option == 'B' || option == 'b')
    {
        print("Cual es su nombre?");
        string name;
        cin >> name;
        vector<string> answers = getAnswers(parseQuestion(readFile("questions.csv")));
        candidant customCandidate;
        customCandidate.name = name;
        customCandidate.answers = answers;
        voters.push_back(customCandidate);
    }
    else
    {
        print("unknown command");
    }

    
    for (int i = 0; i < voters.size(); i++){
        print(voters[i].name);
        match(candidants, voters[i]);
    }

    return 0;
}