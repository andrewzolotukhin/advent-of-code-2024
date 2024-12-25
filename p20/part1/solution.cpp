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
  bool isCheatingEnabled;
  int cheatMovesRemained;
  // vector<pair<int, int>> path;
};

long long solve(vector<string> &maze, int startX, int startY, int endX,
                int endY, int compareTo = -1, int maxCheatMoves = 1) {
  int N = maze.size();
  int M = maze[0].size();

  vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  auto getOppositeDirection = [&](int direction) {
    return (direction + 2) % directions.size();
  };

  auto isValidToVisit = [&](int x, int y, bool cheatAllowed = false) {
    return x >= 0 && x < N && y >= 0 && y < M &&
           (maze[x][y] == '.' || cheatAllowed);
  };

  vector<QueueItem> queue;

  for (int i = 0; i < directions.size(); i++) {
    int newX = startX + directions[i].first;
    int newY = startY + directions[i].second;
    int dir = getOppositeDirection(i);

    if (isValidToVisit(newX, newY)) {
      queue.push_back({
          newX, newY, dir, 1, maxCheatMoves > 0, false, maxCheatMoves
          //  , vector<pair<int, int>>{{startX, startY}, {newX, newY}}
      });
    } else {
      if (maxCheatMoves > 0 && isValidToVisit(newX, newY, true)) {
        queue.push_back({
            newX, newY, dir, 1, true, true, maxCheatMoves - 1
            // , vector<pair<int, int>>{{startX, startY}, {newX, newY}}

        });
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
      if (maxCheatMoves <= 0)
        continue;
      if (!item.isCheatingAllowed)
        continue;
      if (!item.isCheatingEnabled)
        continue;
      if (item.cheatMovesRemained < 0)
        continue;
    }

    // if (distance[item.x][item.y][item.direction] < item.distance) {
    //   // cout << "skip:" << queue.size() << "\n";
    //   continue;
    // }

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

        better++;
      }
      continue;
    }

    QueueItem nextItemTemplate;
    nextItemTemplate.isCheatingAllowed = item.isCheatingAllowed;
    nextItemTemplate.distance = item.distance + 1;
    // nextItemTemplate.path = item.path;

    if (maxCheatMoves > 0) {
      nextItemTemplate.cheatMovesRemained = item.cheatMovesRemained;
      nextItemTemplate.isCheatingEnabled = item.isCheatingEnabled;
      if (nextItemTemplate.isCheatingEnabled) {
        nextItemTemplate.cheatMovesRemained--;
      }
      nextItemTemplate.isCheatingEnabled =
          nextItemTemplate.isCheatingEnabled && (item.cheatMovesRemained > 0);

      if (nextItemTemplate.cheatMovesRemained <= 0) {
        nextItemTemplate.isCheatingAllowed = false;
      }
    }

    for (int i = 0; i < directions.size(); i++) {

      if (i == item.direction) {
        continue;
      }

      int newX = item.x + directions[i].first;
      int newY = item.y + directions[i].second;

      // if (find(nextItemTemplate.path.begin(), nextItemTemplate.path.end(),
      //          make_pair(newX, newY)) != nextItemTemplate.path.end()) {
      //   continue;
      // }

      QueueItem nextItem = nextItemTemplate;
      nextItem.x = newX;
      nextItem.y = newY;
      // nextItem.path.push_back({newX, newY});
      auto opp = getOppositeDirection(i);
      nextItem.direction = opp;

      if (isValidToVisit(newX, newY)) {
        queue.push_back(nextItem);
      } else {
        if ((nextItem.isCheatingAllowed || nextItem.isCheatingEnabled) &&
            isValidToVisit(newX, newY, true)) {
          nextItem.isCheatingEnabled = true;
          queue.push_back(nextItem);
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

  auto best = solve(maze, startX, startY, endX, endY, -1, 0);

  cout << best << '\n';

  auto answer = solve(maze, startX, startY, endX, endY, best - 100LL, 1);
  cout << answer << '\n';
}
