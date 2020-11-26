#include <bits/stdc++.h>
#include "./structs.hpp"
#include "./utils.hpp"

using namespace std;

vector<string> getAnswers(vector<question> &questions)
{
    vector<string> answers;
    for (int i = 0; i < questions.size(); i++)
    {
        system("cls");
        print(questions[i].question);
        print(" ");

        print("Que tan importante consideras este aspecto");
        print("a) Nada importante");
        print("b) Poco importante");
        print("c) Medianamente importante");
        print("d) Bastante importante");
        print("e) Muy importante");
        print(" ");
        string option;
        cin >> option;
        int importance;

        if (option == "a")
        {
            importance = 0;
        }
        else if (option == "b")
        {
            importance = 25;
        }
        else if (option == "c")
        {
            importance = 50;
        }
        else if (option == "d")
        {
            importance = 75;
        }
        else if (option == "e")
        {
            importance = 100;
        }
        else
        {
            print("Wrong command");
            i--;
            continue;
        }
        questions[i].importance = importance;

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

void match(vector<candidant> candidants, candidant thisVoter, vector<question> questions)
{
    vector<string> answers = thisVoter.answers;
    vector<int> compatibility;

    int maxPoints = 0;
    for (int i = 0; i < questions.size(); i++)
    {
        maxPoints += questions[i].importance;
    }

    for (int i = 0; i < candidants.size(); i++)
    {
        int current = 0;
        for (int j = 0; j < candidants[i].answers.size(); j++)
        {
            if (candidants[i].answers[j] == answers[j])
            {
                current += questions[i].importance;
            }
        }
        compatibility.push_back(current);
    }
    vector<pair<int, int>> maximum;
    pair<int, int> first(int(INT_MIN), 0);
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
    cout << "con un puntaje de " << maximum[0].first << " y una compatibilidad de " << maximum[0].first * 100 / maxPoints << "%" << endl;
    print(" ");
}

int main()
{
    vector<candidant> candidants = parseCandidant(readFile("db.csv"));
    vector<candidant> voters;

    print("Cual es su nombre?");
    string name = "Martin";
    cin >> name;
    vector<question> questions = parseQuestion(readFile("questions.csv"));
    vector<string> answers = getAnswers(questions);
    candidant customCandidate;
    customCandidate.name = name;
    customCandidate.answers = answers;
    voters.push_back(customCandidate);

    for (int i = 0; i < voters.size(); i++)
    {
        match(candidants, voters[i], questions);
    }

    return 0;
}