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

int ComputeBestHeightIndex(const int index, const int weight, vector<int>& weights_accu, vector<int>& heights_accu)
{
    int best_height = 1;
    const int WEIGHT_LIMIT = 6 * weight;
    int best_height_index = -1;
    for (int i=0; i<index; i++) {
       DBG(best_height);
       DBG(heights_accu[i]);
       DBG(weights_accu[i]);
       if (best_height <= heights_accu[i] && weights_accu[i] <= WEIGHT_LIMIT) {
         best_height = heights_accu[i];
         best_height_index = i;
       }
    }
    return best_height_index;
}

void solve(int round)
{
  int N; // num ants
  cin >> N; 
  vector<int> weights, weights_accu, heights_accu;
  weights.resize(N);
  weights_accu.resize(N);
  heights_accu.resize(N);
  fill(weights_accu.begin(), weights_accu.end(), 0);

  for (int idx_ant=0; idx_ant < N; idx_ant++) {
    cin >> weights[idx_ant];
    DBG(weights[idx_ant]);
    const int best_height_index = ComputeBestHeightIndex(idx_ant, weights[idx_ant], weights_accu, heights_accu);
    DBG(best_height_index);
    if (best_height_index == -1) {
      weights_accu[idx_ant] = weights[idx_ant];
      heights_accu[idx_ant] = 1;
    } else {
      weights_accu[idx_ant] = weights_accu[best_height_index] + weights[idx_ant];
      DBG(weights_accu[idx_ant]);
      heights_accu[idx_ant] = heights_accu[best_height_index] + 1;
      DBG(heights_accu[idx_ant]);
    }
  }
  cout << "Case #" << round << ": " << *max_element(heights_accu.begin(), heights_accu.end()) << endl;
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
