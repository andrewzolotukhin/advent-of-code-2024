#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <vector>

#define TURN_COST 1000LL
#define MOVE_COST 1LL

using namespace std;

struct QueueItem {
  long long cost;
  int x;
  int y;
  int direction;
  vector<pair<int, int>> previous;
};

bool isGoodToVisit(vector<string> &maze, int x, int y) {
  bool result = x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() &&
                maze[x][y] != '#';
  // cout << "checking " << x << " " << y << " " << result << endl;
  return result;
}

const vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int getOppositeDirection(int direction) {
  return (direction + dirs.size() / 2) % dirs.size();
}

long long solve(vector<string> &maze, pair<int, int> start,
                pair<int, int> end) {
  const int N = maze.size();
  const int M = maze[0].size();
  const int initDirection = 0;
  vector<vector<vector<long long>>> visited = vector<vector<vector<long long>>>(
      N, vector<vector<long long>>(
             M, vector<long long>(dirs.size(), LONG_LONG_MAX)));

  vector<QueueItem> itemsToVisit;
  if (!isGoodToVisit(maze, start.first, start.second) ||
      !isGoodToVisit(maze, end.first, end.second)) {
    return -1;
  }

  for (int i = 0; i < dirs.size(); i++) {
    visited[start.first][start.second][i] = 0;
    int x = start.first + dirs[i].first;
    int y = start.second + dirs[i].second;
    if (!isGoodToVisit(maze, x, y)) {
      continue;
    }
    QueueItem item;
    item.cost = (i == initDirection ? MOVE_COST : (TURN_COST + MOVE_COST));
    item.direction = getOppositeDirection(i);
    item.x = x;
    item.y = y;
    item.previous = {{start.first, start.second}};
    itemsToVisit.push_back(item);
  }

  long long best = 100'000;
  set<pair<int, int>> visitedPoints;

  while (!itemsToVisit.empty()) {
    auto item = itemsToVisit.back();
    itemsToVisit.erase(itemsToVisit.end());

    // cout << "visiting " << item.x << " " << item.y << " " << item.cost << " "
    //      << item.previous.size() << " " << best << endl;

    auto direction = getOppositeDirection(item.direction);
    auto leftDirection = (direction + dirs.size() - 1) % dirs.size();
    auto rightDirection = (direction + 1) % dirs.size();

    if (item.x == end.first && item.y == end.second) {
      if (item.cost < best) {
        best = item.cost;
        visitedPoints.clear();
        cout << "======================\n";
      }
      if (item.cost == best) {
        for (auto p : item.previous) {
          visitedPoints.insert(p);
        }
        visitedPoints.insert(end);
      }
      continue;
    }

    if (isGoodToVisit(maze, item.x + dirs[direction].first,
                      item.y + dirs[direction].second) &&
        visited[item.x + dirs[direction].first][item.y + dirs[direction].first]
               [item.direction] >= item.cost + MOVE_COST - 20000 &&
        item.cost < best &&
        find(item.previous.begin(), item.previous.end(),
             make_pair(item.x + dirs[direction].first,
                       item.y + dirs[direction].second)) ==
            item.previous.end()) {
      visited[item.x][item.y][item.direction] = item.cost;
      QueueItem newItem;
      newItem.cost = item.cost + MOVE_COST;
      newItem.x = item.x + dirs[direction].first;
      newItem.y = item.y + dirs[direction].second;
      newItem.direction = item.direction;
      newItem.previous = vector<pair<int, int>>();
      for (auto p : item.previous) {
        newItem.previous.push_back(p);
      }
      newItem.previous.push_back({item.x, item.y});
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;
      itemsToVisit.push_back(newItem);
    }

    if (isGoodToVisit(maze, item.x + dirs[leftDirection].first,
                      item.y + dirs[leftDirection].second) &&
        visited[item.x + dirs[leftDirection].first]
               [item.y + dirs[leftDirection].second]
               [getOppositeDirection(leftDirection)] >=
            item.cost + (TURN_COST + MOVE_COST) &&
        item.cost < best &&
        find(item.previous.begin(), item.previous.end(),
             make_pair(item.x + dirs[leftDirection].first,
                       item.y + dirs[leftDirection].second)) ==
            item.previous.end()) {
      visited[item.x][item.y][item.direction] = item.cost;
      QueueItem newItem;
      newItem.cost = item.cost + (TURN_COST + MOVE_COST);
      newItem.x = item.x + dirs[leftDirection].first;
      newItem.y = item.y + dirs[leftDirection].second;
      newItem.direction = getOppositeDirection(leftDirection);
      newItem.previous = vector<pair<int, int>>();
      for (auto p : item.previous) {
        newItem.previous.push_back(p);
      }
      newItem.previous.push_back({item.x, item.y});
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;
      itemsToVisit.push_back(newItem);
    }

    if (isGoodToVisit(maze, item.x + dirs[rightDirection].first,
                      item.y + dirs[rightDirection].second) &&
        visited[item.x + dirs[rightDirection].first]
               [item.y + dirs[rightDirection].second]
               [getOppositeDirection(rightDirection)] >=
            item.cost + (TURN_COST + MOVE_COST) &&
        item.cost < best &&
        find(item.previous.begin(), item.previous.end(),
             make_pair(item.x + dirs[rightDirection].first,
                       item.y + dirs[rightDirection].second)) ==
            item.previous.end()) {
      visited[item.x][item.y][item.direction] = item.cost;
      QueueItem newItem;
      newItem.cost = item.cost + (TURN_COST + MOVE_COST);
      newItem.x = item.x + dirs[rightDirection].first;
      newItem.y = item.y + dirs[rightDirection].second;
      newItem.direction = getOppositeDirection(rightDirection);
      newItem.previous = vector<pair<int, int>>();
      for (auto p : item.previous) {
        newItem.previous.push_back(p);
      }
      newItem.previous.push_back({item.x, item.y});
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;

      itemsToVisit.push_back(newItem);
    }
  }

  long long result = LONG_LONG_MAX;
  for (int i = 0; i < dirs.size(); i++) {
    result = min(result, visited[end.first][end.second][i]);
  }

  cout << "Best: " << best << endl;
  cout << "Visited total: " << visitedPoints.size() << endl;

  return result;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  vector<string> maze;

  string line;

  pair<int, int> start, end;

  while (getline(cin, line)) {
    auto si = line.find('S');
    if (si != string::npos) {
      start = {maze.size(), si};
    }

    auto ei = line.find('E');
    if (ei != string::npos) {
      end = {maze.size(), ei};
    }
    maze.push_back(line);
  }

  auto result = solve(maze, start, end);

  cout << result << '\n';
}
