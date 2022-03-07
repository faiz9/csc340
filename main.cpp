#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

class word {
  private:
    string name;
    map<string, vector<string>> pos;

  public: 
    word() {name = "";}
    word(string name);
    void setName(string newName);
    string getName();
    void addPos(string key, string value);
    int getPosSize();
    void print(string posInput, bool distinct);
    bool findWord(string name);
};

// Constructor
word::word(string newName) {
  name = newName;
}

void word::setName(string newName) {
  name = newName;
}

string word::getName() {
  return name;
}

void word::addPos(string key, string value) {
  pos[key].push_back(value);
}

// Helper function for print whole map
void printMap(vector<string> value, string name, string key) {
  for (int i =0; i < value.size(); i++) {
    cout << name;
      // Print key
    cout  << " ["<< key << "] : ";
    cout << value[i] << endl;
  }
}

// Helper function filter duplicate a vector
void removeDuplicate(vector<string> &vect) {
  set<string> s;
  for (string x : vect) {
    s.insert(x);
  }
  // Clear vector
  vect.clear();
  for (set<string>::iterator it=s.begin(); it!=s.end(); ++it) {
    vect.push_back(*it);
  }
}

void word::print(string posInput, bool distinct) {
  
  map<string, vector<string>>::iterator itr; 
  for (itr = pos.begin(); itr != pos.end(); ++itr) {
    string key = itr->first; // Get pos of the word
    vector<string> value = itr->second;

    if (distinct == true) {
      // Handle distinct option
      removeDuplicate(value);
    }
    if (posInput == "") {
      printMap(value, name, key);
    } else if (key == posInput) {
      printMap(value, name, key);
    }
  } 
}
int word::getPosSize() {
  int count =0 ;
  map<string, vector<string>>::iterator itr;
  for (itr = pos.begin(); itr != pos.end(); ++itr) {
    vector<string> value = itr->second;
    count += value.size();
  }
  return count;
}

bool word::findWord(string nameWord) {
  if (name.size() != nameWord.size())
      return false;
  for(int i = 0 ;  i < name.size(); i++) {
    if (tolower(name[i]) != tolower(nameWord[i])) {
      return false;
    }
  }
  return true;
}
// End of define word class

bool loadData(string nameFile, vector<word> &dict) {

  ifstream inFile(nameFile);
  string line;
  if (!inFile) {
    cout << "File not found" << endl;
    return false;
  }
  while(getline(inFile,line)) {
    stringstream  linestream(line);
    string value;
    word newWord;
    int index = 0; // 0 Reading for name, 1 for pos
    // Reading each entry
    while(getline(linestream,value,'|')) {
        if (index == 0) {
            // Reading name of the word
            newWord.setName(value);
            index = 1;
        } else {
            // Reading pos based on key and value
            size_t found = value.find("-=>>");
            if (found == string::npos) {
              cout << "Invalid entry at word: " << newWord.getName() << endl;
              return false;
            }
            string key = value.substr(0, found-1);
            string valueOfKey = value.substr(found+4, value.size()-found);
            newWord.addPos(key, valueOfKey);

          /*
            cout << "Key: ";
            cout << value.substr(0, found-1) << endl;

            cout << "Value: ";
            cout << value.substr(found+4, value.size()-found) << endl;
          */
        }
    }
    dict.push_back(newWord);
  }
  return true;
}

int getDefinition(vector<word> dict) {
  int sum = 0;
  for(int i = 0 ; i < dict.size(); i++) {
    sum += dict[i].getPosSize();
  } 
  return sum;
}

void usage() {
  cout << "\t|" << endl;
  cout << "\t PARAMETER HOW-TO,  please enter:";
  cout << "\t 1. A search key -then 2. An optional part of speech -then" << endl;
  cout << "\t 3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
  cout << "\t|" << endl;
}

void notfound() {
  cout << "\t|" << endl;
  cout << "\t <NOT FOUND> To be considered for the next release. Thank you." << endl;
  cout << "\t|" << endl;
  usage();
}

void parse(string input, vector<string> &argv) {
  string space_delimiter = " ";
  size_t pos = 0;
  argv.clear();
  while ((pos = input.find(space_delimiter)) != string::npos) {
    argv.push_back(input.substr(0, pos));
    input.erase(0, pos + space_delimiter.length());
  }
}

bool cmpWord(string word1, string word2) {
  if (word1.size() != word2.size())
      return false;
  for(int i = 0 ;  i < word1.size(); i++) {
    if (tolower(word1[i]) != tolower(word2[i])) {
      return false;
    }
  }
  return true;
}

bool findWordFromDict(vector<word> dict, string word) {
  for (int i = 0; i < dict.size(); i++) {
    if (dict[i].findWord(word) == true) {
      return true;
    }
  }
  return false;
}
int main() {
  vector<word> dict;
  vector<string> argv;
  int argc;
  bool ret = loadData("Data.CS.SFSU.txt", dict);
  if (ret == false) {
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
  int counter = 1;
  while (input != "!Q" && input != "!q") {
    //break out of program cout thank you
    cout << "Search [" << counter << "]: ";
    getline(cin, input);
    // Parse the option by space
    parse(input, argv);
    argc = argv.size();
    if (input == "" || cmpWord(argv[0], "!help") || argc > 4) {
      usage();
    } else {
      // Initialize flag for options
      string pos, key;
      bool isDistinct = false;
      bool isReverse = false;
      for (int i = 0; i < argc; i++) {
        if (cmpWord(argv[i], "distinct"))
          isDistinct = true;
        if (cmpWord(argv[i], "reverse"))
          isReverse = true;
      }
      key = argv[0];
      if (findWordFromDict(dict, key) == false) {
        notfound();
      } else {
        
      }
    }




    counter +=1;
  }

  cout << "-----THANK YOU-----" << endl;
  return 0;
  //return 0;
}
