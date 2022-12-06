
using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 6" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day6.txt)");
  string str;

  vector<string> chars;

  string input;

  while (getline(file, str)) {
    input = str;
  }

  string data;

  int ans1 = 1;
  for (auto& it : input) {
    if (data.length() == 4) {
      data.erase(0, 1);
    }
    data.push_back(it);
    if (data.length() == 4 && uniqueCharacters(data)) {
      break;
    }
    ans1++;
  }
  cout << "Part 1: " << data << " Ans: " << ans1 << endl;

  data.clear();

  int ans2 = 1;
  for (auto& it : input) {
    if (data.length() == 14) {
      data.erase(0, 1);
    }
    data.push_back(it);
    if (data.length() == 14 && uniqueCharacters(data)) {
      break;
    }
    ans2++;
  }
  cout << "Part 2: " << data << " Ans: " << ans2 << endl;
  return 0;
}
