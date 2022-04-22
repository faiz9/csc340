#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

class word
{
private:
    string name;
    map<string, vector<string> > pos;

public:
    word() { name = ""; }
    word(string name);
    void setName(string newName);
    string getName();
    void addPos(string key, string value);
    int getPosSize();
    void print(string partOfSpeech, bool distinct = false, bool reversed = false);
    bool findWord(string name);

    bool hasPos(string posStr);

    void sortMeanings();
};

char toLowerChar(char in);
string toLowerString(string s);
char toUpperChar(char in);
bool cmpWord(string word1, string word2);