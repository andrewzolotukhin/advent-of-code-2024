#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;

void solve() {
  // read lines from cin until EOF and save to a vector
  vector<string> lines;
  for (string line; getline(cin, line);) {
    lines.push_back(line);
  }

  int N = lines.size();
  int M = lines[0].size();

  unordered_map<char, vector<pair<int, int>>> pos;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (lines[i][j] != '.') {
        pos[lines[i][j]].push_back({i, j});
      }
    }
  }

  auto isInBounds = [&](int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < M;
  };

  int answer = 0;
  // map for answers
  vector<vector<bool>> amap = vector<vector<bool>>(N, vector<bool>(M, false));

  for (auto [key, positions] : pos) {
    for (int i = 0; i < positions.size() - 1; i++) {
      for (int j = i + 1; j < positions.size(); j++) {
        int xDiff = positions[i].first - positions[j].first;
        int yDiff = positions[i].second - positions[j].second;

        int newX1 = positions[i].first + xDiff;
        int newY1 = positions[i].second + yDiff;

        if (isInBounds(newX1, newY1) && !amap[newX1][newY1]) {
          cout << key << " f (" << positions[i].first << ","
               << positions[i].second << ") (" << positions[j].first << ","
               << positions[j].second << ") (" << newX1 << "," << newY1 << ")"
               << endl;
          answer++;
          amap[newX1][newY1] = true;
        }

        int newX2 = positions[i].first - 2 * xDiff;
        int newY2 = positions[i].second - 2 * yDiff;

        if (isInBounds(newX2, newY2) && !amap[newX2][newY2]) {
          cout << key << " s (" << positions[i].first << ","
               << positions[i].second << ") (" << positions[j].first << ","
               << positions[j].second << ") (" << newX2 << "," << newY2 << ")"
               << endl;
          answer++;
          amap[newX2][newY2] = true;
        }
      }
    }
  }

  for (int i = 0; i < amap.size(); i++) {
    for (int j = 0; j < amap[i].size(); j++) {
      lines[i][j] = amap[i][j] ? '#' : lines[i][j];
    }
  }

  for (int i = 0; i < lines.size(); i++) {
    cout << lines[i] << endl;
  }

  cout << answer << '\n';
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
