#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>  // includes cin to read from stdin and cout to write to stdout
#include <sstream>
#include <unordered_map>
#include <vector>

#define NDEBUG 1
#define DEBUG ~(NDEBUG)

#define _STR(s) #s
#define STR(s) _STR(s) // convert macro


#if NDEBUG
  #define DBG(x)
#else
  #define DBG(x) \
    do {         \
    std::cout << std::endl \
              << "line " << __LINE__ << ": " \
              << STR(x) << "(" << x << ") "; \
    } while (0);
#endif

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

bool IsEven(int num) { return num % 2 == 0; }
bool IsOdd(int num) { return !IsEven(num); }

#if DEBUG
void DumpCharArr2D(char** arr, int N)
{
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}
#else
void DumpCharArr2D(char** arr, int N) {}
#endif


void solve(int round)
{
  int D;
  string P;

  cin >> D >> P;

  DBG(D);
  DBG(P);

  int shoot_power = 1;
  int total_power = 0;
  unordered_map<int, int> sp_table; // shoot_power_table <power, number>
  sp_table[shoot_power] = 0;
  for (int i=0; i<P.size(); i++) {
    if (P[i] == 'S') {
      sp_table[shoot_power] += 1;
      total_power += shoot_power;
    } else if (P[i] == 'C') {
      shoot_power *= 2;
      sp_table[shoot_power] = 0;
    }
  }

  if (sp_table[shoot_power] == 0) {
    shoot_power /= 2;
  }

  int y = 0; // num of hacks
  while (total_power - D > 0) {
    if (shoot_power == 1) {
      cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl;
      return;
    }
    sp_table[shoot_power] -= 1;
    total_power -= shoot_power;
    sp_table[shoot_power/2] += 1;
    total_power += shoot_power/2;
    y += 1;
    if (sp_table[shoot_power] == 0) {
      shoot_power /= 2;
    }
  }
  cout << "Case #" << round << ": " << y << endl;
}

int main() {
  int T;
  cin >> T;  // read t. cin knows that t is an int, so it reads it as such.
  //for (int round = 1; round <= 5; ++round) {
  for (int round = 1; round <= T; ++round) {
    solve(round);
  }

  return 0;
}
