#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <cstdint>
using namespace std;

long long solve(long long A, long long B, long long C) {
  vector<long long> program = {2, 4, 1, 7, 7, 5, 1, 7, 4, 6, 0, 3, 5, 5, 3, 0};

  auto readCombo = [&](long long x) {
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

  vector<long long> output;

  auto getResult = [&] {
    long long res = 0;
    for (auto i : output) {
      res = res * 10 + i;
    }
    return res;
  };

  int ip = 0;

  while (ip < program.size()) {
    // cout << "executing " << program[ip] << " at " << ip << endl;
    auto opcode = program[ip];
    ip++;
    if (ip > program.size()) {
      return getResult();
    }
    if (opcode == 0) {
      auto denominator = (long long)pow(2, readCombo(program[ip]));
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
      output.push_back(r);
      ip++;
    } else if (opcode == 6) {
      auto denominator = (long long)pow(2, readCombo(program[ip]));
      B = A / denominator;
      ip++;
    } else if (opcode == 7) {
      auto denominator = (long long)pow(2, readCombo(program[ip]));
      C = A / denominator;
      ip++;
    } else {
      cout << "unknown opcode: " << opcode << endl;
      throw runtime_error("unknown opcode");
    }
  }

  return getResult();
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  // cout << solve(66245665, 0, 0) << '\n';

  long long target = 2417751746035530LL;
  long long from = 21461960000860LL;
  for (long long i = from; i <= LONG_LONG_MAX; i++) {
    if (i % 1000000 == 0) {
      cout << "Trying: " << i << endl;
    };
    if (solve(i, 0, 0) == target) {
      cout << "Found: " << i << endl;
      break;
    }
  }
}
