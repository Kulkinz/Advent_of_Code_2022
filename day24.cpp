
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "Helpers/HelperFunctions.h"

struct blizzard {
  pair<int,int> pos;
  pair<int,int> direction;
};

void drawBlizzards(vector<blizzard> &blizzards,
                   unordered_map<int, unordered_map<int, int>> &grid,
                   int xBound,
                   int yBound);
int main() {
  cout << "Day 24" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day24.txt)");
  string str;

  pair<int,int> start = make_pair(1,0);
  pair<int,int> end;

  vector<string> grid;

  while (getline(file, str)) {
    grid.push_back(str);
  }

  end = make_pair(str.length() - 2, grid.size() - 1);

  int xBound = str.length() - 1;
  int yBound = grid.size() - 1;

  vector<blizzard> blizzards;

  for (int y = 1; y < yBound; y++) {
    for (int x = 1; x < xBound; x++) {
      switch (grid[y][x]) {
        case '>':blizzards.push_back({make_pair(x, y), make_pair(1, 0)});
          break;
        case '<':blizzards.push_back({make_pair(x, y), make_pair(-1, 0)});
          break;
        case '^':blizzards.push_back({make_pair(x, y), make_pair(0, -1)});
          break;
        case 'v':blizzards.push_back({make_pair(x, y), make_pair(0, 1)});
          break;
        default:break;
      }
    }
  }


  queue<pair<int,int>> currQueue;
  queue<pair<int,int>> nextQueue;

  currQueue.push(start);

  int minute = 0;

  unordered_map<int, unordered_map<int, int>> blizzardSpots;

  while (true) {

    // set blizzards positions;
    for (auto &it : blizzards) {
      blizzardSpots[it.pos.first][it.pos.second]++;
    }

//    cout << "Minute: " << minute << endl;
//    drawBlizzards(blizzards, blizzardSpots, xBound, yBound);
//    cout << endl;

    bool hasReachedEndNext = false;

    unordered_map<int, unordered_map<int, bool>> spots;

    // check current values and generate next
    while (!currQueue.empty()) {
      pair<int,int> pos = currQueue.front();
      currQueue.pop();

      if (blizzardSpots[pos.first][pos.second] > 0) continue;
      if (spots[pos.first][pos.second]) continue;
      if (pos.second + 1 == end.second && pos.first == end.first) {
        hasReachedEndNext = true;
        break;
      }

      spots[pos.first][pos.second] = true;

      nextQueue.push(pos);

      if (pos == start) {
        nextQueue.push(make_pair(pos.first, pos.second + 1));
      } else {
        if (pos.first - 1 > 0) {
          nextQueue.push(make_pair(pos.first - 1, pos.second));
        }
        if (pos.first + 1 < xBound) {
          nextQueue.push(make_pair(pos.first + 1, pos.second));
        }
        if (pos.second - 1 > 0) {
          nextQueue.push(make_pair(pos.first, pos.second - 1));
        }
        if (pos.second + 1 < yBound) {
          nextQueue.push(make_pair(pos.first, pos.second + 1));
        }
      }
    }

    // clear blizzardSpots
    for (auto &it : blizzards) {
      blizzardSpots[it.pos.first][it.pos.second] = 0;
    }

    // do next blizzardSpots for next time
    for (auto &it : blizzards) {
      it.pos.first += it.direction.first;
      it.pos.second += it.direction.second;
      if (it.pos.first == 0) it.pos.first = xBound - 1;
      else if (it.pos.first == xBound) it.pos.first = 1;
      else if (it.pos.second == 0) it.pos.second = yBound - 1;
      else if (it.pos.second == yBound) it.pos.second = 1;
    }

    minute++;
    swap(currQueue, nextQueue);


    if (hasReachedEndNext) {
      break;
    }
  }

  cout << "Part 1: " << minute << endl;

  // return

  queue<pair<int,int>> empty1;
  queue<pair<int,int>> empty2;
  std::swap( nextQueue, empty1 );
  std::swap( currQueue, empty2 );

  currQueue.push(end);

  while (true) {

    // set blizzards positions;
    for (auto &it : blizzards) {
      blizzardSpots[it.pos.first][it.pos.second]++;
    }

//    cout << "Minute: " << minute << endl;
//    drawBlizzards(blizzards, blizzardSpots, xBound, yBound);
//    cout << endl;

    bool hasReachedStartNext = false;

    unordered_map<int, unordered_map<int, bool>> spots;

    // check current values and generate next
    while (!currQueue.empty()) {
      pair<int,int> pos = currQueue.front();
      currQueue.pop();

      if (blizzardSpots[pos.first][pos.second] > 0) continue;
      if (spots[pos.first][pos.second]) continue;
      if (pos.second - 1 == start.second && pos.first == start.first) {
        hasReachedStartNext = true;
        break;
      }

      spots[pos.first][pos.second] = true;

      nextQueue.push(pos);

      if (pos == end) {
        nextQueue.push(make_pair(pos.first, pos.second - 1));
      } else {
        if (pos.first - 1 > 0) {
          nextQueue.push(make_pair(pos.first - 1, pos.second));
        }
        if (pos.first + 1 < xBound) {
          nextQueue.push(make_pair(pos.first + 1, pos.second));
        }
        if (pos.second - 1 > 0) {
          nextQueue.push(make_pair(pos.first, pos.second - 1));
        }
        if (pos.second + 1 < yBound) {
          nextQueue.push(make_pair(pos.first, pos.second + 1));
        }
      }
    }

    // clear blizzardSpots
    for (auto &it : blizzards) {
      blizzardSpots[it.pos.first][it.pos.second] = 0;
    }

    // do next blizzardSpots for next time
    for (auto &it : blizzards) {
      it.pos.first += it.direction.first;
      it.pos.second += it.direction.second;
      if (it.pos.first == 0) it.pos.first = xBound - 1;
      else if (it.pos.first == xBound) it.pos.first = 1;
      else if (it.pos.second == 0) it.pos.second = yBound - 1;
      else if (it.pos.second == yBound) it.pos.second = 1;
    }

    minute++;
    swap(currQueue, nextQueue);

    if (hasReachedStartNext) {
      break;
    }
  }

  cout << "back at start: " << minute << endl;

  queue<pair<int,int>> empty3;
  queue<pair<int,int>> empty4;
  std::swap( nextQueue, empty3 );
  std::swap( currQueue, empty4 );

  currQueue.push(start);

  while (true) {

    // set blizzards positions;
    for (auto &it : blizzards) {
      blizzardSpots[it.pos.first][it.pos.second]++;
    }

//    cout << "Minute: " << minute << endl;
//    drawBlizzards(blizzards, blizzardSpots, xBound, yBound);
//    cout << endl;

    bool hasReachedEndNext = false;

    unordered_map<int, unordered_map<int, bool>> spots;

    // check current values and generate next
    while (!currQueue.empty()) {
      pair<int,int> pos = currQueue.front();
      currQueue.pop();

      if (blizzardSpots[pos.first][pos.second] > 0) continue;
      if (spots[pos.first][pos.second]) continue;
      if (pos.second + 1 == end.second && pos.first == end.first) {
        hasReachedEndNext = true;
        break;
      }

      spots[pos.first][pos.second] = true;

      nextQueue.push(pos);

      if (pos == start) {
        nextQueue.push(make_pair(pos.first, pos.second + 1));
      } else {
        if (pos.first - 1 > 0) {
          nextQueue.push(make_pair(pos.first - 1, pos.second));
        }
        if (pos.first + 1 < xBound) {
          nextQueue.push(make_pair(pos.first + 1, pos.second));
        }
        if (pos.second - 1 > 0) {
          nextQueue.push(make_pair(pos.first, pos.second - 1));
        }
        if (pos.second + 1 < yBound) {
          nextQueue.push(make_pair(pos.first, pos.second + 1));
        }
      }
    }

    // clear blizzardSpots
    for (auto &it : blizzards) {
      blizzardSpots[it.pos.first][it.pos.second] = 0;
    }

    // do next blizzardSpots for next time
    for (auto &it : blizzards) {
      it.pos.first += it.direction.first;
      it.pos.second += it.direction.second;
      if (it.pos.first == 0) it.pos.first = xBound - 1;
      else if (it.pos.first == xBound) it.pos.first = 1;
      else if (it.pos.second == 0) it.pos.second = yBound - 1;
      else if (it.pos.second == yBound) it.pos.second = 1;
    }

    minute++;
    swap(currQueue, nextQueue);

    if (hasReachedEndNext) {
      break;
    }
  }

  cout << "Part 2: " << minute << endl;

  return 0;
}
void drawBlizzards(vector<blizzard> &blizzards,
                   unordered_map<int, unordered_map<int, int>> &grid,
                   int xBound,
                   int yBound) {

  unordered_map<int, unordered_map<int, char>> direction;

  for (auto &it : blizzards) {
    if (it.direction == make_pair(1, 0)) {
      direction[it.pos.first][it.pos.second] = '>';
    } else if (it.direction == make_pair(-1, 0)) {
      direction[it.pos.first][it.pos.second] = '<';
    } else if (it.direction == make_pair(0, 1)) {
      direction[it.pos.first][it.pos.second] = 'v';
    } else if (it.direction == make_pair(0, -1)) {
      direction[it.pos.first][it.pos.second] = '^';
    }
  }

  for (int y = 0; y <= yBound; y++) {
    for (int x = 0; x <= xBound; x++) {
      if (x == 0 || y == 0 || x == xBound || y == yBound) {
        if (x == 1 && y == 0) {
          cout << '.';
        } else if (x == xBound - 1 && y == yBound) {
          cout << '.';
        } else {
          cout << '#';
        }
      } else if (grid[x][y] > 0) {
        if (grid[x][y] == 1) {
          cout << direction[x][y];
        } else {
          cout << grid[x][y];
        }
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
}
