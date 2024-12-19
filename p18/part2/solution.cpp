#include <bits/stdc++.h>
#include <climits>
#include <cstdio>
#define STEP_COST 1
using namespace std;

struct QueueItem {
  int x;
  int y;
  int distance;
  int direction;
};

int solve(vector<pair<int, int>> &obstacles, int k) {
  const int N = 71;
  const int M = 71;

  vector<vector<char>> maze = vector<vector<char>>(N, vector<char>(M, '.'));

  for (int i = 0; i < min(k, (int)obstacles.size()); i++) {
    auto obstacle = obstacles[i];
    maze[obstacle.second][obstacle.first] = '#';
  }

  int fromX = 0, fromY = 0;
  int toX = N - 1, toY = M - 1;

  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  vector<vector<vector<int>>> visited = vector<vector<vector<int>>>(
      N, vector<vector<int>>(M, vector<int>(directions.size(), INT_MAX)));
  auto getOppositeDirection = [&](int dir) {
    return (dir + 2) % directions.size();
  };
  auto isGoodToVisit = [&](int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M && maze[x][y] != '#';
  };

  vector<QueueItem> queue;

  for (int i = 0; i < directions.size(); i++) {
    visited[fromX][fromY][i] = 0;
    auto newX = fromX + directions[i].first;
    auto newY = fromY + directions[i].second;
    if (isGoodToVisit(newX, newY)) {
      QueueItem item = {newX, newY, STEP_COST};
      item.direction = getOppositeDirection(i);
      queue.push_back(item);
    }
  }

  int best = INT_MAX;

  // for (auto row : maze) {
  //   for (auto cell : row) {
  //     cout << cell;
  //   }
  //   cout << '\n';
  // }

  while (!queue.empty()) {
    QueueItem item = queue.back();
    queue.pop_back();
    // cout << "visiting " << item.x << " " << item.y << " " << item.direction
    //      << " " << item.distance << '\n';
    // if (visited[item.x][item.y][item.direction] <= item.distance) {
    //   // it's not optimal to visit this cell, just skip it
    //   continue;
    // }

    visited[item.x][item.y][item.direction] = item.distance;

    int forwardDirection = getOppositeDirection(item.direction);
    int leftDirection = (item.direction - 1) % directions.size();
    int rightDirection = (item.direction + 1) % directions.size();

    // if (item.distance > best) {
    //   continue;
    // }

    if (item.x == toX && item.y == toY) {
      if (item.distance < best) {
        best = item.distance;
        // break;
        continue;
      }
    }

    vector<pair<pair<int, int>, int>> directionsToCheck = {
        {directions[forwardDirection], forwardDirection},
        {directions[leftDirection], leftDirection},
        {directions[rightDirection], rightDirection}};

    for (auto d : directionsToCheck) {
      if (isGoodToVisit(item.x + d.first.first, item.y + d.first.second)) {
        int newDistance = item.distance + STEP_COST;
        QueueItem newItem = {item.x + d.first.first, item.y + d.first.second,
                             newDistance};
        newItem.direction = getOppositeDirection(d.second);
        queue.push_back(newItem);
      }
    }
  }

  return best;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);
  vector<pair<int, int>> obstacles;

  string s;

  while (getline(cin, s)) {
    int a, b;
    sscanf(s.c_str(), "%d,%d", &a, &b);
    obstacles.push_back({a, b});
  }

  for (int i = 2800; i < obstacles.size(); i++) {
    auto res = solve(obstacles, i);
    cout << i << ": " << res << '\n';
    if (res == INT_MAX) {
      cout << obstacles[i - 1].first << " " << obstacles[i - 1].second << '\n';
      break;
    }
  }
}
