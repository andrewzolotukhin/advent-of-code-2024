#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

long long solve(int ax, int ay, int bx, int by, int x, int y) {
  const int pa = 3;
  const int pb = 1;
  const int MAX_ITERATIONS = 100;

  int aMax = min(x / ax + 1, y / ay + 1);
  if (aMax > MAX_ITERATIONS)
    aMax = MAX_ITERATIONS;

  int bMax = min(x / bx + 1, y / by + 1);
  if (bMax > MAX_ITERATIONS)
    bMax = MAX_ITERATIONS;

  long long minPrice = MAX_ITERATIONS * 10 * (pa + pb);
  bool solvable = false;

  for (long long i = 0; i <= aMax; i++) {
    for (long long j = 0; j <= bMax; j++) {
      if ((i * ax + j * bx - x == 0) && (i * ay + j * by - y == 0)) {
        long long currPrice = i * pa + j * pb;
        if (currPrice < minPrice) {
          minPrice = currPrice;
          solvable = true;
        }
      }
    }
  }

  return solvable ? minPrice : -1;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  string s;
  long long answer = 0LL;
  while (getline(cin, s)) {
    int ax, ay, bx, by, x, y;
    sscanf(s.c_str(), "Button A: X+%d, Y+%d", &ax, &ay);
    if (!getline(cin, s))
      break;

    sscanf(s.c_str(), "Button B: X+%d, Y+%d", &bx, &by);

    if (!getline(cin, s))
      break;
    sscanf(s.c_str(), "Prize: X=%d, Y=%d", &x, &y);

    auto r = solve(ax, ay, bx, by, x, y);
    if (r > 0) {
      answer += r;
    }

    if (!getline(cin, s))
      break;
  }

  cout << answer << endl;
}
