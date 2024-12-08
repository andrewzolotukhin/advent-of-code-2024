#include <bits/stdc++.h>
using namespace std;

void combinateSumOrMul(vector<long long> &numbers, int current, long long value,
                       vector<long long> &results) {
  if (current == numbers.size()) {
    results.push_back(value);
    return;
  }

  combinateSumOrMul(numbers, current + 1, value + numbers[current], results);
  combinateSumOrMul(numbers, current + 1, value * numbers[current], results);
}

void solve() {
  // read data line by line till EOF
  // every line contains a single integer followed by colon and then there are
  // some integers separated by spaces like this: 20: 1 2 3 4 5 6 7 8 9 10 11 12
  // 13 14 15 16 17 20 should be saved to `result` and the rest should go to the
  // `numbers` vector

  string line;
  long long answer = 0;

  while (getline(cin, line)) {
    stringstream ss(line);
    long long result;
    ss >> result;
    char colon;
    ss >> colon;
    vector<long long> numbers;
    long long number;
    while (ss >> number) {
      numbers.push_back(number);
    }

    vector<long long> results;

    cout << result << '\n';
    combinateSumOrMul(numbers, 1, numbers[0], results);

    // if results contains  result, then add result to answer
    if (find(results.begin(), results.end(), result) != results.end()) {
      answer += result;
    }
  }

  cout << answer << '\n';
}

int main() {
  //  cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);

  solve();
}
