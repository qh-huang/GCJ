#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>  // includes cin to read from stdin and cout to write to stdout
#include <sstream>
#include <vector>

using namespace std;  // since cin and cout are both in namespace std, this saves some text

vector<int> Num2Digits(string num)
{
  vector<int> digits;
  digits.resize(num.size());
  for (int i = 0; i < digits.size(); i++) {
    switch (num[i]) {
      case '0': digits[i] = 0; break;
      case '1': digits[i] = 1; break;
      case '2': digits[i] = 2; break;
      case '3': digits[i] = 3; break;
      case '4': digits[i] = 4; break;
      case '5': digits[i] = 5; break;
      case '6': digits[i] = 6; break;
      case '7': digits[i] = 7; break;
      case '8': digits[i] = 8; break;
      case '9': digits[i] = 9; break;
      default:
        exit(1);
    }
  }
  return digits;
}

string Digits2Num(vector<int> digits)
{
  static const string d2n_str = "0123456789";
  string num;
  num.resize(digits.size());
  for (int i = 0; i < digits.size(); i++) {
    num[i] = d2n_str[digits[i]];
  }
  return num;
}

string findTidy(string number)
{
  if (number.size() == 1) return number;
  // find 1st index breaking Tidy (ex. 11111102345, 2222221234, 1009232, 1234566640123, 111110)
  //                                        ^            ^      ^               ^           ^
  int index = 1;
  vector<int> digits = Num2Digits(number);
  for ( ;index < digits.size(); index++) {
    if (digits[index] < digits[index - 1]) {
      break;
    }
  }

  // lucky, it is Tidy
  if (index == digits.size()) return Digits2Num(digits);

  // fill 9's
  // carry
  for (int i = index; i < digits.size(); i++) {
    digits[i] = 9;
  }
  index--;
  digits[index] = digits[index] - 1;

  for (int i = index - 1; i >= 0; i--) {
    if (digits[i] > digits[i+1]) {
      digits[i] = digits[i] - 1;
      digits[i+1] = 9;
    }
  }

  // eliminate leading 0's
  while (digits[0] == 0) {
    digits.erase(digits.begin());
  }

  return Digits2Num(digits);
}

void solve(int round, string number)
{
  //cout << "Case #" << round << ": " << number; cout << " " << findTidy(number) << endl;
  cout << "Case #" << round << ": " << findTidy(number) << endl;
}

int main() {
  int T;
  string number;
  cin >> T;  // read t. cin knows that t is an int, so it reads it as such.
  for (int round = 1; round <= T; ++round) {
    cin >> number;
    solve(round, number);
  }

  return 0;
}
