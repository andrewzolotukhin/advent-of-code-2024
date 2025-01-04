#include <bits/stdc++.h>
#define AND 0
#define OR 1
#define XOR 2
#define PINS 45

using namespace std;

struct Operation {
  int type;
  int operand1;
  int operand2;
  int result;
};

map<int, int> values;
map<string, int> opIds;
vector<Operation> operations;
int lastId = 0;

int getId(string name) {
  if (!opIds.count(name)) {
    opIds[name] = ++lastId;
  }
  return opIds[name];
}

string getName(int id) {
  for (auto [name, i] : opIds) {
    if (i == id) {
      return name;
    }
  }
  assert(false);
}

unsigned long long calculateSum(unsigned long long x, unsigned long long y) {
  values.clear();
  for (int i = 0; i < PINS; i++) {
    int id = getId("x" + string((i < 10) ? "0" : "") + to_string(i));
    values[id] = (x & (1LL << i)) ? 1 : 0;
  }

  for (int i = 0; i < PINS; i++) {
    int id = getId("y" + string((i < 10) ? "0" : "") + to_string(i));
    values[id] = (y & (1LL << i)) ? 1 : 0;
  }

  int lastValuesCount = values.size();
  while (true) {
    // cout << "values size: " << values.size() << endl;
    for (int i = 0; i < operations.size(); i++) {
      if (values.count(operations[i].operand1) > 0 &&
          values.count(operations[i].operand2) > 0 &&
          values.count(operations[i].result) == 0) {
        int x = values[operations[i].operand1];
        int y = values[operations[i].operand2];
        values[operations[i].result] =
            operations[i].type == XOR
                ? (x ^ y)
                : ((operations[i].type == AND) ? x & y : x | y);
      }
    }
    if (values.size() == lastValuesCount) {
      break;
    }
    lastValuesCount = values.size();
  }

  unsigned long long result = 0;

  for (int i = 0; i <= PINS; i++) {
    int id = getId("z" + string((i < 10) ? "0" : "") + to_string(i));
    // cout << ("z" + string((i < 10) ? "0" : "") + to_string(i)) << endl;
    if (values.count(id)) {
      result |= ((long long)values[id] << i);
    } else {
      return -1;
    }
  }

  return result;
}

unsigned long long getRandom(int bits) {
  // generate a random number of `bits` length
  return (((long long)rand() << 16) + (long long)rand()) % (1LL << (bits + 1));
}

int main() {
  srand(time(NULL));
  string line;
  while (true) {
    getline(cin, line);

    if (line.empty()) {
      break;
    }

    string name;
    int value;

    char t[100];
    sscanf(line.c_str(), "%99[^:]: %d", t, &value);
    name = t;
  }

  // until EOF read operations

  while (getline(cin, line)) {
    int value;

    char operand1s[100], operationss[100], operand2s[100], results[100];
    string operand1, operation, operand2, result;

    sscanf(line.c_str(), "%99[^ ] %99[^ ] %99[^ ]  -> %99[^\n]", operand1s,
           operationss, operand2s, results);

    operand1 = operand1s;
    operation = operationss;
    operand2 = operand2s;
    result = results;

    auto operand1Id = getId(operand1);
    auto operand2Id = getId(operand2);
    auto resultId = getId(result);
    operations.push_back(
        {operation == "AND" ? AND : ((operation == "OR") ? OR : XOR),
         operand1Id, operand2Id, resultId});
  }

  unsigned long long X = 0b111110011110100100110011001010010010110100011LL,
                     Y = 0b101011001011111001101011010100011111011001101LL;

  unsigned long long result = calculateSum(X, Y);
  cout << "result: " << result << endl;
  assert(result != -1);

  vector<string> opsToSwap;

  unsigned long long target = X + Y;

  int correctBits = 5;
  const int bitsBatch = 5;
  const int correctValueThreshold = 1000;
  vector<pair<int, int>> swappedOuts;

  while (correctBits < PINS && swappedOuts.size() < 4) {
    bool isInitiallyCorrect = true;
    for (int i = 0; i < correctValueThreshold; i++) {
      auto x = getRandom(correctBits);
      auto y = getRandom(correctBits);
      auto sum = calculateSum(x, y);
      if (sum == -1 || sum != x + y || sum != x + y) {
        isInitiallyCorrect = false;
        break;
      }
    }

    if (isInitiallyCorrect) {
      correctBits += bitsBatch;
      continue;
    }

    bool found = false;
    for (int i = 0; i < operations.size() - 1; i++) {
      bool skip = false;
      for (auto [l, r] : swappedOuts) {
        if (l == i || r == i) {
          skip = true;
        }
      }
      if (skip) {
        continue;
      }
      cout << correctBits << " (" << i << "): " << swappedOuts.size() << endl;
      for (int j = i + 1; j < operations.size(); j++) {
        bool skip = false;
        for (auto [l, r] : swappedOuts) {
          if (l == j || r == j) {
            skip = true;
          }
        }
        if (skip) {
          continue;
        }

        // try to swap out resultIds of operations[i] and operations[j]
        int t = operations[i].result;
        operations[i].result = operations[j].result;
        operations[j].result = t;

        bool isCorrect = true;
        for (int k = 0; k < correctValueThreshold; k++) {
          auto x = getRandom(correctBits);
          auto y = getRandom(correctBits);
          // cout << x << " " << y << endl;
          auto sum = calculateSum(x, y);
          if (sum == -1 || sum != x + y || sum != x + y) {
            isCorrect = false;
            break;
          }
        }

        if (isCorrect) {
          swappedOuts.push_back({i, j});
          cout << "++++ " << correctBits << ": " << i << " " << j << endl;
          opsToSwap.push_back(getName(operations[i].result));
          opsToSwap.push_back(getName(operations[j].result));
          found = true;
          correctBits += bitsBatch;
          break;
        }

        t = operations[i].result;
        operations[i].result = operations[j].result;
        operations[j].result = t;
      }
      if (found)
        break;
    }
    assert(found);
  }

  sort(opsToSwap.begin(), opsToSwap.end());

  for (auto op : opsToSwap) {
    cout << op << ",";
  }
  cout << endl;

  result = calculateSum(X, Y);
  cout << "result: " << result << endl;
  cout << "must be: " << (X + Y) << endl;

  // cout << X << " + " << Y << " = " << result << endl;
}
