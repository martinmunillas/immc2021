#include <bits/stdc++.h>

using namespace std;

struct candidant
{
    string name;
    vector<string> answers;
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

vector<candidant> parseFile(vector<string> rows)
{
    vector<candidant> db;
    for (int j = 0; j < rows.size(); j++)
    {
        int k = 0, l = 1;
        candidant current;

        while (rows[j].size())
        {
            if (rows[j][k] == ',')
            {
                if (l == 1)
                {
                    current.name = rows[j].substr(0, k);
                }
                else
                {
                    current.answers.push_back(rows[j].substr(0, k));
                }
                rows[j] = rows[j].substr(k, rows[j].size());
                l++;
                k = 0;
            }
            else
            {
                k++;
            }
        }
        db.push_back(current);
    }
    return db;
}

int main()
{
    vector<candidant> candidants = parseFile(readFile("db.csv"));
    for (int i = 0; i < candidants.size(); i++)
        print(candidants[i].name);
}