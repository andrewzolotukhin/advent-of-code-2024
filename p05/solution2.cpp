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
    if (!before.count(a)) {
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

  vector<int> notValid = {};

  vector<tuple<int, int>> elementsToSwap =
      vector<tuple<int, int>>(updates.size());

  auto isValidUpdate = [&](vector<int> update, int index) {
    //
    for (int i = 0; i < update.size() - 1; i++) {
      for (int j = i + 1; j < update.size(); j++) {
        if (before[update[j]].size() > 0) {
          for (auto k : before[update[j]]) {
            if (k == update[i]) {
              elementsToSwap[index] = make_tuple(i, j);
              return false;
            }
          }
        }
      }
    }
    return true;
  };

  for (int i = 0; i < updates.size(); i++) {
    vector<int> update = updates[i];
    if (!isValidUpdate(update, i)) {
      notValid.push_back(i);
    }
  }

  for (auto i : notValid) {
    do {
      auto tup = elementsToSwap[i];
      // swap elements in updates[i]
      swap(updates[i][get<0>(tup)], updates[i][get<1>(tup)]);
    } while (!isValidUpdate(updates[i], i));
  }

  for (auto u : notValid) {
    auto update = updates[u];
    for (int k : update) {
      cout << k << " ";
    }
    cout << endl;
    int middle = update.size() / 2;

    middleSum += update[middle];
  }
  cout << middleSum << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  solve();
}
