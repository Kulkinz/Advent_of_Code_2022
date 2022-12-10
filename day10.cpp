
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 10" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day10.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    data.push_back(str);
  }

  int cycle = 1;
  int val = 1;
  long sum = 0;

  vector<string> screen(6, "");

  auto it = data.begin();
  bool addx = false;
  while (it != data.end()) {

    int target = floor((cycle - 1) / 40);
    int position = (cycle - 1) % 40;

    if (val - 1 <= position && position <= val + 1) {
      screen[target].push_back('#');
    } else {
      screen[target].push_back('.');
    }

    if (((cycle - 20) % 40 == 0) && (cycle < 221)) {
      sum += cycle * val;
    }

    if (addx) {
      val+= stoi(it->substr(5));
      it++;
      addx = false;
    } else if (*it == "noop") {
      it++;
    } else {
      addx = true;
    }


    cycle++;
  }

  cout << "Part 1: " << sum << endl;

  cout << "Part 2: " << endl;

  for (auto &crt : screen) {
    cout << crt << endl;
  }


  return 0;
}