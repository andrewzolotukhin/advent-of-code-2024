#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s;
  cin >> s;

  unsigned long long result = 0;

  vector<int> input;

  for (int i = 0; i < s.size(); i++) {
    for (int j = '0'; j < s[i]; j++) {
      input.push_back(((i & 1) ? -1 : (i / 2)));
    }
  }

  int left = 0;
  int right = input.size() - 1;

  while (left < right) {
    if (input[left] != -1) {
      left++;
      continue;
    }
    if (input[right] == -1) {
      right--;
      continue;
    }

    swap(input[left], input[right]);
    left++;
    right--;
  }

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  cout << "\n";

  for (int i = 0; i < input.size(); i++) {
    if (input[i] == -1) {
      break;
    }
    result += input[i] * i;
  }

  cout << result << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  solve();
}
