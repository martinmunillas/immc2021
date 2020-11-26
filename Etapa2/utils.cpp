#include <bits/stdc++.h>
#include "./structs.hpp"

using namespace std;

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

