
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

enum Operation { add, subtract, multiply, divide, equals };

struct monkey {
  string name;
  Operation operation;
  string one;
  string two;

};

bool is_number(const string &s) {
  return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

int main() {
  cout << "Day 21" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day21.txt)");
  string str;

  map<string, long long> values;
  vector<monkey> monkeys;

  while (getline(file, str)) {
    vector<string> out;
    tokenize(str, ": ", out);

    if (is_number(out[1])) {
      values[out[0]] = stoi(out[1]);
    } else {

      vector<string> out1;
      tokenize(out[1], ' ', out1);
      Operation op;

      if (out[0] == "root") {
        op = equals;
      } else {
        switch (out1[1][0]) {
          case '+':
            op = add;
            break;
          case '-':
            op = subtract;
            break;
          case '*':
            op = multiply;
            break;
          case '/':
            op = divide;
            break;
        }
      }

      monkeys.push_back({out[0], op, out1[0], out1[2]});
    }
  }

  auto it = monkeys.begin();
  while (it != monkeys.end()) {

    if (values.count(it->one) && values.count(it->two) && (it->one != "humn" && it->two != "humn")) {
      switch (it->operation) {
        case add:
          values[it->name] = values[it->one] + values[it->two];
          break;
        case subtract:
          values[it->name] = values[it->one] - values[it->two];
          break;
        case multiply:
          values[it->name] = values[it->one] * values[it->two];
          break;
        case divide:
          values[it->name] = values[it->one] / values[it->two];
          break;
        case equals:
          break;
      }

      monkeys.erase(it);
      it = monkeys.begin();
      continue;

    }
    it++;
  }

//  cout << values["root"] << endl;
  vector<monkey> finalOperations;

  map<string, bool> accounted;

  it = monkeys.begin();
  while (it != monkeys.end()) {

    if ((values.count(it->one) || accounted.count(it->one)) && (values.count(it->two) || accounted.count(it->two))) {

      accounted[it->one] = true;
      accounted[it->two] = true;
      accounted[it->name] = true;

      finalOperations.push_back(*it);

      monkeys.erase(it);
      it = monkeys.begin();
      continue;

    }
    it++;
  }

  values["humn"] = 0;
//  values["humn"] = 3887609741180;
  int lastSignDifference = 1;
  long long rateOfChange = 10000000000;
  bool canStop = false;
  while (!canStop) {
    for (auto &monk : finalOperations) {
      switch (monk.operation) {
        case add:
          values[monk.name] = values[monk.one] + values[monk.two];
          break;
        case subtract:
          values[monk.name] = values[monk.one] - values[monk.two];
          break;
        case multiply:
          values[monk.name] = values[monk.one] * values[monk.two];
          break;
        case divide:
          values[monk.name] = values[monk.one] / values[monk.two];
          break;
        case equals:
          cout << "HUMN: " << values["humn"] << " Rate Of Change:" << rateOfChange << " Values: " << values[monk.one] << "," << values[monk.two] << endl;
          if (values[monk.one] == values[monk.two]) {
            canStop = true;
          } else {
            int signDifference;
            if (values[monk.one] - values[monk.two] > 0) {
              signDifference = 1;
            } else {
              signDifference = -1;
            }
            if (signDifference != lastSignDifference) {
              lastSignDifference = signDifference;
              rateOfChange /= -10;
            }
          }
          break;
      }
    }
    if (!canStop) values["humn"] += rateOfChange;
//    if (values["humn"] > 3887609741200) break;
  }


  cout << values["humn"] << endl;

  return 0;
}