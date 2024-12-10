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

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  cout << "\n";

  while (left < right) {
    if (input[left] != -1) {
      left++;
      continue;
    }
    if (input[right] == -1) {
      right--;
      continue;
    }

    int freeSpace = 1;
    int t = left + 1;
    while (input[t] == -1 && t < right) {
      freeSpace++;
      t++;
    }

    int blockSize = 1;
    t = right - 1;
    while (input[t] != -1 && input[t] == input[right] && t > left) {
      blockSize++;
      t--;
    }

    if (freeSpace < blockSize) {
      // try to find a bigger block further to the right
      int k = left + freeSpace;
      while (k < right) {
        if (input[k] != -1) {
          k++;
          continue;
        }

        int freeSpace2 = 1;
        while (input[k + freeSpace2] == -1 && k + freeSpace2 < right) {
          freeSpace2++;
        }

        if (freeSpace2 >= blockSize) {
          break;
        }
        k += freeSpace2;
      }

      if (k < right) {
        for (int i = 0; i < blockSize; i++) {
          swap(input[k + i], input[right - blockSize + 1 + i]);
        }
      }
    } else {
      for (int i = 0; i < blockSize; i++) {
        swap(input[left + i], input[right - blockSize + 1 + i]);
      }
      left += blockSize;
    }

    right -= blockSize;

    // swap(input[left], input[right]);
    // left++;
    // right--;
  }

  for (int i = 0; i < input.size(); i++) {
    cout << input[i] << " ";
  }
  cout << "\n";

  for (int i = 0; i < input.size(); i++) {
    if (input[i] == -1) {
      continue;
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
