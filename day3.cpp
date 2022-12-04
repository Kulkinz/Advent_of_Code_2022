
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

    vector<char> charHalf(half.begin(), half.end());
    vector<char> charOtherHalf(otherHalf.begin(), otherHalf.end());

    sort(charHalf.begin(), charHalf.end());
    sort(charOtherHalf.begin(), charOtherHalf.end());

    vector<char> result;
    set_intersection(charHalf.begin(), charHalf.end(), charOtherHalf.begin(), charOtherHalf.end(), back_inserter(result));

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

    sort(charA.begin(), charA.end());
    sort(charB.begin(), charB.end());
    sort(charC.begin(), charC.end());

    vector<char> result;
    set_intersection(charA.begin(), charA.end(), charB.begin(), charB.end(), back_inserter(result));
    vector<char> finalResult;
    set_intersection(result.begin(), result.end(), charC.begin(), charC.end(), back_inserter(finalResult));

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
