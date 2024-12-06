#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;

void solve() {
  unordered_map<int, vector<int>> before;
  // read line by line in form "%d|%d"  until blank line is met
  // and put into `before` dictionary
  string line;
  while (getline(cin, line) && !line.empty()) {
    int a, b;
    sscanf(line.c_str(), "%d|%d", &a, &b);
    if (!before.count(b)) {
      before[a] = {};
    }
    before[a].push_back(b);
  }

  vector<vector<int>> updates;

  // read updates until EOF. Every update is in its own line
  // and is a comma-separated list of numbers
  // using sscanf to parse the line
  string s;
  while (getline(cin, s) && !s.empty()) {
    vector<int> update;
    const char *p = s.c_str();
    while (*p) {
      int n;
      sscanf(p, "%d", &n);
      update.push_back(n);
      while (*p && *p != ',') {
        p++;
      }
      if (*p) {
        p++;
      }
    }
    updates.push_back(update);
  }

  int n = 0;
  int middleSum = 0;

  for (int i = 0; i < updates.size(); i++) {
    vector<int> update = updates[i];
    bool isValid = true;
    for (int j = update.size() - 1; j >= 0; j--) {
      int u = update[j];
      // if in 0..j-1 there is a number from before[u] then continue to the next
      // update
      bool found = false;
      for (int k = 0; k < j; k++) {
        // if before[u] contains update[k] then we can skip this update
        if (find(before[u].begin(), before[u].end(), update[k]) !=
            before[u].end()) {
          found = true;
          // cout << "in update #" << i << " number " << u << " appears after "
          //      << update[k] << endl;
          break;
        }
      }
      if (found) {
        isValid = false;
        break;
      }
    }

    if (isValid) {
      n++;
      middleSum += update[update.size() / 2];
    }
  }

  cout << middleSum << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  solve();
}
