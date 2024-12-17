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
  // vector<pair<int, int>> previous;
};
const vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int getOppositeDirection(int direction) {
  return (direction + dirs.size() / 2) % dirs.size();
}

bool isGoodToVisit(vector<string> &maze, int x, int y) {
  return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() &&
         maze[x][y] != '#';
}

void countBestPath(vector<string> &maze,
                   vector<vector<vector<long long>>> &visited, int x, int y,
                   int endX, int endY, set<pair<int, int>> &result) {

  if (x == endX && y == endY) {
    result.insert({x, y});
  }

  if (result.find(make_pair(x, y)) != result.end()) {
    return;
  }

  vector<int> candidates;
  long long minSoFar = LONG_LONG_MAX;

  cout << "in countBestPath " << x << " " << y << endl;

  for (int i = 0; i < dirs.size(); i++) {
    cout << "checking " << x + dirs[i].first << " " << y + dirs[i].second << " "
         << i << " "
         << visited[x + dirs[i].first][y + dirs[i].second]
                   [getOppositeDirection(i)]
         << endl;

    if (visited[x + dirs[i].first][y + dirs[i].second]
               [getOppositeDirection(i)] < minSoFar) {
      minSoFar = visited[x + dirs[i].first][y + dirs[i].second]
                        [getOppositeDirection(i)];
      candidates.clear();
      candidates.push_back(i);
    } else {
      if (visited[x + dirs[i].first][y + dirs[i].second]
                 [getOppositeDirection(i)] < LONG_LONG_MAX &&
          visited[x + dirs[i].first][y + dirs[i].second]
                 [getOppositeDirection(i)] == minSoFar) {
        candidates.push_back(i);
      }
    }
  }

  if (minSoFar < LONG_LONG_MAX) {
    cout << " candidates: ";
    for (auto c : candidates) {
      cout << c << ": "
           << visited[x + dirs[c].first][y + dirs[c].second]
                     [getOppositeDirection(c)]
           << ", ";
    }
    cout << endl;
    for (auto d : candidates) {
      // visited[x][y][getOppositeDirection(d)] = LONG_LONG_MAX;
      result.insert({x, y});
      auto newX = x + dirs[d].first;
      auto newY = y + dirs[d].second;
      // cout << "new x " << newX << " new y " << newY << endl;
      if (isGoodToVisit(maze, newX, newY) &&
          result.find(make_pair(newX, newY)) == result.end()) {
        countBestPath(maze, visited, newX, newY, endX, endY, result);
      }
    }
  }
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
    // item.previous = {};
    itemsToVisit.push_back(item);
  }

  set<pair<int, int>> result;

  while (!itemsToVisit.empty()) {
    auto item = itemsToVisit.front();
    itemsToVisit.erase(itemsToVisit.begin());
    // cout << "looking at x: " << item.x << " y: " << item.y
    //      << " dir: " << item.direction << " cost: " << item.cost << endl;
    auto opp = getOppositeDirection(item.direction);

    auto leftDirection = (opp + dirs.size() - 1) % dirs.size();
    auto rightDirection = (opp + 1) % dirs.size();

    visited[item.x][item.y][item.direction] = item.cost;
    long long best = LONG_LONG_MAX;

    // if (item.x == end.first && item.y == end.second) {
    //   cout << "result: " << visited[item.x][item.y][item.direction] << endl;
    //
    //   if (visited[item.x][item.y][item.direction] < best) {
    //     // cout << "cearing result " <<
    //     visited[item.x][item.y][item.direction]
    //     //      << " " << res << endl;
    //     result.clear();
    //     best = visited[item.x][item.y][item.direction];
    //   }
    //   if (visited[item.x][item.y][item.direction] <= best) {
    //     // cout << "new path: " << visited[item.x][item.y][item.direction] <<
    //     "
    //     // "
    //     //      << res << endl;
    //     for (auto p : item.previous) {
    //       // cout << "adding " << p.first << " " << p.second << endl;
    //       result.insert({p.first, p.second});
    //     }
    //
    //     // create a copy of the maze
    //     vector<string> mazeCopy = maze;
    //     for (auto p : result) {
    //       mazeCopy[p.first][p.second] = 'O';
    //     }
    //
    //     for (auto m : mazeCopy) {
    //       cout << m << endl;
    //     }
    //   }
    // }

    // if (visited[item.x][item.y][item.direction] < item.cost) {
    //   continue;
    // }
    //

    if (isGoodToVisit(maze, item.x + dirs[opp].first,
                      item.y + dirs[opp].second) &&
        visited[item.x + dirs[opp].first][item.y + dirs[opp].second]
               [item.direction] > item.cost + MOVE_COST) {
      QueueItem newItem;
      newItem.cost = item.cost + MOVE_COST;
      newItem.x = item.x + dirs[opp].first;
      newItem.y = item.y + dirs[opp].second;

      // if (find(item.previous.begin(), item.previous.end(),
      //          make_pair(newItem.x, newItem.y)) == item.previous.end()) {
      newItem.direction = item.direction;
      // newItem.previous = item.previous;
      // newItem.previous.push_back({item.x, item.y});
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;
      itemsToVisit.push_back(newItem);
      // }
    }

    if (isGoodToVisit(maze, item.x + dirs[leftDirection].first,
                      item.y + dirs[leftDirection].second) &&
        visited[item.x + dirs[leftDirection].first]
               [item.y + dirs[leftDirection].second]
               [getOppositeDirection(leftDirection)] >
            item.cost + (TURN_COST + MOVE_COST)) {
      QueueItem newItem;
      newItem.cost = item.cost + (TURN_COST + MOVE_COST);
      newItem.x = item.x + dirs[leftDirection].first;
      newItem.y = item.y + dirs[leftDirection].second;

      // if (find(item.previous.begin(), item.previous.end(),
      //          make_pair(newItem.x, newItem.y)) == item.previous.end()) {
      newItem.direction = getOppositeDirection(leftDirection);
      // newItem.previous = item.previous;
      // newItem.previous.push_back({item.x, item.y});
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;
      itemsToVisit.push_back(newItem);
      // }
    }

    if (isGoodToVisit(maze, item.x + dirs[rightDirection].first,
                      item.y + dirs[rightDirection].second) &&
        visited[item.x + dirs[rightDirection].first]
               [item.y + dirs[rightDirection].second]
               [getOppositeDirection(rightDirection)] >
            item.cost + (TURN_COST + MOVE_COST)) {
      // visited[item.x][item.y][rightDirection] = item.cost;
      QueueItem newItem;
      newItem.cost = item.cost + (TURN_COST + MOVE_COST);
      newItem.x = item.x + dirs[rightDirection].first;
      newItem.y = item.y + dirs[rightDirection].second;
      // if (find(item.previous.begin(), item.previous.end(),
      //          make_pair(newItem.x, newItem.y)) == item.previous.end()) {
      newItem.direction = getOppositeDirection(rightDirection);
      // newItem.previous = item.previous;
      // newItem.previous.push_back({item.x, item.y});
      // cout << "adding " << newItem.x << " " << newItem.y << " "
      //      << newItem.direction << " " << newItem.cost << endl;

      itemsToVisit.push_back(newItem);
      // }
    }
    cout << itemsToVisit.size() << endl;
  }

  long long res = LONG_LONG_MAX;
  for (int i = 0; i < dirs.size(); i++) {
    res = min(res, visited[end.first][end.second][i]);
  }

  cout << "res: " << res << endl;

  // for (int i = 0; i < dirs.size(); i++) {
  //   visited[start.first][start.second][i] = LONG_LONG_MAX;
  // }

  // countBestPath(maze, visited, start.first, start.second, end.first,
  // end.second,
  //               result);

  return result.size();
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
