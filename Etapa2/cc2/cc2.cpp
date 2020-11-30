#include <bits/stdc++.h>

using namespace std;

struct candidant
{
    string name;
    vector<pair<string, float>> answers;
};

struct question
{
    string question;
    vector<pair<string, string>> options;
};

void print(string message)
{
    cout << message << endl;
};

vector<string> readFile(string fileSrc)
{
    vector<string> file;
    std::ifstream src(fileSrc);
    if (src.is_open())
    {
        std::string line;
        while (getline(src, line))
        {
            file.push_back(line);
        }
    }
    else
    {
        print("Couldn't open the database");
    }
    return file;
}

vector<candidant> parseCandidant(vector<string> rows)
{
    vector<candidant> db;
    for (int i = 0; i < rows.size(); i++)
    {
        int j = 0, k = 0;
        candidant current;
        pair<string, float> currentAnswer;

        while (rows[i].size())
        {
            j++;
            if (rows[i][j] == ',')
            {
                if (k == 0)
                {
                    current.name = rows[i].substr(0, j);
                }
                else if (k % 2)
                {
                    currentAnswer.first = rows[i].substr(0, j);
                }
                else
                {
                    currentAnswer.second = stof(rows[i].substr(0, j));
                    current.answers.push_back(currentAnswer);
                }
                rows[i] = rows[i].substr(j + 1);
                k++;
                j = 0;
            }
        }
        db.push_back(current);
    }
    return db;
}

vector<question> parseQuestion(vector<string> rows)
{
    vector<question> db;
    for (int i = 0; i < rows.size(); i++)
    {
        int j = -1, k = 0;
        question current;

        pair<string, string> current_option;
        while (rows[i].size())
        {
            j++;
            if (rows[i][j] == ';')
            {
                if (k == 0)
                {
                    current.question = rows[i].substr(0, j);
                }
                else if (k % 2 != 0)
                {
                    current_option.first = rows[i].substr(0, j);
                }
                else
                {
                    current_option.second = rows[i].substr(0, j);
                    current.options.push_back(current_option);
                }
                rows[i] = rows[i].substr(j + 1);
                k++;
                j = -1;
            }
        }
        db.push_back(current);
    }
    return db;
}

vector<pair<string, float>> getAnswers(vector<question> questions)
{
    vector<pair<string, float>> answers;
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
        pair<string, float> current;

        if (option == "a")
        {
            current.second = 0.0f;
        }
        else if (option == "b")
        {
            current.second = 0.25f;
        }
        else if (option == "c")
        {
            current.second = 0.50f;
        }
        else if (option == "d")
        {
            current.second = 0.75f;
        }
        else if (option == "e")
        {
            current.second = 1.0f;
        }
        else
        {
            print("Wrong command");
            i--;
            continue;
        }

        for (int j = 0; j < questions[i].options.size(); j++)
        {
            cout << questions[i].options[j].first << ")" << questions[i].options[j].second << endl;
        }
        print("Que opción se ajusta mejor a tu pensamiento?");
        string answer;
        cin >> answer;
        print(" ");
        current.first = answer;
        answers.push_back(current);
    }
    return answers;
}

void match(vector<candidant> candidants, candidant thisVoter)
{
    vector<float> compatibility;

    vector<float> maxPoints;

    for (int i = 0; i < candidants.size(); i++)
    {
        float current = 0;
        maxPoints.push_back(0.0f);
        for (int j = 0; j < candidants[i].answers.size(); j++)
        {
            maxPoints[i] += candidants[i].answers[j].second * thisVoter.answers[j].second;

            if (candidants[i].answers[j].first == thisVoter.answers[j].first)
            {
                current += candidants[i].answers[j].second * thisVoter.answers[j].second;
            }
        }
        compatibility.push_back(current);
    }
    vector<pair<float, int>> maximum;
    pair<float, int> first(float(INT_MIN), 0);
    maximum.push_back(first);
    for (int i = 0; i < compatibility.size(); i++)
    {
        if (compatibility[i] > maximum[0].first)
        {
            maximum.clear();
            pair<float, int> current;
            current.first = compatibility[i];
            current.second = i;
            maximum.push_back(current);
        }
        else if (compatibility[i] == maximum[0].first)
        {
            pair<float, int> current;
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
    cout << " con una compatibilidad de " << maximum[0].first * 100 / maxPoints[maximum[0].second] << "%" << endl;
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
        vector<pair<string, float>> answers = getAnswers(parseQuestion(readFile("questions.csv")));
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