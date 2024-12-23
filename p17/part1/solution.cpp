#include <bits/stdc++.h>
#include <cmath>
using namespace std;

void solve() {
  int A, B, C, n;
  vector<int> program;

  cin >> A >> B >> C >> n;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    program.push_back(x);
  }

  auto readCombo = [&](int x) {
    switch (x) {
    case 4:
      return A;
    case 5:
      return B;
    case 6:
      return C;
    case 7:
      throw runtime_error("unknown combo");
    default:
      return x;
    };
  };

  int ip = 0;

  while (ip < program.size()) {
    // cout << "executing " << program[ip] << " at " << ip << endl;
    auto opcode = program[ip];
    ip++;
    if (ip > program.size()) {
      return;
    }
    if (opcode == 0) {
      auto denominator = (int)pow(2, readCombo(program[ip]));
      A /= denominator;
      ip++;
    } else if (opcode == 1) {
      B ^= program[ip];
      ip++;
    } else if (opcode == 2) {
      auto res = readCombo(program[ip]) % 8;
      B = res;
      ip++;
    } else if (opcode == 3) {
      int addr = program[ip];
      if (A == 0) {
        ip++;
      } else {
        ip = addr;
      }
    } else if (opcode == 4) {
      B = B ^ C;
      ip++;
    } else if (opcode == 5) {
      auto r = readCombo(program[ip]) % 8;
      cout << r << ",";
      ip++;
    } else if (opcode == 6) {
      auto denominator = (int)pow(2, readCombo(program[ip]));
      B = A / denominator;
      ip++;
    } else if (opcode == 7) {
      auto denominator = (int)pow(2, readCombo(program[ip]));
      C = A / denominator;
      ip++;
    } else {
      cout << "unknown opcode: " << opcode << endl;
      throw runtime_error("unknown opcode");
    }
  }
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
