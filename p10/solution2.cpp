#include <bits/stdc++.h>
#include <cstring>
using namespace std;

bool isInside(int i, int j, int N, int M) {
  return (i >= 0 && i < N && j >= 0 && j < M);
}

void tryWalk(vector<string> &field, int i, int j, int N, int M, int *result,
             vector<vector<bool>> &mem) {
  cout << i << " " << j << " " << field[i][j] << endl;
  if (field[i][j] == '9') {
    (*result)++;
    mem[i][j] = true;
    cout << "found " << i << " " << j << " " << field[i][j] << endl;
    return;
  }

  mem[i][j] = true;

  if (isInside(i + 1, j, N, M) && (field[i + 1][j] == field[i][j] + 1)) {
    tryWalk(field, i + 1, j, N, M, result, mem);
  }

  if (isInside(i - 1, j, N, M) && (field[i - 1][j] == field[i][j] + 1)) {
    tryWalk(field, i - 1, j, N, M, result, mem);
  }

  if (isInside(i, j + 1, N, M) && (field[i][j + 1] == field[i][j] + 1)) {
    tryWalk(field, i, j + 1, N, M, result, mem);
  }

  if (isInside(i, j - 1, N, M) && (field[i][j - 1] == field[i][j] + 1)) {
    tryWalk(field, i, j - 1, N, M, result, mem);
  }
}

void solve() {
  vector<string> field;
  // read until EOF and push_back to field
  string s;
  while (getline(cin, s)) {
    field.push_back(s);
  }

  for (auto s : field) {
    cout << s << endl;
  }

  int N = field.size();
  int M = field[0].size();

  int result = 0;
  vector<vector<bool>> mem = vector<vector<bool>>(N, vector<bool>(M, false));

  for (auto i = 0; i < N; i++) {
    for (auto j = 0; j < M; j++) {
      if (field[i][j] == '0') {
        mem = vector<vector<bool>>(N, vector<bool>(M, false));
        tryWalk(field, i, j, N, M, &result, mem);
      }
    }
  }
  cout << result << endl;
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
