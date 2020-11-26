#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <bits/stdc++.h>
#include "./structs.hpp"

using namespace std;

void print(string message);

vector<string> readFile(string fileSrc);

vector<candidant> parseCandidant(vector<string> rows);

vector<question> parseQuestion(vector<string> rows);


#endif