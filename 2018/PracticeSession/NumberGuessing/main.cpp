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


void solve()
{
  int A, B, N;
  cin >> A >> B;
  cin >> N;

  string response = "";
  int min = A+1;
  int max = B;
  int guess (min + max) / 2;
  while (response != "CORRECT") {
    guess = (min + max) / 2;
    cout << guess << endl;
    cin >> response;
    if (response == "TOO_SMALL") {
      min = guess + 1;
    } else { // TOO_BIG
      max = guess - 1;
    }
  }
}

int main() {
  int T;
  cin >> T;  // read t. cin knows that t is an int, so it reads it as such.
  //for (int round = 1; round <= 5; ++round) {
  for (int round = 1; round <= T; ++round) {
    solve();
  }

  return 0;
}
