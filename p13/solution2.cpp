#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

long long solve(long long ax, long long ay, long long bx, long long by,
                long long x, long long y) {
  const long long pa = 3;
  const long long pb = 1;

  if ((x * ay - y * ax) % (ay * bx - ax * by)) {
    return -1;
  }

  long long m = (x * ay - y * ax) / (ay * bx - ax * by);
  if (m < 0)
    return -1;

  if ((y - by * m) % ay) {
    return -1;
  }

  long long n = (y - by * m) / ay;

  if (n < 0)
    return -1;

  return pa * n + pb * m;
}

int main() {
  string s;
  long long answer = 0LL;
  const long long INCREMENT = 10000000000000LL;
  while (getline(cin, s)) {
    long long ax, ay, bx, by, x, y;
    sscanf(s.c_str(), "Button A: X+%lld, Y+%lld", &ax, &ay);
    if (!getline(cin, s))
      break;

    sscanf(s.c_str(), "Button B: X+%lld, Y+%lld", &bx, &by);

    if (!getline(cin, s))
      break;
    sscanf(s.c_str(), "Prize: X=%lld, Y=%lld", &x, &y);

    auto r = solve(ax, ay, bx, by, x + INCREMENT, y + INCREMENT);
    if (r > 0) {
      answer += r;
    }

    if (!getline(cin, s))
      break;
  }

  cout << answer << endl;
}
