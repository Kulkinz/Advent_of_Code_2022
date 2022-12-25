
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 25" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day25.txt)");
  string str;

  long long sum = 0;
  while (getline(file, str)) {

    long long num = 0;

    for (int i = 0; i < str.length(); i++) {
      long long power = pow(5, str.length() - i - 1);
      long long value;
      switch (str[i]) {
        case '2':
          value = 2;
          break;
        case '1':
          value = 1;
          break;
        case '0':
          value = 0;
          break;
        case '-':
          value = -1;
          break;
        case '=':
          value = -2;
          break;
      }

      num += power * value;

    }

    sum += num;
  }

  cout << "SUM: " << sum << endl;

  vector<long long> values;

  long long multiplier = 1;
  values.push_back(multiplier);

  while (multiplier < sum) {
    multiplier *= 5;
    values.push_back(multiplier);
  }

  vector<int> divisioned;

  while (multiplier > 0) {
    int amountIn = (sum / multiplier);
    divisioned.push_back(amountIn);
    sum -= amountIn * multiplier;
    multiplier /= 5;
  }

  reverse(divisioned.begin(), divisioned.end());

  vector<int> shifted;

  int carryOver = 0;
  for (auto &it : divisioned) {

    int currNum = it + carryOver;

    if (currNum <= 2) {
      shifted.push_back(currNum);
      carryOver = 0;
    } else {
      carryOver = 1;
      shifted.push_back(currNum - 5);
    }
  }

  cout << "Answer: ";

  reverse(shifted.begin(), shifted.end());

  for (auto &it : shifted) {
    switch (it) {
      case -2:
        cout << '=';
        break;
      case -1:
        cout << '-';
        break;
      case 0:
        cout << '0';
        break;
      case 1:
        cout << '1';
        break;
      case 2:
        cout << '2';
        break;
    }
  }

  cout << endl;
  return 0;
}