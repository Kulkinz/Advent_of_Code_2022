
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

void changeRope(const pair<int, int> &rope, pair<int, int> &tail);
int main() {
  cout << "Day 9" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day9.txt)");
  string str;

  set<pair<int,int>> ropePositionsAns2;
  set<pair<int,int>> ropePositionsAns1;

  pair<int,int> start(0,0);
  ropePositionsAns1.insert(start);
  ropePositionsAns2.insert(start);
  pair<int,int> rope(start);
  pair<int,int> tail1(start);
  pair<int,int> tail2(start);
  pair<int,int> tail3(start);
  pair<int,int> tail4(start);
  pair<int,int> tail5(start);
  pair<int,int> tail6(start);
  pair<int,int> tail7(start);
  pair<int,int> tail8(start);
  pair<int,int> tail9(start);
  while (getline(file, str)) {
    vector<string> out;
    tokenize(str, ' ', out);

    for (int i = 0; i < stoi(out[1]); i++) {
      switch (out[0][0]) {
        case 'R':
          rope.first++;
          break;
        case 'L':
          rope.first--;
          break;
        case 'U':
          rope.second++;
          break;
        case 'D':
          rope.second--;
          break;
      }

      changeRope(rope, tail1);

      ropePositionsAns1.insert(tail1);

      changeRope(tail1, tail2);
      changeRope(tail2, tail3);
      changeRope(tail3, tail4);
      changeRope(tail4, tail5);
      changeRope(tail5, tail6);
      changeRope(tail6, tail7);
      changeRope(tail7, tail8);
      changeRope(tail8, tail9);

      ropePositionsAns2.insert(tail9);
    }
  }

  cout << "Part 1: " << ropePositionsAns1.size() << endl;
  cout << "Part 2: " << ropePositionsAns2.size() << endl;

  return 0;
}
void changeRope(const pair<int, int> &rope, pair<int, int> &tail) {
  int xDifference = rope.first - tail.first;
  int yDifference = rope.second - tail.second;
  if (abs(xDifference) <= 1 && abs(yDifference) <= 1) {
    // tail doesn't need to move
  } else {
    if (xDifference == 0) {
      tail.second += copysign(1, yDifference);
    } else if (yDifference == 0) {
      tail.first += copysign(1, xDifference);
    } else {
      tail.first += copysign(1, xDifference);
      tail.second += copysign(1, yDifference);
    }
  }
}

