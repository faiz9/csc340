#include "word.h"
#include <map>

using namespace std;

map <string, word> dict;

bool loadData(string nameFile, map <string, word> &dict)
{
    ifstream inFile(nameFile);
    string line;
    if (!inFile)
    {
        cout << "File not found" << endl;
        return false;
    }
    while (getline(inFile, line))
    {
        stringstream linestream(line);
        string value;
        word newWord;
        int index = 0; // 0 Reading for name, 1 for pos
        // Reading each entry
        while (getline(linestream, value, '|'))
        {
            if (index == 0)
            {
                // Reading name of the word

                for(int i = 0; i < value.size(); ++i) value[i] = toLowerChar(value[i]);

                newWord.setName(value);
                index = 1;
            }
            else
            {
                // Reading pos based on key and value
                size_t found = value.find("-=>>");
                if (found == string::npos)
                {
                    cout << "Invalid entry at word: " << newWord.getName() << endl;
                    return false;
                }
                string key = toLowerString(value.substr(0, found - 1));
                string valueOfKey = value.substr(found + 4, value.size() - found);

                for(int i = 0; i < valueOfKey.size(); ++i){
                    if(valueOfKey[i] != ' '){
                        valueOfKey[i] = toUpperChar(valueOfKey[i]);
                        break;
                    }
                }

                valueOfKey[0] = toUpperChar(valueOfKey[0]);
                newWord.addPos(key, valueOfKey);

                // cout << "Key: " << key << " / Value : " << valueOfKey << endl;
            }
        }

        newWord.sortMeanings();

        dict[newWord.getName()] = newWord; 

        // cout << " ok new word " << newWord.getName() << ": " << endl;
        // newWord.print("");
    }
    return true;
}

int getDefinition(map <string, word> &dict)
{
    int ans = 0;
    for(map<string, word>::iterator wordItor = dict.begin(); wordItor != dict.end(); ++wordItor){
        ans += wordItor->second.getPosSize();
    }
    return ans;
}

void usage()
{
    cout << "\t|" << endl;
    cout << "\t PARAMETER HOW-TO,  please enter:" << endl;
    cout << "\t 1. A search key -then 2. An optional part of speech -then" << endl;
    cout << "\t 3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
    cout << "\t|" << endl;
}

void notfound()
{
    cout << "\t|" << endl;
    cout << "\t <NOT FOUND> To be considered for the next release. Thank you." << endl;
    cout << "\t|" << endl;
    usage();
}

void error2(string option)
{
    cout << "\t|" << endl;
    cout << "\t <The entered 2nd parameter \'" << option << "\' is NOT a part of speech.>" << endl;
    cout << "\t <The entered 2nd parameter \'" << option << "\' is NOT \'distinct\'.>" << endl;
    cout << "\t <The entered 2nd parameter \'" << option << "\' is NOT \'reverse\'.>" << endl;
    cout << "\t <The entered 2nd parameter \'" << option << "\' was disregarded.>" << endl;
    cout << "\t <The entered 2nd parameter should be a part of speech or \'distinct\' or \'reverse\'.>" << endl;
    cout << "\t|" << endl;
}

void error3(string option)
{
    cout << "\t|" << endl;
    cout << "\t <The entered 3rd parameter \'" << option << "\' is NOT \'distinct\'.>" << endl;
    cout << "\t <The entered 3rd parameter \'" << option << "\' is NOT \'reverse\'.>" << endl;
    cout << "\t <The entered 3rd parameter \'" << option << "\' was disregarded.>" << endl;
    cout << "\t <The entered 3rd parameter should be \'distinct\' or \'reverse\'.>" << endl;
    cout << "\t|" << endl;
}

void error4(string option)
{
    cout << "\t|" << endl;
    cout << "\t <The entered 4th parameter \'" << option << "\' is NOT \'reverse\'.>" << endl;
    cout << "\t <The entered 4th parameter \'" << option << "\' was disregarded.>" << endl;
    cout << "\t <The entered 4th parameter should be \'reverse\'.>" << endl;
    cout << "\t|" << endl;
}

void parse(string input, vector<string> &argv)
{
    char space_delimiter = ' ';
    argv.clear();

    string currentToken = "";

    for (int i = 0; i < input.size(); ++i)
    {
        if (input[i] == space_delimiter)
        {
            if (currentToken.size())
            {
                argv.push_back(currentToken);
                currentToken.clear();
            }
        }
        else
        {
            currentToken += input[i];
        }
    }

    if (currentToken.size())
        argv.push_back(currentToken);
}

bool isPartOfSpeech(string word)
{
    vector<string> POS;

    POS.push_back("noun");
    POS.push_back("adjective");
    POS.push_back("verb");
    POS.push_back("preposition");
    POS.push_back("pronoun");
    POS.push_back("interjection");
    POS.push_back("conjunction");
    POS.push_back("adverb");

    for (int i = 0; i < POS.size(); ++i)
    {
        if (cmpWord(word, POS[i]) == true)
            return true;
    }
    return false;
}
bool isDistinct(string word)
{
    return cmpWord(word, "distinct");
}

bool isReverse(string word)
{
    return cmpWord(word, "reverse");
}
bool checkType(string word, int typeId)
{
    if (typeId == 1)
        return isPartOfSpeech(word);
    if (typeId == 2)
        return isDistinct(word);
    if (typeId == 3)
        return isReverse(word);
    return false;
}

int main()
{
    vector<string> argv;
    int argc;
    bool ret = loadData("Data.CS.SFSU.txt", dict);
    if (ret == false)
    {
        return ret;
    }
    cout << "------ Keywords: " << dict.size() << endl;
    cout << "------ Definitions: " << getDefinition(dict) << endl;
    /*for(i = 0; i < dict.size(); i++) {
      dict[i].print("noun");
    }
    for(int i = 0; i < dict.size(); i++) {
      dict[i].print("noun", true);
    } */
    string input = "";
    int counter = 0;
    while (true)
    {
        counter += 1;
        cout << "Search [" << counter << "]: ";
        getline(cin, input);
        // Parse the option by space
        parse(input, argv);
        argc = argv.size();

        // cout << "num of params: " << argc << endl;
        // for (int i = 0; i < argv.size(); ++i)
        // {
        //     cout << "'" << argv[i] << "'" << endl;
        // }
        if (argc <= 0 || argc >= 5 || cmpWord(argv[0], "!help"))
        {
            usage();
        }
        else if (cmpWord(argv[0], "!q"))
        {
            break;
        }
        else
        {
            // Initialize flag for options
            string key = toLowerString(argv[0]);

            if(dict.find(key) == dict.end()){
                notfound();
                continue;
            }

            string partOfSpeech = "";
            bool isDistinct = false;
            bool isReverse = false;

            for (int i = 1; i < argv.size(); ++i)
            {
                string param = argv[i];

                int typeId = -1;

                for (int j = i; j <= 3; ++j)
                    if (checkType(param, j))
                    {
                        typeId = j;
                        break;
                    }

                if (typeId < 0)
                {
                    if (i == 1)
                        error2(param);
                    else if (i == 2)
                        error3(param);
                    else
                        error4(param);
                }
                else
                {
                    if (typeId == 1)
                        partOfSpeech = toLowerString(param);
                    else if (typeId == 2)
                        isDistinct = true;
                    else
                        isReverse = true;
                }
            }

            if(partOfSpeech != "" && !dict[key].hasPos(partOfSpeech)){
                notfound();
                continue;
            }
            dict[key].print(partOfSpeech, isDistinct, isReverse);
        }
    }

    cout << "-----THANK YOU-----" << endl;
    return 0;
    // return 0;
}
