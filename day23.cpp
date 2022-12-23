
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "Helpers/HelperFunctions.h"

void renderGrid(unordered_map<int, unordered_map<int, bool>> &grid, vector<pair<int,int>> &elves);

int main() {
  cout << "Day 23" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day23.txt)");
  string str;

  unordered_map<int, unordered_map<int, bool>> grid;
  vector<pair<int,int>> elves;

  int y = 0;
  while (getline(file, str)) {
    int x = 0;
    for (auto &it : str) {
      if (it == '#') {
        grid[x][y] = true;
        elves.emplace_back(x, y);
      }
      x++;
    }
    y++;
  }

  int startingStep = 0;

  int i = 0;

  for (i = 0; ; ++i) {

//    renderGrid(grid, elves);

    map<pair<int,int>, int> proposed;
    vector<pair<pair<int,int>, pair<int,int>>> nextPossible;
    vector<pair<int,int>> next;

    bool didMove = false;

    for (auto &elf : elves) {
      int currX = elf.first;
      int currY = elf.second;

      bool breakOut = false;

      if (grid[currX - 1][currY - 1] || grid[currX][currY - 1] | grid[currX + 1][currY - 1]
          || grid[currX - 1][currY]                              || grid[currX + 1][currY]
          || grid[currX - 1][currY + 1] || grid[currX][currY + 1] || grid[currX + 1][currY + 1]) {
        for (int j = 0; j < 4; j++) {
          switch ((startingStep + j) % 4) {
            case 0: // north
              if (!grid[currX - 1][currY - 1] && !grid[currX][currY - 1] && !grid[currX + 1][currY - 1]) {
                proposed[make_pair(currX, currY - 1)]++;
                nextPossible.emplace_back(elf, make_pair(currX, currY - 1));
                breakOut = true;
              }
              break;
            case 1: // south
              if (!grid[currX - 1][currY + 1] && !grid[currX][currY + 1] && !grid[currX + 1][currY + 1]) {
                proposed[make_pair(currX, currY + 1)]++;
                nextPossible.emplace_back(elf, make_pair(currX, currY + 1));
                breakOut = true;
              }
              break;
            case 2: // west
              if (!grid[currX - 1][currY - 1] && !grid[currX - 1][currY] && !grid[currX - 1][currY + 1]) {
                proposed[make_pair(currX - 1, currY)]++;
                nextPossible.emplace_back(elf, make_pair(currX - 1, currY));
                breakOut = true;
              }
              break;
            case 3: // east
              if (!grid[currX + 1][currY - 1] && !grid[currX + 1][currY] && !grid[currX + 1][currY + 1]) {
                proposed[make_pair(currX + 1, currY)]++;
                nextPossible.emplace_back(elf, make_pair(currX + 1, currY));
                breakOut = true;
              }
              break;
          }
          if (breakOut) break;
        }
      }


      if (!breakOut) { // stay in place;
        next.push_back(elf);
      } else {
        didMove = true;
      }
    }

    if (!didMove) break;

    for (auto &it : nextPossible) {
      if (proposed[it.second] > 1) {
        next.push_back(it.first);
      } else {
        next.push_back(it.second);
      }
    }

    for (auto &it : elves) {
      grid[it.first][it.second] = false;
    }

    elves.clear();

    for (auto &it : next) {
      grid[it.first][it.second] = true;
      elves.push_back(it);
    }

    startingStep++;
    startingStep %= 4;

    if (i == 9) {
      int maxX = INT16_MIN;
      int minX = INT16_MAX;
      int maxY = INT16_MIN;
      int minY = INT16_MAX;

      for (auto &it : elves) {
        maxX = max(maxX, it.first);
        minX = min(minX, it.first);
        maxY = max(maxY, it.second);
        minY = min(minY, it.second);
      }

      int ans = (maxX - minX + 1) * (maxY - minY + 1) - elves.size();

      cout << "Part 1: " << ans << endl;
    }
  }

  cout << "Part 2: " << i + 1 << endl;

  return 0;
}


void renderGrid(unordered_map<int, unordered_map<int, bool>> &grid, vector<pair<int,int>> &elves) {
  int maxX = INT16_MIN;
  int minX = INT16_MAX;
  int maxY = INT16_MIN;
  int minY = INT16_MAX;

  for (auto &it : elves) {
    maxX = max(maxX, it.first);
    minX = min(minX, it.first);
    maxY = max(maxY, it.second);
    minY = min(minY, it.second);
  }

  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {
      cout << ((grid[x][y]) ? '#' : '.');
    }
    cout << endl;
  }

  cout << endl;
}