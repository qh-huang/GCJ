#include <algorithm>
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
    std::cout << std::endl \
              << "line " << __LINE__ << ": " \
              << STR(x) << "(" << x << ") ";
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

/**
  N  100

  K=1 (99) 49, 50

  K=2 (98) 49, [24, 25]
  K=3 (97) [24, 24], 24, 25

  K=4 (96) 24, 24, 24, [12, 12]
  K=5 (95) [11, 12], 24, 24, 12, 12
  K=6 (94) 11, 12, [11, 12], 24, 12, 12
  K=7 (93) 11, 12, 11, 12, [11, 12], 12, 12

  K=8 (92) 11, 12, 11, 12, 11, 12, 12, [5, 6]
  K=9 (91) 11, 12, 11, 12, 11, 12, [5, 6], 5, 6
  K=10 (90) 11, 12, 11, 12, 11, [5, 6], 5, 6, 5, 6
  K=11 (89) 11, 12, 11, [5, 6], 11, 5, 6, 5, 6, 5, 6
  K=12 (88) 11, [5, 6], 11, 5, 6, 11, 5, 6, 5, 6, 5, 6

  N 101

  K=1 (100) 50, 50
  K=2 (99)  50, [24, 25]
 */
void solve(long long int round, long long int K, long long int N)
{
  cout << "Case #" << round << ": ";

  DBG(N)
  DBG(K)

  // find the group K belongs to
  // [1-2][3-6][7-14]...
  long long int start = 1;
  while (start*2 <= K) {
    start *= 2;
  }

  DBG(start);
  long long int max, min;
  long long int num_segs = start; // K(8~15), start(8), num_segs = 8


  // the K-1 round, imaging N(100)
  long long int remain = N - (start - 1); // ex. 93
  long long int the_seg_to_split = remain / num_segs;

  DBG(remain)
  DBG(the_seg_to_split)

  if (K-start+1 <= remain % num_segs) { // K(8~12)
    the_seg_to_split += 1; // 12
  }

  max = the_seg_to_split / 2;
  if (IsOdd(the_seg_to_split)) {
    min = max;
  } else {
    min = max - 1;
  }

  cout << max << " " << min << endl;
}

int main() {
  long long int T, K, N;
  cin >> T;  // read t. cin knows that t is an int, so it reads it as such.
  //for (int round = 1; round <= 5; ++round) {
  for (long long int round = 1; round <= T; ++round) {
    cin >> N >> K;
    solve(round, K ,N);
  }

  return 0;
}
