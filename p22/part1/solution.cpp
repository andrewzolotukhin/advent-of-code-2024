#include <bits/stdc++.h>
using namespace std;

long long solve(long long secret) {
  for (int i = 0; i < 2000; i++) {
    secret = (secret << 6) ^ secret;
    secret = secret % 16777216;
    secret = (secret >> 5) ^ secret;
    secret = secret % 16777216;
    secret = (secret << 11) ^ secret;
    secret = secret % 16777216;
  }
  return secret;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  string s;
  long long result = 0LL;

  while (getline(cin, s)) {
    long long n = stoll(s);
    result += solve(n);
  }
  cout << result << '\n';
}
