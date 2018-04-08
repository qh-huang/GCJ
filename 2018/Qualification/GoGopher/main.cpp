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

void solve(int round)
{
  int A;
  cin >> A;

  //cerr << 0 << ' ' << 0 << endl << flush;


  if (A == 20) { // ==> 4*5 = 20
    int** arr = (int**) malloc (5 * sizeof(int*));
    for (int i=0; i<5; i++) {
      arr[i] = (int*) malloc (6 * sizeof(int));
      for (int j=0; j<6; j++) {
        arr[i][j] = 0;
      }
    }

    int i, j;
    // brute-force solution: hit (2,2) ==> (3,4)
    for (int row = 2; row <= 3; row+=1) {
      for (int col = 2; col <= 4; col+=2) {
        while (!CheckAllOccupied(arr, row, col)) {
          cout << row << " " << col << endl << flush;
          cin >> i >> j;
          if (i == 0 && j == 0) {
            for (int i=0; i<5; i++) {
              free(arr[i]);
            }
            free(arr);
            return;
          }
          if (i == -1 && j == -1) {
            for (int i=0; i<5; i++) {
              free(arr[i]);
            }
            free(arr);
            return;
          }
          arr[i][j] = 1;
        }
      }
    }

    for (int i=0; i<5; i++) {
      free(arr[i]);
    }
    free(arr);
  } else { // A == 200 => 3 * 67 = 201
    int** arr = (int**) malloc (4 * sizeof(int*));
    for (int i=0; i<4; i++) {
      arr[i] = (int*) malloc (68 * sizeof(int));
      for (int j=0; j<68; j++) {
        arr[i][j] = 0;
      }
    }

    int i, j;
    // brute-force solution: hit (2,2) ==> (2,14)
    for (int row = 2; row <= 2; row+=1) {
      for (int col = 2; col <= 66; col+=3) { // 2,5,8,11,...65
        while (!CheckAllOccupied(arr, row, col)) {
          cout << row << " " << col << endl << flush;
          cin >> i >> j;
          if (i == 0 && j == 0) {
            for (int i=0; i<4; i++) {
              free(arr[i]);
            }
            free(arr);
            return;
          }
          if (i == -1 && j == -1) {
            for (int i=0; i<4; i++) {
              free(arr[i]);
            }
            free(arr);
            return;
          }
          arr[i][j] = 1;
        }
        if (col == 65) {
          col = 63; // should cover col = 66
        }
      }
    }
    for (int i=0; i<4; i++) {
      free(arr[i]);
    }
    free(arr);
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
