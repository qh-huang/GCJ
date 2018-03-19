#include <iostream>  // includes cin to read from stdin and cout to write to stdout
#include <sstream>

using namespace std;  // since cin and cout are both in namespace std, this saves some text

void solve(int round, string cakes, int K)
{
  //const string cakes_orig = cakes;
  // cout << "Case #" << round << ": " << cakes << " " << K << endl;
  int flip_cnt = 0;
  for (int i = 0; i < (int)cakes.size() - K + 1; i++) {
    if (cakes[i] == '-') {
      for (int k = 0; k < K; k++) {
        cakes[i+k] = (cakes[i+k] == '+')? '-' : '+';
      }
      flip_cnt++;
    }
  }
  //cout << cakes_orig << " " << K << ' '; // debug only
  if (cakes.find('-') != cakes.npos) {
    cout << "Case #" << round << ": " << "IMPOSSIBLE" << endl;
  } else {
    cout << "Case #" << round << ": " << flip_cnt << endl;
  }
}

int main() {
  int t;
  string cakes;
  int K;
  cin >> t;  // read t. cin knows that t is an int, so it reads it as such.
  for (int round = 1; round <= t; ++round) {
    cin >> cakes >> K;
    solve(round, cakes, K);
  }

  return 0;
}
