#include <bits/stdc++.h>
using namespace std;

pair<int, int> walk(int x, int y, vector<vector<bool>> &visited,
                    vector<string> &field) {
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  visited[x][y] = true;
  auto N = field.size();
  auto M = field[0].size();

  auto isInside = [&](int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
  };

  auto p = 4;
  auto a = 1;

  for (auto i = 0; i < directions.size(); i++) {
    auto dx = directions[i].first;
    auto dy = directions[i].second;
    auto nx = x + dx;
    auto ny = y + dy;
    if (isInside(nx, ny) && field[nx][ny] == field[x][y]) {
      p--;
    }
  }

  for (auto i = 0; i < directions.size(); i++) {
    auto dx = directions[i].first;
    auto dy = directions[i].second;
    auto nx = x + dx;
    auto ny = y + dy;
    if (!isInside(nx, ny) || visited[nx][ny]) {
      continue;
    }
    if (field[nx][ny] == field[x][y]) {
      auto r = walk(nx, ny, visited, field);
      p += r.first;
      a += r.second;
    }
  }

  return {p, a};
}

void solve() {
  vector<string> field;

  // until EOF push_back a line to field
  string line;
  while (getline(cin, line)) {
    field.push_back(line);
  }

  int N = field.size();
  int M = field[0].size();

  vector<pair<char, pair<int, int>>> perimitersAndAreas;

  int result = 0;

  vector<vector<bool>> visited(N, vector<bool>(M, false));

  for (auto i = 0; i < N; i++) {
    for (auto j = 0; j < M; j++) {
      if (visited[i][j]) {
        continue;
      }

      auto pAndArea = walk(i, j, visited, field);

      perimitersAndAreas.push_back({field[i][j], pAndArea});
    }
  }

  for (auto v : perimitersAndAreas) {
    cout << v.first << " " << v.second.first << " " << v.second.second << endl;
    result += v.second.first * v.second.second;
  }

  cout << result << endl;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
