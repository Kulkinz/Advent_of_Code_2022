
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

    size_t found = half.find_first_not_of(otherHalf);
    while (found != string::npos) {
      half.erase(found, 1);
      found = half.find_first_not_of(otherHalf);
    }

    duplicates.push_back(half[0]); // eliminates duplicates

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
    string sumOfLines = "";

    size_t found = lineA.find_first_of(lineB);
    while (found != string::npos) {
      sumOfLines += lineA[found];
      lineA.erase(found, 1);
      found = lineA.find_first_of(lineB);
    }
    found = sumOfLines.find_first_of(lineC);
    duplicates.push_back(sumOfLines[found]);

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
