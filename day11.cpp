
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include "Helpers/HelperFunctions.h"

class Monkey {
 private:
  queue<long> items;
  void (*operation)(long&);
  int test;
  int ifTrue;
  int ifFalse;
  vector<Monkey> *monkeysRef;
  long amountInspected = 0;
 public:
  Monkey(void(*operation)(long&), int test, int ifTrue, int ifFalse, vector<Monkey> *monkeysRef, vector<int> start) {
    this->operation = operation;
    this->test = test;
    this->ifTrue = ifTrue;
    this->ifFalse = ifFalse;
    this->monkeysRef = monkeysRef;

    for (auto &it : start) {
      items.push(it);
    }
  }
  void turn() {

    while (!items.empty()) {
      long curr = items.front();
      operation(curr);
      amountInspected++;
//      curr /= 3;
      if (curr % test == 0) {
        monkeysRef[0][ifTrue].grabItem(curr);
      } else {
        monkeysRef[0][ifFalse].grabItem(curr);
      }
      items.pop();
    }
  }
  void grabItem(long item) {
    items.push(item);
  }
  int getInspected() const {
    return amountInspected;
  }
};

int main() {
  cout << "Day 11" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day11.txt)");
  string str;

//  while (getline(file, str)) {
//    vector<string> out;
//    tokenize(str, ' ', out);
//    cout << str << endl;
//  }

  vector<Monkey> monkeys;

//  monkeys.push_back(Monkey([](long &a) {a *= 19; a %= 96577;}, 23, 2, 3, &monkeys, vector<int>{79, 98}));
//  monkeys.push_back(Monkey([](long &a) {a += 6; a %= 96577;}, 19, 2, 0, &monkeys, vector<int>{54, 65, 75, 74}));
//  monkeys.push_back(Monkey([](long &a) {unsigned long long int b = a; b *= b; b %= 96577; a = (long) b;}, 13, 1, 3, &monkeys, vector<int>{79, 60, 97}));
//  monkeys.push_back(Monkey([](long &a) {a += 3; a %= 96577;}, 17, 0, 1, &monkeys, vector<int>{74}));

  monkeys.push_back(Monkey([](long &a) {a *= 7; a %= 9699690;}, 13, 1, 3, &monkeys, vector<int>{64}));
  monkeys.push_back(Monkey([](long &a) {a += 7; a %= 9699690;}, 19, 2, 7, &monkeys, vector<int>{60, 84, 84, 65}));
  monkeys.push_back(Monkey([](long &a) {a *= 3; a %= 9699690;}, 5, 5, 7, &monkeys, vector<int>{52, 67, 74, 88, 51, 61}));
  monkeys.push_back(Monkey([](long &a) {a += 3; a %= 9699690;}, 2, 1, 2, &monkeys, vector<int>{67, 72}));
  monkeys.push_back(Monkey([](long &a) {unsigned long long int b = a; b *= b; b %= 9699690; a = (long) b;}, 17, 6, 0, &monkeys, vector<int>{80, 79, 58, 77, 68, 74, 98, 64}));
  monkeys.push_back(Monkey([](long &a) {a += 8; a %= 9699690;}, 11, 4, 6, &monkeys, vector<int>{62, 53, 61, 89, 86}));
  monkeys.push_back(Monkey([](long &a) {a += 2; a %= 9699690;}, 7, 3, 0, &monkeys, vector<int>{86, 89, 82}));
  monkeys.push_back(Monkey([](long &a) {a += 4; a %= 9699690;}, 3, 4, 5, &monkeys, vector<int>{92, 81, 70, 96, 69, 84, 83}));

  for (int i = 0; i < 10000; i++) {
    for (auto &it : monkeys) {
      it.turn();
    }
  }

  vector<long> inspections;
  for (auto &it : monkeys) {
    inspections.push_back(it.getInspected());
    cout << it.getInspected() << endl;
  }

  sort(inspections.rbegin(), inspections.rend());

  cout << (unsigned long long int) inspections[0] * (unsigned long long int) inspections[1] << endl;

  return 0;
}