#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void print(string message)
{
    cout << message << endl;
}

string readFiles(string& fileSrc)
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

vector<string> parseFile (string& file) {
    std::vector<std::string> statements;
   int i = 0;
    while (file.size())
    {
        i++;
        if (file[i] == ';')
        {
            statements.push_back(file.substr(0, i + 1));
            file = file.substr(i + 1, file.size());
            i = 0;
        };

        if (file.size() + 1 == i)
        {
            cout << "Missing ';' at " << i << endl;
            exit(0);
        }
    };
}

int main()
{
    parseFile(readFiles("db.csv"))
}