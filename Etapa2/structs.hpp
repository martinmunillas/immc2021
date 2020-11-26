#ifndef STRUCTS_HPP_
#define STRUCTS_HPP_

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
    int importance;
};

#endif