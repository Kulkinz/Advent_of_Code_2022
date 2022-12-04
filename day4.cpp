
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 4" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day4.txt)");
  string str;

  int ans1 = 0;
  int ans2 = 0;

  while (getline(file, str)) {
    string line = str;

    vector<string> out;
    tokenize(line, ',', out);

    vector<int> container1;
    vector<int> container2;

    vector<string> range1;
    vector<string> range2;
    tokenize(out[0], '-', range1);
    tokenize(out[1], '-', range2);

    if (stoi(range1[0]) <= stoi(range2[0]) && stoi(range1[1]) >= stoi(range2[1])) {
      ans1++;
    } else if (stoi(range2[0]) <= stoi(range1[0]) && stoi(range2[1]) >= stoi(range1[1])) {
      ans1++;
    }

    if (stoi(range1[0]) <= stoi(range2[0]) && stoi(range2[0]) <= stoi(range1[1])) {
      ans2++;
    } else if (stoi(range2[0]) <= stoi(range1[0]) && stoi(range1[0]) <= stoi(range2[1])) {
      ans2++;
    }
  }

  cout << "Part 1: " << ans1 << endl;
  cout << "Part 2: " << ans2 << endl;
  return 0;
}
