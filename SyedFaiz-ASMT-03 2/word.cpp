#include "word.h"

// helper functions
char toLowerChar(char in) {
    if (in <= 'Z' && in >= 'A')
        return (char)(in - ('Z' - 'z'));
    return in;
}
string toLowerString(string s){
    for(int i = 0; i < s.size(); ++i){
        s[i] = toLowerChar(s[i]);
    }
    return s;
}
char toUpperChar(char in) {
    if (in <= 'z' && in >= 'a'){
        // cout << in << " ~> " << (char)(in - ('z' - 'Z')) << endl;
        return (char)(in - ('z' - 'Z'));
    }
    return in;
}

bool cmpWord(string word1, string word2)
{
    if (word1.size() != word2.size())
        return false;
    for (int i = 0; i < word1.size(); i++)
    {
        if (tolower(word1[i]) != tolower(word2[i]))

        {
            return false;
        }
    }
    return true;
}

// Constructor
word::word(string newName)
{
    name = newName;
}

void word::setName(string newName)
{
    name = newName;
}

string word::getName()
{
    return name;
}

void word::addPos(string key, string value)
{
    if (pos.find(key) == pos.end())
        pos[key] = vector<string>();

    value[0] = toUpperChar(value[0]);    

    pos[key].push_back(value);
}

void word::print(string partOfSpeech, bool distinct, bool reversed)
{
    cout << "\t|" << endl;
    
    vector <pair<string, string> > result;
    map<string, vector<string> >::iterator it;

    if(partOfSpeech == ""){
        for (it = pos.begin(); it != pos.end(); ++it)
        {
            for(int i = 0; i < it->second.size(); ++i){
                result.push_back(make_pair(it->first, it->second[i]));
            }
        }
    }else{
        it = pos.find(partOfSpeech);

        if(it != pos.end()){
            for(int i = 0; i < it->second.size(); ++i){
                result.push_back(make_pair(it->first, it->second[i]));
            }
        }
    }

    string currentWord = name;
    for(int i = 1; i < currentWord.size(); ++i){
        currentWord[i] = toLowerChar(currentWord[i]);
    }
    currentWord[0] = toUpperChar(currentWord[0]);

    if(reversed) reverse(result.begin(), result.end());
    for(int i = 0; i < result.size(); ++i){
        if(i > 0 && distinct && result[i] == result[i - 1]) continue;

        cout << "\t" << currentWord;
        // Print key
        cout << " [" << result[i].first << "] : ";
        cout << result[i].second << "\n";
    }

    cout << "\t|" << endl;
}

int word::getPosSize()
{
    int count = 0;
    map<string, vector<string> >::iterator it;
    for (it = pos.begin(); it != pos.end(); ++it)
    {
        count += it->second.size();
    }
    return count;
}

bool word::hasPos(string posStr){
    return pos.find(posStr) != pos.end();
}
void word::sortMeanings()
{
    for (map<string, vector<string> >::iterator it = pos.begin(); it != pos.end(); ++it)
    {
        sort(it->second.begin(), it->second.end());
    }
}

bool word::findWord(string nameWord)
{
    return cmpWord(name, nameWord);
}