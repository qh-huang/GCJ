#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>  // includes cin to read from stdin and cout to write to stdout
#include <sstream>
#include <unordered_map>
#include <vector>

#define NDEBUG 0
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

double FractionPart(double whole)
{
  return whole - (int)whole;
}

int NumOfPeopleToRoundup(const double fraction)
{
  int num = 1;
  while (FractionPart(num * fraction) < 0.5) num++;
  return num;
}

void solve(int nround)
{
  int N, L;
  cin >> N >> L;
  vector<int> C;
  int num_of_people_left = N;
  for (int i=1; i<=L; i++) {
    int c_i;
    cin >> c_i;
    num_of_people_left -= c_i;
    C.push_back(c_i);
  }
  DBG(num_of_people_left);

  // if 100 can be divided by N, then result is 100
  if (100 % N == 0) {
    cout << "Case #" << nround << ": " << 100 << endl;
    return;
  }

  // find the index of round-down (ex. X.4999) language, and fill it to round-up
  int index_of_round_down = 0;
  long total_percentage = 0;
  DBG(total_percentage);
  while (index_of_round_down < (int)C.size()) {
    long double ratio = ( 100. / (double)N )* (double)C[index_of_round_down];
    DBG(ratio);
    double fraction = ratio - ((long)ratio);
    if (fraction < 0.5 && num_of_people_left > 0) {
      C[index_of_round_down] += 1;
      num_of_people_left -= 1;
      DBG(num_of_people_left);
    } else {
      total_percentage += round(ratio);
      DBG(total_percentage);
      index_of_round_down++;
    }
  }

  // all languages are round-up, create new languages for the rest of people
  if (index_of_round_down == (int)C.size() && num_of_people_left > 0) {
    double each_person_contribute = 100. / (double)N;
    int num_of_people_to_roundup = NumOfPeopleToRoundup(each_person_contribute);
    int max_percentage_from_left_people = num_of_people_left / num_of_people_to_roundup;
    total_percentage += max_percentage_from_left_people * round(num_of_people_to_roundup * each_person_contribute);
    num_of_people_left -= (max_percentage_from_left_people * num_of_people_to_roundup);
    total_percentage += round(each_person_contribute * (double)num_of_people_left);
  }

  cout << "Case #" << nround << ": " << total_percentage << endl;
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
