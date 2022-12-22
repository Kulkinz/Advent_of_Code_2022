
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 22" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day22.txt)");
  string str;

  bool isMap = true;

  vector<string> mapData;

  while (getline(file, str)) {

    if (str.empty()) {
      isMap = false;
      continue;
    } else if (isMap) {
      mapData.push_back(str);
    }
  }

  // ends with str as the path

  int height = mapData.size();
  int width = 0;
  for (auto &it : mapData) {
    width = max(width, (int) it.size());
  }

  for (auto &it : mapData) {
    int diff = width - it.size();
    for (int i = 0; i < diff; i++) {
      it.push_back(' ');
    }
  }


  int start = 0;
  for (int x = 0; ; x++) {
    if (mapData[0][x] == '.') {
      start = x;
      break;
    }
  }

  map<int,int> topWrap;
  map<int,int> bottomWrap;
  map<int,int> leftWrap;
  map<int,int> rightWrap;

  // topMost
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (mapData[y][x] != ' ') {
        topWrap[x] = y;
        break;
      }
    }
  }

  // bottomMost
  for (int x = 0; x < width; x++) {
    for (int y = height - 1; y >= 0; y--) {
      if (mapData[y][x] != ' ') {
        bottomWrap[x] = y;
        break;
      }
    }
  }

  // leftMost
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (mapData[y][x] != ' ') {
        leftWrap[y] = x;
        break;
      }
    }
  }

  // rightMost
  for (int y = 0; y < height; y++) {
    for (int x = width - 1; x >= 0; x--) {
      if (mapData[y][x] != ' ') {
        rightWrap[y] = x;
        break;
      }
    }
  }

  vector<string> instructions;

  size_t begin = 0;
  size_t end = str.find_first_of("RL", 0);
  while (end != string::npos) {
    instructions.push_back(str.substr(begin, end - begin + 1));
    begin = end + 1;
    end  = str.find_first_of("RL", begin);
  }
  instructions.push_back(str.substr(begin, -1));


  pair<int,int> position = make_pair(start, 0);
  int heading = 0;

  for (auto &it : instructions) {

    int distance;
    int rotate;

    if (it[it.length()-1] == 'R') {
      distance = stoi(it.substr(0,it.length()-1));
      rotate = 1;
    } else if (it[it.length()-1] == 'L') {
      distance = stoi(it.substr(0,it.length()-1));
      rotate = -1;
    } else {
      distance = stoi(it);
      rotate = 0;
    }


    for (int i = 0; i < distance; i++) {

      switch (heading) {
        int nextX;
        int nextY;
        case 0: // right
          nextX = position.first + 1;
          if (nextX == width || mapData[position.second][nextX] == ' ') {
            nextX = leftWrap[position.second];
          }

          if (mapData[position.second][nextX] == '.') {
            position.first = nextX;
          }

          break;
        case 1: // down
          nextY = position.second + 1;
          if (nextY == height || mapData[nextY][position.first] == ' ') {
            nextY = topWrap[position.first];
          }

          if (mapData[nextY][position.first] == '.') {
            position.second = nextY;
          }

          break;
        case 2: // left
          nextX = position.first - 1;
          if (nextX == -1 || mapData[position.second][nextX] == ' ') {
            nextX = rightWrap[position.second];
          }

          if (mapData[position.second][nextX] == '.') {
            position.first = nextX;
          }

          break;
        case 3: // up
          nextY = position.second - 1;
          if (nextY == -1 || mapData[nextY][position.first] == ' ') {
            nextY = bottomWrap[position.first];
          }

          if (mapData[nextY][position.first] == '.') {
            position.second = nextY;
          }

          break;
      }
    }

    heading += rotate;
    heading = (heading == -1) ? 3 : (heading == 4) ? 0 : heading;

  }

  cout << "Part 1: " << (1000 * (position.second+1)) + (4 * (position.first+1)) + heading << endl;

  map<pair<int,int>, pair<int,int>> correspondingUp;
  map<pair<int,int>, pair<int,int>> correspondingDown;
  map<pair<int,int>, pair<int,int>> correspondingLeft;
  map<pair<int,int>, pair<int,int>> correspondingRight;
  map<pair<int,int>, int> correspondingUpHeading;
  map<pair<int,int>, int> correspondingDownHeading;
  map<pair<int,int>, int> correspondingLeftHeading;
  map<pair<int,int>, int> correspondingRightHeading;
  int hardCodeX1 = 0;
  int hardCodeY1 = 0;
  int hardCodeX2 = 0;
  int hardCodeY2 = 0;

  // 1 - 6
  hardCodeX1 = 100;
  hardCodeY1 = 0;
  hardCodeX2 = 0;
  hardCodeY2 = 199;
  for (int i = 0; i < 50; i++) {
    correspondingUp[make_pair(hardCodeX1 + i, hardCodeY1)] = make_pair(hardCodeX2 + i, hardCodeY2);
    correspondingUpHeading[make_pair(hardCodeX1 + i, hardCodeY1)] = 3;
    correspondingDown[make_pair(hardCodeX2 + i, hardCodeY2)] = make_pair(hardCodeX1 + i, hardCodeY1);
    correspondingDownHeading[make_pair(hardCodeX2 + i, hardCodeY2)] = 1;
  }

  // 1 - 4
  hardCodeX1 = 149;
  hardCodeY1 = 0;
  hardCodeX2 = 99;
  hardCodeY2 = 149;
  for (int i = 0; i < 50; i++) {
    correspondingRight[make_pair(hardCodeX1, hardCodeY1 + i)] = make_pair(hardCodeX2, hardCodeY2 - i);
    correspondingRightHeading[make_pair(hardCodeX1, hardCodeY1 + i)] = 2;
    correspondingRight[make_pair(hardCodeX2, hardCodeY2 - i)] = make_pair(hardCodeX1, hardCodeY1 + i);
    correspondingRightHeading[make_pair(hardCodeX2, hardCodeY2 - i)] = 2;
  }

  // 1 - 3
  hardCodeX1 = 100;
  hardCodeY1 = 49;
  hardCodeX2 = 99;
  hardCodeY2 = 50;
  for (int i = 0; i < 50; i++) {
    correspondingDown[make_pair(hardCodeX1 + i, hardCodeY1)] = make_pair(hardCodeX2, hardCodeY2 + i);
    correspondingDownHeading[make_pair(hardCodeX1 + i, hardCodeY1)] = 2;
    correspondingRight[make_pair(hardCodeX2, hardCodeY2 + i)] = make_pair(hardCodeX1 + i, hardCodeY1);
    correspondingRightHeading[make_pair(hardCodeX2, hardCodeY2 + i)] = 3;
  }


  // 2 - 6
  hardCodeX1 = 50;
  hardCodeY1 = 0;
  hardCodeX2 = 0;
  hardCodeY2 = 150;
  for (int i = 0; i < 50; i++) {
    correspondingUp[make_pair(hardCodeX1 + i, hardCodeY1)] = make_pair(hardCodeX2, hardCodeY2 + i);
    correspondingUpHeading[make_pair(hardCodeX1 + i, hardCodeY1)] = 0;
    correspondingLeft[make_pair(hardCodeX2, hardCodeY2 + i)] = make_pair(hardCodeX1 + i, hardCodeY1);
    correspondingLeftHeading[make_pair(hardCodeX2, hardCodeY2 + i)] = 1;
  }

  // 2 - 5
  hardCodeX1 = 50;
  hardCodeY1 = 0;
  hardCodeX2 = 0;
  hardCodeY2 = 149;
  for (int i = 0; i < 50; i++) {
    correspondingLeft[make_pair(hardCodeX1, hardCodeY1 + i)] = make_pair(hardCodeX2, hardCodeY2 - i);
    correspondingLeftHeading[make_pair(hardCodeX1, hardCodeY1 + i)] = 0;
    correspondingLeft[make_pair(hardCodeX2, hardCodeY2 - i)] = make_pair(hardCodeX1, hardCodeY1 + i);
    correspondingLeftHeading[make_pair(hardCodeX2, hardCodeY2 - i)] = 0;
  }

  // 3 - 5
  hardCodeX1 = 50;
  hardCodeY1 = 50;
  hardCodeX2 = 0;
  hardCodeY2 = 100;
  for (int i = 0; i < 50; i++) {
    correspondingLeft[make_pair(hardCodeX1, hardCodeY1 + i)] = make_pair(hardCodeX2 + i, hardCodeY2);
    correspondingLeftHeading[make_pair(hardCodeX1, hardCodeY1 + i)] = 1;
    correspondingUp[make_pair(hardCodeX2 + i, hardCodeY2)] = make_pair(hardCodeX1, hardCodeY1 + i);
    correspondingUpHeading[make_pair(hardCodeX2 + i, hardCodeY2)] = 0;
  }


  // 4 - 6
  hardCodeX1 = 50;
  hardCodeY1 = 149;
  hardCodeX2 = 49;
  hardCodeY2 = 150;
  for (int i = 0; i < 50; i++) {
    correspondingDown[make_pair(hardCodeX1 + i, hardCodeY1)] = make_pair(hardCodeX2, hardCodeY2 + i);
    correspondingDownHeading[make_pair(hardCodeX1 + i, hardCodeY1)] = 2;
    correspondingRight[make_pair(hardCodeX2, hardCodeY2 + i)] = make_pair(hardCodeX1 + i, hardCodeY1);
    correspondingRightHeading[make_pair(hardCodeX2, hardCodeY2 + i)] = 3;
  }


  position = make_pair(start, 0);
  heading = 0;

  for (auto &it : instructions) {

    int distance;
    int rotate;

    if (it[it.length()-1] == 'R') {
      distance = stoi(it.substr(0,it.length()-1));
      rotate = 1;
    } else if (it[it.length()-1] == 'L') {
      distance = stoi(it.substr(0,it.length()-1));
      rotate = -1;
    } else {
      distance = stoi(it);
      rotate = 0;
    }


    for (int i = 0; i < distance; i++) {


      pair<int,int> nextPosition;
      int nextHeader = heading;
      switch (heading) {
        case 0: // right
          nextPosition = make_pair(position.first + 1, position.second);
          if (nextPosition.first == width || mapData[position.second][nextPosition.first] == ' ') {
            nextPosition = correspondingRight[position];
            nextHeader = correspondingRightHeading[position];
          }

          if (mapData[nextPosition.second][nextPosition.first] == '.') {
            position = nextPosition;
            heading = nextHeader;
          }

          break;
        case 1: // down
          nextPosition = make_pair(position.first, position.second + 1);
          if (nextPosition.second == height || mapData[nextPosition.second][position.first] == ' ') {
            nextPosition = correspondingDown[position];
            nextHeader = correspondingDownHeading[position];
          }

          if (mapData[nextPosition.second][nextPosition.first] == '.') {
            position = nextPosition;
            heading = nextHeader;
          }

          break;
        case 2: // left
          nextPosition = make_pair(position.first - 1, position.second);
          if (nextPosition.first == -1 || mapData[position.second][nextPosition.first] == ' ') {
            nextPosition = correspondingLeft[position];
            nextHeader = correspondingLeftHeading[position];
          }

          if (mapData[nextPosition.second][nextPosition.first] == '.') {
            position = nextPosition;
            heading = nextHeader;
          }

          break;
        case 3: // up
          nextPosition = make_pair(position.first, position.second - 1);
          if (nextPosition.second == -1 || mapData[nextPosition.second][position.first] == ' ') {
            nextPosition = correspondingUp[position];
            nextHeader = correspondingUpHeading[position];
          }

          if (mapData[nextPosition.second][nextPosition.first] == '.') {
            position = nextPosition;
            heading = nextHeader;
          }

          break;
      }
    }

    heading += rotate;
    heading = (heading == -1) ? 3 : (heading == 4) ? 0 : heading;

  }

  cout << "Part 2: " << (1000 * (position.second+1)) + (4 * (position.first+1)) + heading << endl;

  return 0;
}