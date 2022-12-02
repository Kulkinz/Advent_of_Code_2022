
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int calculate(char play, char other);
int main() {
  cout << "Day 2" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day2.txt)");
  string str;

  int totalScore1 = 0;
  int totalScore2 = 0;
  while (getline(file, str)) {
    char other = str.at(0);

    char play1 = str.at(2);

    char play2 = (other + ('X' - 'A')) + (str.at(2) - 'Y');
    play2 = (play2 == ('X' - 1)) ? 'Z' : (play2 == ('Z' + 1)) ? 'X' : play2;

    totalScore1 += calculate(play1, other);
    totalScore2 += calculate(play2, other);
  }
  cout << "Part 1: " << totalScore1 << endl;
  cout << "Part 2: " << totalScore2 << endl;

  return 0;
}

int calculate(char play, char other) {
  int score = 0;
  int difference = ((play - 'X') - (other - 'A'));
  difference = (difference == 2) ? -1 : (difference == -2) ? 1 : difference;
  difference++;
  score += 3 * difference;

  score += (play - 'X') + 1;

  return score;
}
