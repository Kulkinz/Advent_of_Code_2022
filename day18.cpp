
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <queue>
#include "Helpers/HelperFunctions.h"

struct position {
  int x;
  int y;
  int z;
};

int main() {
  cout << "Day 18" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day18.txt)");
  string str;

  vector<string> input;

  int xMax = 0;
  int yMax = 0;
  int zMax = 0;

  vector<position> positions;

  while (getline(file, str)) {
    vector<string> out;
    tokenize(str, ',', out);

    xMax = max(xMax, stoi(out[0]));
    yMax = max(yMax, stoi(out[1]));
    zMax = max(zMax, stoi(out[2]));
    input.push_back(str);


    positions.push_back({stoi(out[0]), stoi(out[1]), stoi(out[2])});
  }

  vector<vector<vector<bool>>> space(xMax + 1,
                                    vector<vector<bool>>(yMax  + 1,
                                        vector<bool>(zMax  + 1, false)));


  for (auto &it : positions) {
    space[it.x][it.y][it.z] = true;
  }

  int acc = 0;
  for (auto &it : positions) {
    if (it.x == 0) {
      acc++;
    } else {
      if (!space[it.x-1][it.y][it.z]) acc++;
    }
    if (it.x == xMax) {
      acc++;
    } else {
      if (!space[it.x+1][it.y][it.z]) acc++;
    }
    if (it.y == 0) {
      acc++;
    } else {
      if (!space[it.x][it.y-1][it.z]) acc++;
    }
    if (it.y == yMax) {
      acc++;
    } else {
      if (!space[it.x][it.y+1][it.z]) acc++;
    }
    if (it.z == 0) {
      acc++;
    } else {
      if (!space[it.x][it.y][it.z-1]) acc++;
    }
    if (it.z == zMax) {
      acc++;
    } else {
      if (!space[it.x][it.y][it.z+1]) acc++;
    }
  }

  cout << "Part 1: " << acc << endl;

  // simulate air

  queue<position> queue;

  queue.push({0,0,0});

  space[0][0][0] = true;

  while (!queue.empty()) {
    position curr = queue.front();
    queue.pop();

    if (curr.x != 0) {
      if (!space[curr.x-1][curr.y][curr.z]) {
        space[curr.x-1][curr.y][curr.z] = true;
        queue.push({curr.x-1,curr.y,curr.z});
      }
    }
    if (curr.x != xMax) {
      if (!space[curr.x+1][curr.y][curr.z]) {
        space[curr.x+1][curr.y][curr.z] = true;
        queue.push({curr.x+1,curr.y,curr.z});
      }
    }
    if (curr.y != 0) {
      if (!space[curr.x][curr.y-1][curr.z]) {
        space[curr.x][curr.y-1][curr.z] = true;
        queue.push({curr.x,curr.y-1,curr.z});
      }
    }
    if (curr.y != yMax) {
      if (!space[curr.x][curr.y+1][curr.z]) {
        space[curr.x][curr.y+1][curr.z] = true;
        queue.push({curr.x,curr.y+1,curr.z});
      }
    }
    if (curr.z != 0) {
      if (!space[curr.x][curr.y][curr.z-1]) {
        space[curr.x][curr.y][curr.z-1] = true;
        queue.push({curr.x,curr.y,curr.z-1});
      }
    }
    if (curr.z != zMax) {
      if (!space[curr.x][curr.y][curr.z+1]) {
        space[curr.x][curr.y][curr.z+1] = true;
        queue.push({curr.x,curr.y,curr.z+1});
      }
    }
  }

  int acc2 = 0;

  for (int x = 0; x <= xMax; ++x) {
    for (int y = 0; y <= yMax; ++y) {
      for (int z = 0; z <= zMax; ++z) {
        if (!space[x][y][z]) {
          if (space[x-1][y][z]) {
            acc2++;
          }
          if (space[x+1][y][z]) {
            acc2++;
          }
          if (space[x][y-1][z]) {
            acc2++;
          }
          if (space[x][y+1][z]) {
            acc2++;
          }
          if (space[x][y][z-1]) {
            acc2++;
          }
          if (space[x][y][z+1]) {
            acc2++;
          }
        }
      }
    }
  }

  cout << "Part 2: " << acc - acc2 << endl;

  return 0;
}