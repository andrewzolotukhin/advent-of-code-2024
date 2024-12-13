#include <bits/stdc++.h>
using namespace std;

void walk(int x, int y, vector<vector<bool>> &visited, vector<string> &field,
          int &sides, int &area) {
  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  visited[x][y] = true;
  area++;
  auto N = field.size();
  auto M = field[0].size();

  auto isInside = [&](int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
  };

  auto good = [&](pair<int, int> dir) {
    auto nx = x + dir.first;
    auto ny = y + dir.second;
    return isInside(nx, ny) && field[nx][ny] == field[x][y];
  };

  for (int i = 0; i < directions.size(); i++) {
    auto dir1 = directions[i];
    auto dir2 = directions[(i + 1) % directions.size()];
    if (!good(dir1) && !good(dir2)) {
      sides++;
    }
    if (good(dir1) && good(dir2) &&
        !good({dir1.first + dir2.first, dir1.second + dir2.second})) {
      sides++;
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
      walk(nx, ny, visited, field, sides, area);
    }
  }
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

  int result = 0;

  vector<vector<bool>> visited(N, vector<bool>(M, false));

  for (auto i = 0; i < N; i++) {
    for (auto j = 0; j < M; j++) {
      if (visited[i][j]) {
        continue;
      }

      int area = 0, sides = 0;

      walk(i, j, visited, field, area, sides);
      cout << area << " " << sides << endl;

      result += area * sides;
    }
  }

  cout << result << endl;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
