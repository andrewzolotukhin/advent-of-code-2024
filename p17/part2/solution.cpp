#include <bits/stdc++.h>

using namespace std;

long long solve(long long A) {
  long long res = 0LL;
  long long B = 0LL;
  long long C = 0LL;

  do {
    B = A % 8;
    B ^= 7;
    C = A >> B;
    B ^= 7;
    B = B ^ C;
    A >>= 3;
    res += B % 8;
    res *= 10;
  } while (A);

  return res / 10;
}

/*
  000 -> 111
  001 -> 110
  010 -> 101
  011 -> 100
  100 -> 011
  101 -> 010
  110 -> 001
  111 -> 000

*/

int main() {

  for (long long i = 0; i < 100; i++) {
    cout << i << " " << (i % 8) << ": " << solve(i) << endl;
  }

  // long long target = 2417751746035530LL;
  //
  // for (long long i = 34464302400860LL; i < 2146196000086000LL; i++) {
  //   if (i % 10000000000LL) {
  //     cout << i << endl;
  //   }
  //   if (solve(i) == target) {
  //     cout << "Found: " << i << endl;
  //     break;
  //   }
  // }
}
