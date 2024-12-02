#include <bits/stdc++.h>
using namespace std;

void solve() {
  vector<int> a, b;
  int n = 1000;

  while (n--) {
    int x;
    cin >> x;
    a.push_back(x);
    cin >> x;
    b.push_back(x);
  }

  // sort both arrays in ascending order
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  // calculate difference between each pair of elements
  // and sum them up
  // this is the answer
  int ans = 0;
  for (int i = 0; i < a.size(); i++) {
    ans += abs(a[i] - b[i]);
  }

  cout << ans << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  solve();
}
