#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s;
  // const int W = 11, H = 7, STEPS = 5;
  const int W = 101, H = 103, STEPS = 100;
  const int MW = W / 2;
  const int MH = H / 2;

  auto getQuadrant = [&](int x, int y) {
    if ((x == MW) || (y == MH))
      return 0;
    if (x > MW && y < MH)
      return 1;
    if (x < MW && y < MH)
      return 2;
    if (x < MW && y > MH)
      return 3;
    if (x > MW && y > MH)
      return 4;
    return 0;
  };

  vector<int> robotsPerQuadrant(5, 0);

  while (getline(cin, s)) {
    int x, y, vx, vy;
    sscanf(s.c_str(), "p=%d,%d v=%d,%d", &x, &y, &vx, &vy);
    auto newx = (x + STEPS * vx) % W;
    auto newy = (y + STEPS * vy) % H;
    if (newx < 0)
      newx += W;
    if (newy < 0)
      newy += H;

    auto quadrant = getQuadrant(newx, newy);

    cout << quadrant << '\n';

    if (quadrant) {
      robotsPerQuadrant[quadrant]++;
    }
  }

  int result = 1;

  for (int i = 1; i < 5; i++) {
    if (robotsPerQuadrant[i]) {
      result *= robotsPerQuadrant[i];
    }
  }

  cout << result << '\n';
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
