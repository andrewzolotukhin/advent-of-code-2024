#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s;
  // const int W = 11, H = 7, STEPS = 5;
  const int W = 101, H = 103;
  const int MW = W / 2;
  const int MH = H / 2;

  vector<vector<char>> grid(H, vector<char>(W, '.'));

  vector<int> x, y, vx, vy;

  while (getline(cin, s)) {
    int tx, ty, tvx, tvy;
    sscanf(s.c_str(), "p=%d,%d v=%d,%d", &tx, &ty, &tvx, &tvy);
    x.push_back(tx);
    y.push_back(ty);
    vx.push_back(tvx);
    vy.push_back(tvy);
  }

  unsigned long long step = 0;

  while (step++ < 1'000'000'000) {

    for (int i = 0; i < x.size(); i++) {
      x[i] += vx[i];
      y[i] += vy[i];

      x[i] = (x[i] + W) % W;
      y[i] = (y[i] + H) % H;
    }

    // renew grid
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        grid[i][j] = '.';
      }
    }

    for (int i = 0; i < x.size(); i++) {
      grid[y[i]][x[i]] = 'X';
    }

    // clear console
    // cout << "\033[2J\033[1;1H";
    cout << "Step: " << step << endl;

    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        cout << grid[i][j];
      }
      cout << endl;
    }
  }
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
