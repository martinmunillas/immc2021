#include <bits/stdc++.h>
#include "./structs.hpp"
#include "./utils.hpp"

using namespace std;

vector<string> getAnswers(vector<question> questions)
{
    vector<string> answers;
    for (int i = 0; i < questions.size(); i++)
    {
        print(questions[i].question);
        for (int j = 0; j < questions[i].options.size(); j++)
        {
            cout << questions[i].options[j].first << ")" << questions[i].options[j].second << endl;
        }
        print("Que opción se ajusta mejor a tu pensamiento?");
        string answer;
        cin >> answer;
        print(" ");
        answers.push_back(answer);
    }
    return answers;
}

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
                current += 100;
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
    cout << "con un puntaje de " << maximum[0].first << " y una compatibilidad de " << maximum[0].first / answers.size() << "%" << endl;
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

    for (int i = 0; i < voters.size(); i++)
    {
        match(candidants, voters[i]);
    }

    return 0;
}