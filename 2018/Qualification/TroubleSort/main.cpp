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
void DumpIntVec(vector<int>& vec)
{
  for (int i=0; i<vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}
#else
void DumpCharArr2D(char** arr, int N) {}
void DumpIntVec(vector<int>& vec) {}
#endif


void solve(int round)
{
  vector<long long int> all, odd, even;
  int N;

  cin >> N;
  DBG(N);

  long long int input;
  for (int i=0; i<N; i++) {
    cin >> input;
    if (IsOdd(i)) {
      odd.push_back(input);
    } else {
      even.push_back(input);
    }
    // debug onluy;
    all.push_back(input);
  }

  // DumpIntVec(all);
  // DumpIntVec(even);
  // DumpIntVec(odd);

  sort(even.begin(), even.end());
  sort(odd.begin(), odd.end());

  // DumpIntVec(even);
  // DumpIntVec(odd);

  // 1 1 7 9 8
  // 1 7 8
  // 1 9
  if (even.size() == odd.size()) {
    const int num = even.size();
    for (int i=0; i<num; i++) {
      if (even[i] > odd[i]) {
        cout << "Case #" << round << ": " << 2 * i << endl;
        return;
      }
      if (i < num - 1 && odd[i] > even[i+1]) {
        cout << "Case #" << round << ": " << 2 * i + 1 << endl;
        return;
      }
    }
  } else { // even.size() > odd.size()
    const int num = odd.size();
    for (int i=0; i<num; i++) {
      if (even[i] > odd[i]) {
        cout << "Case #" << round << ": " << 2 * i << endl;
        return;
      }
      if (odd[i] > even[i+1]) {
        cout << "Case #" << round << ": " << 2 * i + 1 << endl;
        return;
      }
    }
  }

  cout << "Case #" << round << ": " << "OK" << endl;
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
