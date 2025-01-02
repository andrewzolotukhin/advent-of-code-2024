#include <bits/stdc++.h>
#define COLS 5
#define ROWS 7
using namespace std;

long long C(int n, int r) {
  if (r > n) {
    return 0;
  }

  if (r * 2 > n) {
    r = n - r;
  }

  if (r == 0) {
    return 1;
  }

  long long result = n;
  for (int i = 2; i <= r; ++i) {
    result *= (n - i + 1);
    result /= i;
  }
  return result;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);
  //

  string line;

  vector<vector<int>> pins, locks;

  int count = 0;
  int index = 0;

  vector<string> current;

  while (getline(cin, line)) {
    if (line == "")
      continue;

    current.push_back(line);
    // cout << line << endl;
    index = (index + 1) % ROWS;

    if (index == 0) {
      count++;
      if (current.size() == ROWS) {
        bool isLock = false;
        for (int i = 0; i < COLS; i++) {
          if (current[0][i] != '#') {
            isLock = true;
            break;
          }
        }

        vector<int> pinOrLock;

        for (int i = 0; i < COLS; i++) {
          int sum = 0;
          for (int j = 0; j < ROWS; j++) {
            if (current[j][i] == '#') {
              sum++;
            }
          }
          pinOrLock.push_back(sum);
        }

        if (isLock) {
          locks.push_back(pinOrLock);
        } else {
          pins.push_back(pinOrLock);
        }
      }
      current.clear();
    }
  }

  long long result = 0L;

  cout << "Pins: " << pins.size() << endl;
  cout << "Locks: " << locks.size() << endl;

  for (auto pin : pins) {
    for (auto lock : locks) {
      bool match = true;

      for (int i = 0; i < COLS; i++) {
        if (pin[i] + lock[i] > ROWS) {
          match = false;
          break;
        }
      }
      if (match) {
        result++;
      }
    }
  }

  cout << "Result: " << result << endl;
}
