
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  cout << "Day 1" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day1.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    data.push_back(str);
  }
  data.emplace_back("");

  auto it = data.begin();

  vector<int> totals;

  int curr = 0;
  while (it != data.end()) {
    if (it->empty()) {
      totals.push_back(curr);
      curr = 0;
    } else {
      curr += stoi(*it);
    }
    it++;
  }

  sort(totals.begin(), totals.end(), greater<int>());

  cout << "Part 1: " << totals[0] << endl;

  cout << "Part 2: " << totals[0] + totals[1] + totals[2] << endl;

  return 0;
}
