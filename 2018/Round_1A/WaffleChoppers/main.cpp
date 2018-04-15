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
void DumpCharArr2D(vector<string> arr)
{
  for (int i = 0; i < arr.size(); i++) {
    cout << arr[i] << endl;
  }
  cout << endl;
}
#else
void DumpCharArr2D(char** arr, int N) {}
#endif

int
SumTotalChocolate(vector<string> arr)
{
  int num_choco = 0;
  for (int row=0; row<arr.size(); row++) {
    for (int col=0; col<arr[row].size(); col++) {
      if (arr[row][col] == '@') {
        num_choco++;
      }
    }
  }
  return num_choco;
}

int
SumTotalChocolateInRow(const string row)
{
  int num_choco = 0;
  for (int col=0; col<row.size(); col++) {
    if (row[col] == '@') {
      num_choco++;
    }
  }
  return num_choco;
}

int
SumTotalChocolateInCol(vector<string> arr, const int col)
{
  int num_choco = 0;
  for (int row=0; row<arr.size(); row++) {
    if (arr[row][col] == '@') {
      num_choco++;
    }
  }
  return num_choco;
}

int
SumTotalChocolateInPiece(
    vector<string> arr,
    const int row_from, const int row_to,
    const int col_from, const int col_to)
{
  int num_choco = 0;
  for (int row=row_from; row<=row_to; row++) {
    for (int col=col_from; col<=col_to; col++) {
      if (arr[row][col] == '@') {
        num_choco++;
      }
    }
  }
  //cout << __func__ << ": " << num_choco << endl;
  return num_choco;
}


void solve(int round)
{
  int R, C, H, V;
  cin >> R >> C >> H >> V;

  vector<string> waffle;
  waffle.resize(R);
  for (int row=0; row<R; row++) {
    cin >> waffle[row];
  }

  //DumpCharArr2D(waffle);
  const int total_choco = SumTotalChocolate(waffle);

  if (total_choco % (H+1) != 0) { cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return; }
  if (total_choco % (V+1) != 0) { cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return; }
  if (total_choco % ((H+1)*(V+1)) != 0) {cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return; }

  vector<int> row_split;
  vector<int> col_split;

  // row split
  const int num_choco_per_row_cut = total_choco / (H+1);
  int left_choco = total_choco;
  int allocated_choco = 0;
  for (int row=0; row<R; row++) {
    allocated_choco += SumTotalChocolateInRow(waffle[row]);
    if (allocated_choco == num_choco_per_row_cut) {
      left_choco -= allocated_choco;
      allocated_choco = 0;
      //cout << "cut row_" << row << endl;
      row_split.push_back(row);
    } else if (allocated_choco > num_choco_per_row_cut) {
      cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return;
    }
  }
  if (left_choco != 0) { cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return; }

  // col split
  const int num_choco_per_col_cut = total_choco / (V+1);
  left_choco = total_choco;
  allocated_choco = 0;
  for (int col=0; col<C; col++) {
    allocated_choco += SumTotalChocolateInCol(waffle, col);
    if (allocated_choco == num_choco_per_col_cut) {
      left_choco -= allocated_choco;
      allocated_choco = 0;
      //cout << "cut col_" << col << endl;
      col_split.push_back(col);
    } else if (allocated_choco > num_choco_per_col_cut) {
      cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return;
    }
  }
  if (left_choco != 0) { cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return; }

  // check each piece
  const int num_choco_per_piece = total_choco / ((H+1)*(V+1));
  int row_from, row_to, col_from, col_to;
  for (int i=0; i<row_split.size(); i++) {
    row_from = (i==0)? 0 : row_split[i-1] + 1;
    row_to = row_split[i];
    for (int j=0; j<col_split.size(); j++) {
      col_from = (j==0)? 0 : col_split[j-1] + 1;
      col_to = col_split[j];

      if (num_choco_per_piece != SumTotalChocolateInPiece(waffle, row_from, row_to, col_from, col_to)) {
        cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl; return;
      }

    }
  }

  cout << "Case #" << round << ": " << "POSSIBLE" << endl;
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
