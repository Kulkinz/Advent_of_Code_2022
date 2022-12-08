
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 8" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day8.txt)");
  string str;

  vector<vector<int>> grid;

  int xEdge;
  int yEdge;

  int i = 0;

  while (getline(file, str)) {
    xEdge = str.length() - 1;
    vector<int> row;
    for (auto &it : str) {
      row.push_back(it - '0');
    }
    grid.push_back(row);
    i++;
  }

  yEdge = i - 1;

  int acc = 0;
  int max = 0;
  for (int x = 0; x <= xEdge; x++) {
    for (int y = 0; y <= yEdge; y++) {
      if (x == 0 || x == xEdge || y == 0 || y == yEdge) {
        acc++;
      } else {
        int curr = grid[y][x];
        int score = 1;
        bool leftVisible = true;
        for (int i = x - 1; i >= 0; i--) {
          if (curr <= grid[y][i]) {
            leftVisible = false;
            score *= (x - i);
            break;
          }
        }
        if (leftVisible) score *= x;

        bool rightVisible = true;
        for (int i = x + 1; i <= xEdge; i++) {
          if (curr <= grid[y][i]) {
            rightVisible = false;
            score *= (i - x);
            break;
          }
        }
        if (rightVisible) score *= (xEdge - x);

        bool topVisible = true;
        for (int i = y - 1; i >= 0; i--) {
          if (curr <= grid[i][x]) {
            topVisible = false;
            score *= (y - i);
            break;
          }
        }
        if (topVisible) score *= (y);

        bool bottomVisible = true;
        for (int i = y + 1; i <= yEdge; i++) {
          if (curr <= grid[i][x]) {
            bottomVisible = false;
            score *= (i - y);
            break;
          }
        }
        if (bottomVisible) score *= (yEdge - y);

        max = score > max ? score : max;

        if (leftVisible || rightVisible || topVisible || bottomVisible) {
          acc++;
        }
      }
    }
  }

  cout << "Part 1: " << acc << endl;
  cout << "Part 2: " << max << endl;


  return 0;
}
