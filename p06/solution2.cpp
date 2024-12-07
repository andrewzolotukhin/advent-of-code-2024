#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n = 1;

  vector<string> maze;

  int x, y, initX, initY;

  // directions: up, right, down, left (clockwise, important for this problem).
  vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

  char obstacle = '#';

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int pos = s.find('^');
    if (pos != -1) {
      x = initX = i;
      y = initY = pos;
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

  auto hasLoop = [obstacle, isInBounds, dirs, n](vector<string> maze, int x,
                                                 int y) {
    // cout << endl << "====================" << endl;
    // for (auto k : maze)
    //   cout << k << endl;
    // cout << "====================" << endl;
    int visitedSquares = 0;
    int currentDir = 0;
    int hasLoop = false;

    while (isInBounds(x, y)) {
      if (maze[x][y] == obstacle) {
        hasLoop = false;
        break;
      }

      visitedSquares++;

      if (visitedSquares >= (n * n)) {
        hasLoop = true;
        break;
      }

      int dx = dirs[currentDir].first;
      int dy = dirs[currentDir].second;
      int nx = x + dx;
      int ny = y + dy;
      if (!isInBounds(nx, ny)) {
        hasLoop = false;
        break;
      }
      if (isInBounds(nx, ny) && maze[nx][ny] != obstacle) {
        x = nx;
        y = ny;
      } else {
        currentDir = (currentDir + 1) % 4;
      }
    }
    // cout << "--------------------" << endl;
    // for (auto k : maze)
    //   cout << k << endl;
    // cout << "====================" << endl;
    // cout << "====================" << endl;
    return hasLoop;
  };

  int result = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (maze[i][j] == obstacle || (i == initX && j == initY))
        continue;
      auto mazeCopy = maze;
      mazeCopy[i][j] = obstacle;
      if (hasLoop(mazeCopy, initX, initY)) {
        result++;
      }
    }

  cout << result << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  solve();
}
