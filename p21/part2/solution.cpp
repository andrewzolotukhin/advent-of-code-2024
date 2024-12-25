#include <bits/stdc++.h>
using namespace std;

pair<vector<int>, vector<int>> getChanges(long long secret) {
  vector<int> result;
  vector<int> values;
  values.push_back(secret % 10);
  for (int i = 0; i < 2000; i++) {
    secret = (secret << 6) ^ secret;
    secret = secret % 16777216;
    secret = (secret >> 5) ^ secret;
    secret = secret % 16777216;
    secret = (secret << 11) ^ secret;
    secret = secret % 16777216;
    values.push_back(secret % 10);
  }

  result.push_back(values[0]);
  for (int i = 1; i < values.size(); i++) {
    result.push_back(values[i] - values[i - 1]);
  }

  return {values, result};
}

long long solve(vector<long long> secrets) {
  vector<pair<vector<int>, vector<int>>> changes;
  for (long long secret : secrets) {
    changes.push_back(getChanges(secret));
  }

  long long maxResult = 0LL;

  for (int i = -9; i < 10; i++) {
    cout << i << ' ' << maxResult << '\n';
    for (int j = -9; j < 10; j++) {
      if (i + j < -9 || i + j > 9)
        continue;
      for (int k = -9; k < 10; k++) {
        if (j + k < -9 || j + k > 9)
          continue;
        if (i + j + k < -9 || i + j + k > 9)
          continue;
        for (int l = 1; l < 10; l++) {
          long long result = 0LL;
          if (i + j + k + l > 9 || i + j + k + l <= 0) {
            continue;
          }
          // cout << i << ' ' << j << ' ' << k << ' ' << l << ' ' << maxResult
          //      << '\n';
          for (int m = 0; m < changes.size(); m++) {
            for (int n = 3; n < changes[m].first.size(); n++) {
              if (changes[m].second[n - 3] == i &&
                  changes[m].second[n - 2] == j &&
                  changes[m].second[n - 1] == k && changes[m].second[n] == l) {
                result += changes[m].first[n];
                break;
              }
            }
          }
          if (result > maxResult) {
            maxResult = result;
          }
        }
      }
    }
  }

  return maxResult;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  string s;
  long long result = 0LL;

  vector<long long> secrets;

  while (getline(cin, s)) {
    long long n = stoll(s);
    secrets.push_back(n);
  }

  result = solve(secrets);

  cout << result << '\n';
}
