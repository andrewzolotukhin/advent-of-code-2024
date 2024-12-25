#include <bits/stdc++.h>
#include <climits>
#include <utility>

using namespace std;

struct QueueItem {
  int x;
  int y;
  int direction;
  long long distance;
  bool isCheatingAllowed;
  vector<pair<pair<int, int>, int>> path;
};

vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int getOppositeDirection(int direction) {
  return (direction + 2) % directions.size();
};

vector<pair<pair<int, int>, pair<int, int>>>
getCheats(vector<string> &maze, int x, int y, int maxDistance) {
  int N = maze.size();
  int M = maze[0].size();
  if (maze[x][y] != '#')
    return vector<pair<pair<int, int>, pair<int, int>>>();

  vector<QueueItem> queue;

  vector<vector<vector<int>>> distances(
      N, vector<vector<int>>(M, vector<int>(directions.size(), INT_MAX)));

  for (int i = 0; i < directions.size(); i++) {
    distances[x][y][i] = 0;
    queue.push_back({x, y, i, 0, false});
  }

  set<pair<int, int>> reachable;

  while (!queue.empty()) {

    QueueItem item = queue.front();
    queue.erase(queue.begin());

    if (item.distance > maxDistance ||
        item.distance > distances[item.x][item.y][item.direction]) {
      continue;
    }

    if (item.distance < distances[item.x][item.y][item.direction]) {
      distances[item.x][item.y][item.direction] = item.distance;
    }

    if (maze[item.x][item.y] != '#') {
      reachable.insert({item.x, item.y});
      continue;
    }

    for (int i = 0; i < directions.size(); i++) {
      if (getOppositeDirection(i) == item.direction) {
        continue;
      }

      QueueItem forwardItem = item;
      forwardItem.x += directions[i].first;
      forwardItem.y += directions[i].second;
      forwardItem.distance += 1;
      forwardItem.direction = i;
      if (forwardItem.x >= 0 && forwardItem.x < N && forwardItem.y >= 0 &&
          forwardItem.y < M) {
        queue.push_back(forwardItem);
      }
    }
  }

  vector<pair<pair<int, int>, pair<int, int>>> result;

  for (auto p : reachable) {
    int minDir = INT_MAX;
    int minDist = INT_MAX;
    for (int i = 0; i < directions.size(); i++) {
      if (distances[p.first][p.second][i] < minDist) {
        minDist = distances[p.first][p.second][i];
        minDir = i;
      }
    }
    result.push_back({p, {minDist, minDir}});
  }

  return result;
}

long long
solve(vector<string> &maze,
      vector<vector<vector<pair<pair<int, int>, pair<int, int>>>>> &cheats,
      int startX, int startY, int endX, int endY, int compareTo = -1,
      bool cheatsEnabled = true) {
  int N = maze.size();
  int M = maze[0].size();

  auto isValidToVisit = [&](int x, int y, bool cheatAllowed = false) {
    return x >= 0 && x < N && y >= 0 && y < M &&
           (maze[x][y] == '.' || cheatAllowed);
  };

  vector<QueueItem> queue;

  bool cheatsApplied = false;

  for (int i = 0; i < directions.size(); i++) {
    int newX = startX + directions[i].first;
    int newY = startY + directions[i].second;
    int dir = getOppositeDirection(i);

    if (isValidToVisit(newX, newY)) {
      queue.push_back(
          {newX, newY, dir, 1, cheatsEnabled, {{{startX, startY}, 0}}});
    } else {
      if (cheatsEnabled && !cheatsApplied && isValidToVisit(newX, newY, true)) {
        cout << startX << " " << startY << " " << cheats[startX][startY].size()
             << '\n';
        for (auto cheat : cheats[startX][startY]) {
          int cx = cheat.first.first;
          int cy = cheat.first.second;
          int d = cheat.second.first;
          int dr = cheat.second.second;
          if (cx != startX || cy != startY) {
            cout << "cheat from: " << startX << " " << startY << " to: " << cx
                 << " " << cy << " " << d << " " << dr << '\n';
            queue.push_back({cx, cy, dr, d, false, {{{startX, startY}, 0}}});
          }
        }
        cheatsApplied = true;
      }
    }
  }

  vector<vector<vector<long long>>> distance(
      N, vector<vector<long long>>(
             M, vector<long long>(directions.size(), LONG_LONG_MAX)));

  long long best = LONG_LONG_MAX;
  long long better = 0LL;

  while (!queue.empty()) {
    QueueItem item = queue.back();
    queue.pop_back();

    if (maze[item.x][item.y] == '#') {
      if (!cheatsEnabled)
        continue;
      if (!item.isCheatingAllowed)
        continue;
    }

    if (distance[item.x][item.y][item.direction] < item.distance) {
      // cout << "skip:" << queue.size() << "\n";
      continue;
    }

    // if(maze[item.x][item.y] == '#')

    distance[item.x][item.y][item.direction] =
        (compareTo != -1 && item.distance < compareTo) ? compareTo
                                                       : item.distance;

    if (compareTo != -1 && item.distance > compareTo) {
      // cout << "exit:" << queue.size() << "\n";
      continue;
    }

    if (item.x == endX && item.y == endY) {
      best = min(best, item.distance);
      if (item.distance <= compareTo) {
        // cout << "Better: " << (compareTo - item.distance) << '\n';
        // auto copy = maze;
        //
        // for (auto p : item.path) {
        //   copy[p.first][p.second] = maze[p.first][p.second] == '#' ? 'C' :
        //   'O';
        // }
        //
        // for (int i = 0; i < copy.size(); i++) {
        //   for (int j = 0; j < copy[0].size(); j++) {
        //     cout << copy[i][j];
        //   }
        //   cout << '\n';
        // }
        // cout << "======================\n";
        //
        cout << "Better: " << item.distance << " " << compareTo << " "
             << (compareTo - item.distance) << " " << item.x << " " << item.y
             << " " << item.direction << '\n';
        item.path.push_back({{item.x, item.y}, item.direction});
        for (auto p : item.path) {
          cout << "(" << p.first.first << ", " << p.first.second << ", "
               << p.second << ") => ";
        }
        cout << '\n';

        better++;
      }
      continue;
    }

    QueueItem nextItemTemplate;
    nextItemTemplate.isCheatingAllowed = item.isCheatingAllowed;
    nextItemTemplate.distance = item.distance;
    nextItemTemplate.path = item.path;
    nextItemTemplate.path.push_back({{item.x, item.y}, item.direction});

    for (int i = 0; i < directions.size(); i++) {

      if (i == item.direction) {
        continue;
      }

      int newX = item.x + directions[i].first;
      int newY = item.y + directions[i].second;

      QueueItem nextItem = nextItemTemplate;
      nextItem.x = newX;
      nextItem.y = newY;
      // nextItem.path.push_back({newX, newY});
      auto opp = getOppositeDirection(i);
      nextItem.direction = opp;

      if (isValidToVisit(newX, newY)) {
        nextItem.distance += 1;
        queue.push_back(nextItem);
      } else {
        if (cheatsEnabled && item.isCheatingAllowed &&
            isValidToVisit(newX, newY)) {
          for (auto c : cheats[newX][newY]) {
            auto cx = c.first.first;
            auto cy = c.first.second;
            auto cdist = c.second.first;
            auto cdir = c.second.second;
            if (cx == item.x && cy == item.y) {
              continue;
            }
            QueueItem cItem;
            cItem.x = cx;
            cItem.y = cy;
            cItem.direction = cdir;
            cItem.distance = item.distance + cdist;
            cItem.isCheatingAllowed = false;
            cItem.path = item.path;
            cItem.path.push_back({{item.x, item.y}, item.direction});
            // cout << "cheat from 2: " << item.x << " " << item.y << " to: " <<
            // cx
            //      << " " << cy << " " << cdist << " " << cdir << '\n';
            queue.push_back(cItem);
          }
        }
      }
    }
  }

  return compareTo != -1 ? better : best;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  vector<string> maze;
  string s;
  int startX, startY, endX, endY;

  while (getline(cin, s)) {
    maze.push_back(s);
  }

  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[0].size(); j++) {
      if (maze[i][j] == 'S') {
        maze[i][j] = '.';
        startX = i;
        startY = j;
      }
      if (maze[i][j] == 'E') {
        maze[i][j] = '.';
        endX = i;
        endY = j;
      }
    }
  }

  auto cheats = vector<vector<vector<pair<pair<int, int>, pair<int, int>>>>>(
      maze.size(),
      vector<vector<pair<pair<int, int>, pair<int, int>>>>(
          maze[0].size(), vector<pair<pair<int, int>, pair<int, int>>>()));

  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[0].size(); j++) {
      if (maze[i][j] == '#') {
        auto shouldCalculate = false;
        for (int i = 0; i < directions.size(); i++) {
          auto newX = i + directions[i].first;
          auto newY = j + directions[i].second;
          if (i >= 0 && i < maze.size() && j >= 0 && j < maze[0].size()) {
            if (maze[newX][newY] != '#') {
              shouldCalculate = true;
              break;
            }
          }
        }
        if (shouldCalculate) {
          cout << "Calculating: " << i << " " << j << '\n';
          cheats[i][j] = getCheats(maze, i, j, 20);
        }
      }
    }
  }

  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[0].size(); j++) {
      if (maze[i][j] != '#') {
        vector<pair<pair<int, int>, pair<int, int>>> res;
        vector<pair<pair<int, int>, pair<int, int>>> res2;
        for (int i = 0; i < directions.size(); i++) {
          auto newX = i + directions[i].first;
          auto newY = j + directions[i].second;
          if (i >= 0 && i < maze.size() && j >= 0 && j < maze[0].size()) {
            if (maze[newX][newY] == '#') {
              for (auto c : cheats[newX][newY]) {
                auto copy = c;
                res.push_back(copy);
              }

              // let's remove duplicates -
              // for every unique pair (first.first, first.second)
              // keeping only the shortest path
              // (where second.first is minimal)
              // first we can sort everything by first.first, first.second and
              // second.first and take only the first element for each unique
              // pair

              sort(res.begin(), res.end(), [](auto a, auto b) {
                if (a.first.first == b.first.first) {
                  if (a.first.second == b.first.second) {
                    return a.second.first < b.second.first;
                  }
                  return a.first.second < b.first.second;
                }
                return a.first.first < b.first.first;
              });

              for (int i = 1; i < res.size(); i++) {
                if (res[i].first.first == res[i - 1].first.first &&
                    res[i].first.second == res[i - 1].first.second) {
                  continue;
                }
                res2.push_back(res[i]);
              }
            }
          }
        }
        cheats[i][j] = res2;
      }
    }
  }

  cout << "1,1 cheats: " << cheats[1][1].size() << '\n';

  // for (auto c : cheats[0][0]) {
  //   cout << c.first.first << " " << c.first.second << " " << c.second.first
  //        << " " << c.second.second << '\n';
  // }

  auto best = solve(maze, cheats, startX, startY, endX, endY, -1, false);

  cout << best << '\n';

  auto answer =
      solve(maze, cheats, startX, startY, endX, endY, best - 76LL, true);
  cout << answer << '\n';
}
