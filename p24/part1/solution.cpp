#include <bits/stdc++.h>
#include <cassert>
#include <unordered_map>
#define CONSTANT "CONSTANT"
#define AND "AND"
#define OR "OR"
#define XOR "XOR"

using namespace std;

struct Operation {
  string type;
  string operand1;
  string operand2;
  int value;
  bool isEvaluated;
};

void Evaluate(unordered_map<string, Operation> &registers, string name) {
  auto operation = registers[name];
  if (operation.isEvaluated) {
    return;
  }

  if (operation.type == CONSTANT) {
    assert(false);
  } else {
    auto leftRegister = registers[operation.operand1];
    auto rightRegister = registers[operation.operand2];

    if (!leftRegister.isEvaluated) {
      Evaluate(registers, operation.operand1);
    }

    if (!rightRegister.isEvaluated) {
      Evaluate(registers, operation.operand2);
    }

    leftRegister = registers[operation.operand1];
    rightRegister = registers[operation.operand2];

    if (leftRegister.isEvaluated && rightRegister.isEvaluated) {
      if (operation.type == AND) {
        operation.value = leftRegister.value & rightRegister.value;
      }

      if (operation.type == OR) {
        operation.value = leftRegister.value | rightRegister.value;
      }

      if (operation.type == XOR) {
        operation.value = leftRegister.value ^ rightRegister.value;
      }

    } else {
      cout << leftRegister.isEvaluated << " " << rightRegister.isEvaluated
           << endl;
      assert(false);
    }

    operation.isEvaluated = true;
    registers[name] = operation;
  }
}

int main() {
  // cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);
  //

  unordered_map<string, Operation> registers;
  vector<string> zregisters;

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
    registers[name] = {CONSTANT, name, "", value, true};
    if (name.substr(0, 1) == "z") {
      zregisters.push_back(name);
    }
  }

  // until EOF read dependant values

  while (getline(cin, line)) {
    int value;

    char operand1s[100], operations[100], operand2s[100], results[100];
    string operand1, operation, operand2, result;

    sscanf(line.c_str(), "%99[^ ] %99[^ ] %99[^ ]  -> %99[^\n]", operand1s,
           operations, operand2s, results);

    operand1 = operand1s;
    operation = operations;
    operand2 = operand2s;
    result = results;

    registers[result] = {operation, operand1, operand2, 0, false};
    if (result.substr(0, 1) == "z") {
      zregisters.push_back(result);
    }
  }

  for (auto reg : registers) {
    if (!reg.second.isEvaluated) {
      Evaluate(registers, reg.first);
    }
  }

  long long result = 0;

  sort(zregisters.begin(), zregisters.end(),
       [&](string a, string b) { return a > b; });

  for (auto reg : zregisters) {
    auto operation = registers[reg];
    cout << reg << ": " << operation.value << endl;

    result <<= 1;
    result |= operation.value;
  }

  cout << result << endl;
}
