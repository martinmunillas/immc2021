#include <bits/stdc++.h>

using namespace std;

struct candidant
{
    string name;
    vector<string> answers;
};

struct question
{
    string question;
    vector<pair<string, string>> options;
};

void print(auto message)
{
    cout << message << endl;
}

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

        while (rows[i].size())
        {
            j++;
            if (rows[i][j] == ',')
            {
                if (k == 0)
                {
                    current.name = rows[i].substr(0, j);
                }
                else
                {
                    current.answers.push_back(rows[i].substr(0, j));
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
        int j = 0, k = 0;
        question current;

        pair<string, string> current_option;
        while (rows[i].size())
        {
            j++;
            if (rows[i][j] == ',')
            {
                if (k == 0)
                {
                    current.question = rows[i].substr(0, j);
                } else if (k % 2 != 0) {
                    current_option.first = rows[i].substr(0, j);
                }
                else
                {
                    current_option.second = rows[i].substr(0, j);
                    current.options.push_back(current_option);
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

vector<string> getAnswers(vector<question> questions) {
    vector<string> answers;
    for(int i = 0; i < questions.size(); i++) {
        print(questions[i].question);
        for(int j = 0; j < questions[i].options.size(); j++) {
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

string match(vector<candidant> candidants, vector<string> answers) {
    vector<int> compatibility;
    for(int i = 0; i < candidants.size(); i++) {
        int current = 0;
        for(int j = 0; j < candidants[i].answers.size(); j++) {
            if( candidants[i].answers[j] == answers[j] ) {
                current++;
            }
        }
        compatibility.push_back(current);
    }
    
}


int main()
{
    vector<candidant> candidants = parseCandidant(readFile("db.csv"));

    vector<string> answers = getAnswers(parseQuestion(readFile("cuestions.csv")));

    print(match(candidants, answers));

    return 0
}