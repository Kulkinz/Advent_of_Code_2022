
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

int processStep(vector<vector<char>> &grid, int &start, int &width, int &depth);

int main() {
  cout << "Day 14" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day14.txt)");
  string str;

  vector<pair<pair<int,int>,pair<int,int>>> rocks;

  int minX = INT16_MAX;
  int maxX = 0;
  int depth = 0;

  while (getline(file, str)) {
    vector<string> out;
    tokenize(str, " -> ", out);

    pair<int,int> last;

    auto it = out.begin();

    vector<string> numOut;
    tokenize(*it, ',', numOut);
    last = make_pair(stoi(numOut[0]), stoi(numOut[1]));

    minX = min(minX, last.first);
    maxX = max(maxX, last.first);
    depth = max(depth, last.second);
    numOut.clear();

    it++;
    for (; it != out.end(); ++it) {
      tokenize(*it, ',', numOut);
      pair<int,int> curr = make_pair(stoi(numOut[0]), stoi(numOut[1]));
      rocks.emplace_back(make_pair(last, curr));

      minX = min(minX, curr.first);
      maxX = max(maxX, curr.first);
      depth = max(depth, curr.second);
      numOut.clear();

      last = curr;
    }
  }

  // part 2
  minX = minX - depth - 1;
  maxX = maxX + depth + 1;

  for (auto &it : rocks) {
    it.first.first -= minX;
    it.second.first -= minX;
  }

  int width = maxX - minX;
  vector<vector<char>> grid(
      depth + 2 + 1,
      vector<char>(width + 1, '.'));
  // [y][x]

  for (auto &it : rocks) {

    // x the same, so iterate y
    if (it.first.first == it.second.first) {
      for (int y = min(it.first.second, it.second.second); y <= max(it.first.second, it.second.second); y++) {
        grid[y][it.first.first] = '#';
      }
    } else { // y the same so iterate x
      for (int x = min(it.first.first, it.second.first); x <= max(it.first.first, it.second.first); x++) {
        grid[it.first.second][x] = '#';
      }
    }

  }

  for (int x = 0; x <= width; x ++) {
    grid[depth+2][x] = '#';
  }

  int start = 500 - minX;

  cout << processStep(grid, start, width, depth) << endl;

//  for (auto &it1 : grid) {
//    for (auto &it2 : it1) {
//      cout << it2;
//    }
//    cout << endl;
//  }

  return 0;
}

int processStep(vector<vector<char>> &grid, int &start, int &width, int &depth) {

  int sandAmount = 0;
  pair<int,int> sand = make_pair(start, 0);

  while (true) {
    if (grid[0][start] == 'o') {
      return sandAmount;
//    } else if (sand.second + 1 > depth) { // safety check
//      return sandAmount;
    } else if (grid[sand.second+1][sand.first] == '.') {
      sand.second += 1;
      continue;
    } else if (sand.first-1 < 0) { // going to fall in void
      return sandAmount;
    } else if (grid[sand.second+1][sand.first-1] == '.') {
      sand.second += 1;
      sand.first -= 1;
      continue;
    } else if (sand.first+1 > width) { // going to fall in void
      return sandAmount;
    } else if (grid[sand.second+1][sand.first+1] == '.') {
      sand.second += 1;
      sand.first += 1;
      continue;
    } else {
      grid[sand.second][sand.first] = 'o';
      sandAmount++;
      sand.first = start;
      sand.second = 0;
      continue;
    }
  }
}