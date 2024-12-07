#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n = 1;

  vector<string> maze;

  int x, y;

  // directions: up, right, down, left (clockwise, important for this problem).
  vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  int currentDir = 0;

  char obstacle = '#';

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int pos = s.find('^');
    if (pos != -1) {
      x = i;
      y = pos;
      s[pos] = '.';
    }
    maze.push_back(s);

    if (i == 0) {
      n = s.size();
    }
  }

  auto isInBounds = [&](int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
  };

  auto mazeCopy = maze;

  int visitedSquares = 0;

  while (isInBounds(x, y)) {
    if (maze[x][y] == obstacle) {
      break;
    }
    if (maze[x][y] == '.') {
      visitedSquares++;
    }
    maze[x][y] = 'X';
    int dx = dirs[currentDir].first;
    int dy = dirs[currentDir].second;
    int nx = x + dx;
    int ny = y + dy;
    if (!isInBounds(nx, ny)) {
      break;
    }
    if (isInBounds(nx, ny) && maze[nx][ny] != obstacle) {
      x = nx;
      y = ny;
    } else {
      currentDir = (currentDir + 1) % 4;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << maze[i] << endl;
  }

  cout << visitedSquares << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  solve();
}
