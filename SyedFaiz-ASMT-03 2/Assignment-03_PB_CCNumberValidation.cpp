#include<iostream>
#include<vector>
#include<iomanip>
#include <string>

using namespace std;

bool isvalidcc(const string&);

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2)  << i << " " 
			 << setw(17) << *itr 
			 << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0;
}
bool isvalidcc(const string& number) {
  vector<int> odd, even;  // Vector stores the number based on idex from left to right
  int index = 0, sumOdd = 0, sumEven = 0;
  
 // The starting numbers are: 4 for Visa cards, 5 for MasterCard cards, 37 for American Express cards, and 6 for Discover cards.
  if (number.size() < 13 || number.size() > 16) {
    // Invalid size
    return false;
  }
  if (number[0] != '4' && number[0] != '5' && number[0] != '6' &&
      (number[0] != '3' && number[1] != '7')) {
    // CHeck starting number
    return false;
  }
  for(int i = number.size()-1; i >= 0; i--) {
    int num = (int) (number[i]) - 48;  //stoi or typecasting
    if (index % 2 == 0) {
      odd.push_back(num);
    } else {
      even.push_back(num);
    }
    index += 1;
  }

  // Calculate sum of all odd index value
  for(int i = 0; i < odd.size(); i++) {
    sumOdd += odd[i];
  }

  // Calcualte sum of all even index value
  for (int i = 0; i < even.size(); i++) {
    int num = even[i] * 2;
    if (num > 9) {
      int first = num % 10;
      int second = num / 10;
      num = first + second;
    }
    sumEven += num;
  }

  // Final check number divisible 10 or not
  if ((sumOdd + sumEven) % 10 == 0) {
    return true;
  }

  return false;
}
