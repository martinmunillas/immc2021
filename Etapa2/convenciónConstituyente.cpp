#include <bits/stdc++.h>

using namespace std;

struct candidant
{
    string name;
    vector<char> answers;
}

void
print(string message)
{
    cout << message << endl;
}

string readFiles(string fileSrc)
{
    string file = "";
    std::ifstream src(fileSrc);
    if (src.is_open())
    {
        std::string line;
        while (getline(src, line))
        {
            file += line;
        }
    }
    else
    {
        print("Couldn't open the database");
    }
}

vector<vector<string>> parseFile(string file)
{
    std::vector<std::string> rows;
    int i = 0;
    while (file.size())
    {
        i++;
        if (file[i] == '\n')
        {
            rows.push_back(file.substr(0, i + 1));
            file = file.substr(i + 1, file.size());
            i = 0;
        };
    };
    vector<candidant> db;
    for (int j = 0; j < rows.size(); j++)
    {
        int k = 0;
        candidant current;
        while (rows[j].size())
        {
            if (rows[j][k] == ',')
            {
                rows.push_back(file.substr(0, i + 1));
                file = file.substr(i + 1, file.size());
                k = 0;
            }
        }
    }
}

int main()
{
    parseFile(readFiles("db.csv"))
}