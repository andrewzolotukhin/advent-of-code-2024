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
    item.direction = i;
    item.x = x;
    item.y = y;
    itemsToVisit.push_back(item);
  }

  while (!itemsToVisit.empty()) {
    auto item = itemsToVisit.front();
    itemsToVisit.erase(itemsToVisit.begin());
    // cout << "looking at x: " << item.x << " y: " << item.y
    //      << " dir: " << item.direction << " cost: " << item.cost << endl;

    auto leftDirection = (item.direction + dirs.size() - 1) % dirs.size();
    auto rightDirection = (item.direction + 1) % dirs.size();

    if (isGoodToVisit(maze, item.x + dirs[item.direction].first,
                      item.y + dirs[item.direction].second) &&
        visited[item.x][item.y][getOppositeDirection(item.direction)] >
            item.cost + MOVE_COST) {
      visited[item.x][item.y][getOppositeDirection(item.direction)] = item.cost;
      QueueItem newItem;
      newItem.cost = item.cost + MOVE_COST;
      newItem.x = item.x + dirs[item.direction].first;
      newItem.y = item.y + dirs[item.direction].second;
      newItem.direction = item.direction;
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;
      itemsToVisit.push_back(newItem);
    }

    if (isGoodToVisit(maze, item.x + dirs[leftDirection].first,
                      item.y + dirs[leftDirection].second) &&
        visited[item.x][item.y][getOppositeDirection(leftDirection)] >
            item.cost + (TURN_COST + MOVE_COST)) {
      visited[item.x][item.y][getOppositeDirection(leftDirection)] = item.cost;
      QueueItem newItem;
      newItem.cost = item.cost + (TURN_COST + MOVE_COST);
      newItem.x = item.x + dirs[leftDirection].first;
      newItem.y = item.y + dirs[leftDirection].second;
      newItem.direction = leftDirection;
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;
      itemsToVisit.push_back(newItem);
    }

    if (isGoodToVisit(maze, item.x + dirs[rightDirection].first,
                      item.y + dirs[rightDirection].second) &&
        visited[item.x][item.y][getOppositeDirection(rightDirection)] >
            item.cost + (TURN_COST + MOVE_COST)) {
      visited[item.x][item.y][getOppositeDirection(rightDirection)] = item.cost;
      QueueItem newItem;
      newItem.cost = item.cost + (TURN_COST + MOVE_COST);
      newItem.x = item.x + dirs[rightDirection].first;
      newItem.y = item.y + dirs[rightDirection].second;
      newItem.direction = rightDirection;
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;

      itemsToVisit.push_back(newItem);
    }
  }

  long long result = LONG_LONG_MAX;
  for (int i = 0; i < dirs.size(); i++) {
    result = min(result, visited[end.first][end.second][i]);
  }

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
