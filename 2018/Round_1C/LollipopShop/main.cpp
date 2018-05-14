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


bool CheckAllOccupied(int** arr, const int i, const int j)
{
  for (int row = i-1; row <= i+1; row++) {
    for (int col = j-1; col <= j+1; col++) {
      if (arr[row][col] == 0) {
        return false;
      }
    }
  }
  return true;
}

vector<int> SplitNumbersByDelimiter(string str_to_split, const string delimiter)
{
    vector<int> result;
    int pos = 0;
    string token;
    while ((pos = str_to_split.find(delimiter)) != std::string::npos) {
        token = str_to_split.substr(0, pos);
        result.push_back(Num2Digits(token)[0]);
        str_to_split.erase(0, pos + delimiter.length());
    }
    return result;
}

int FindBestValidLollipop(const vector<int>& lollipops, const vector<int>& flavors, const vector<int>& stats_flavors)
{
    int best_flavor = -1;
    for (int flavor : flavors) {
        if (lollipops[flavor] == 1) { // not sold yet
            if (best_flavor == -1 ||
                    stats_flavors[flavor] < stats_flavors[best_flavor]) {
                best_flavor = flavor;  
            }
        }
    }
    return best_flavor;
}

void solve(int round)
{
  int N; // num of customers and lollipops
  cin >> N; 
  vector<int> lollipops, flavors_stats;
  lollipops.resize(N);
  flavors_stats.resize(N);

  fill(lollipops.begin(), lollipops.end(), 1);
  fill(flavors_stats.begin(), flavors_stats.end(), 0);
  for (int id_customer=0; id_customer < N; id_customer++) {
    int D; // num of flavors
    cin >> D;
    vector<int> flavors;
    flavors.resize(D);
    for (int idx_flavor=0; idx_flavor < D; idx_flavor++) {
        int flavor;
        cin >> flavor;
        flavors[idx_flavor] = flavor;
        flavors_stats[flavor] += 1;
    }
    int lollipops_found = FindBestValidLollipop(lollipops, flavors, flavors_stats);
    cout << lollipops_found << endl << flush;
    if (lollipops_found != -1) {
        lollipops[lollipops_found] = 0;
    }
  }
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
