
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Helpers/HelperFunctions.h"

void calculatePriorities(int &ans, vector<char> &chars);
int main() {
  cout << "Day 3" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day3.txt)");
  string str;

  int ans1 = 0;
  vector<string> data;
  while (getline(file, str)) {
    data.push_back(str);
  }

  vector<char> duplicates;

  auto it = data.begin();

  while (it != data.end()) {
    string s = *it;
    string half = s.substr(0, s.length()/2);
    string otherHalf = s.substr(s.length()/2);

    vector<char> charHalf(half.begin(), half.end());
    vector<char> charOtherHalf(otherHalf.begin(), otherHalf.end());

    vector<char> result = get_intersection(charHalf, charOtherHalf);

    duplicates.push_back(result[0]);

    it++;
  }

  calculatePriorities(ans1, duplicates);

  cout << "Part 1: " << ans1 << endl;

  int ans2 = 0;

  it = data.begin();

  duplicates.clear();

  while (it != data.end()) {

    string lineA = *it;
    string lineB = *(it+1);
    string lineC = *(it+2);

    vector<char> charA(lineA.begin(), lineA.end());
    vector<char> charB(lineB.begin(), lineB.end());
    vector<char> charC(lineC.begin(), lineC.end());

    vector<char> result = get_intersection(charA, charB);
    vector<char> finalResult = get_intersection(result, charC);

    duplicates.push_back(finalResult[0]);

    it += 3;
  }

  calculatePriorities(ans2, duplicates);

  cout << "Part 2: " << ans2 << endl;

  return 0;
}

void calculatePriorities(int &ans, vector<char> &chars) {
  for (auto& it : chars) {

    if (it < 'a') { // 'A'
      ans += (it - 'A') + 27;
    } else { // 'a'
      ans += (it - 'a') + 1;
    }
  }
}
