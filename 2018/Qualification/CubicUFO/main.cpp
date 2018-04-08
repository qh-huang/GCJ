#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
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

long double
DegToRad(const long double deg)
{

  return (deg / 180.) * M_PI;
}

long double
RadToDeg(const long double rad)
{
  return rad * 180. / M_PI;
}

vector<int>
Num2Digits(string num)
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

#if NDEBUG
void DumpDist (long double x, long double y, long double z) {}
void DumpCrossProduct(
    long double x0, long double y0, long double z0,
    long double x1, long double y1, long double z1) {}
#else
void DumpDist (long double x, long double y, long double z)
{
  cout << sqrt(x*x + y*y + z*z) << endl;
}

void DumpCrossProduct(
    long double x0, long double y0, long double z0,
    long double x1, long double y1, long double z1)
{
  cout << x0 * x1 + y0 * y1 + z0 * z1 << endl;
}
#endif
void solve(int round)
{
  double A;

  cin >> setprecision(16) >> A;

  if (A < 1.414213001) { // only need 1 rotation along 1 axis
    double theta = (long double)acos(1. / A);
    // c of plane A: 0.5  0    0
    // c of plane B: 0    0.5  0
    // c of plane C: 0    0    0.5
    // rotate along z-axis
    long double x_a = 0.5 * cos(theta);
    long double y_a = 0.5 * sin(theta);
    long double z_a = 0.;
    long double x_b = 0.5 * sin(theta) * -1.0;
    long double y_b = 0.5 * cos(theta);
    long double z_b = 0.;
    long double x_c = 0.;
    long double y_c = 0.;
    long double z_c = 0.5;
    cout << "Case #" << round << ": " << endl;
    cout.precision(16);
    cout << setprecision(16) << x_a << " " << y_a << " " << z_a << endl;
    cout << setprecision(16) << x_b << " " << y_b << " " << z_b << endl;
    cout << setprecision(16) << x_c << " " << y_c << " " << z_c << endl;
  } else if (A < 1.732050001) {
    const long double SQRT_2 = sqrt(2.);
    // A = sqrt(2.) * cos(theta) + 1. * sin(theta)
    // brute-force approximate
    long double ubound = DegToRad(45);
    long double lbound = 0.;
    long double theta = (lbound + ubound) / 2.;
    long double area = SQRT_2 * cos(theta) + 1. * sin(theta);
    while (fabs(area - A) >= 0.0000000001) {
      if (area < A) {
        lbound = theta;
      } else { // area > A
        ubound = theta;
      }
      theta = (lbound + ubound) / 2.;
      area = SQRT_2 * cos(theta) + 1. * sin(theta);
    }
    double deg = RadToDeg(theta);
    DBG(deg);
    // origin
    // x_a = 0.5 * cos(45deg)
    // y_a = 0.5 * sin(45deg)
    // z_a = 0
    // x_b = -0.5 * sin(45deg)
    // y_b = 0.5 * cos(45deg)
    // z_b = 0
    // x_c = 0
    // y_c = 0
    // z_c = 0.5
    // rotate along x-axis
    double x_a = 0.5 * cos(DegToRad(45));
    double y_a = 0.5 * sin(DegToRad(45)) * cos(DegToRad(theta));
    double z_a = 0.5 * sin(DegToRad(45)) * sin(DegToRad(theta));
    double x_b = -0.5 * sin(DegToRad(45));
    double y_b = 0.5 * cos(DegToRad(45)) * cos(DegToRad(theta));
    double z_b = 0.5 * cos(DegToRad(45)) * sin(DegToRad(theta));
    double x_c = 0;
    double y_c = -0.5 * sin(DegToRad(theta));
    double z_c = 0.5 * cos(DegToRad(theta));
    cout.precision(16);
    cout << x_a << " " << y_a << " " << z_a << endl;
    cout << x_b << " " << y_b << " " << z_b << endl;
    cout << 0 << " " << y_c << " " << z_c << endl;
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
