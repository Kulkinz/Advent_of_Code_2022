
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include "Helpers/HelperFunctions.h"

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
  return {l.first+r.first,l.second+r.second};
}

#define WIDTHPLUSWALL 9

vector<bitset<WIDTHPLUSWALL>> cave;

//struct state {
//  int xPos;
//  int yRelative;
//  int gustIndex;
//};

class rock {
 private:

  pair<int, int> origin = make_pair(3, 4);
  vector<pair<int,int>> structure; // bottom left = 0,0
  int height;
  bool checkRight() {

    pair<int,int> movement = make_pair(1,0);
    for (auto &it : structure) {
      pair<int,int> spot = origin + it + movement;

      if (cave[spot.second][spot.first]) {
        return false;
      }
    }
    return true;

  }

  bool checkLeft() {

    pair<int,int> movement = make_pair(-1,0);
    for (auto &it : structure) {
      pair<int,int> spot = origin + it + movement;

      if (cave[spot.second][spot.first]) {
        return false;
      }
    }
    return true;
  }

  bool checkDown() {

    pair<int,int> movement = make_pair(0,-1);
    for (auto &it : structure) {
      pair<int,int> spot = origin + it + movement;

      if (cave[spot.second][spot.first]) {
        return false;
      }
    }
    return true;
  }

  void setLocation() {

    for (auto &it : structure) {
      pair<int,int> spot = origin + it;

      cave[spot.second][spot.first] = true;
    }
  }
 public:
  rock(vector<pair<int,int>> structure, int height) {
    this->structure = structure;
    this->height = height;
  }

  void moveRight() {

    if (!checkRight()) return;

    origin.first++;

  }
  void moveLeft() {

    if (!checkLeft()) return;

    origin.first--;
  }
  bool moveDown() {

    if (checkDown()) {
      origin.second--;
      return false;
    } else {
      setLocation();
      return true;
    }

  }
  void resetOrigin(int height) {
    origin.first = 3;
    origin.second = height + 3 + 1;
  }
  int getHighestPointRock() {
    return origin.second - 1 + height;
  }
  pair<int, int> getOrigin() {
    return origin;
  }
};

int main() {
  cout << "Day 17" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day17.txt)");
  string str;
  getline(file, str);

  queue<rock*> rocks;

  rocks.push(new rock(vector<pair<int,int>> { make_pair(0,0), make_pair(1,0), make_pair(2,0), make_pair(3,0) }, 1));
  rocks.push(new rock(vector<pair<int,int>> { make_pair(1,0), make_pair(0,1), make_pair(1,1), make_pair(2,1), make_pair(1,2) }, 3));
  rocks.push(new rock(vector<pair<int,int>> { make_pair(0,0), make_pair(1,0), make_pair(2,0), make_pair(2,1), make_pair(2,2) }, 3));
  rocks.push(new rock(vector<pair<int,int>> { make_pair(0,0), make_pair(0,1), make_pair(0,2), make_pair(0,3) }, 4));
  rocks.push(new rock(vector<pair<int,int>> { make_pair(0,0), make_pair(1,0), make_pair(0,1), make_pair(1,1) }, 2));

  bitset<WIDTHPLUSWALL> bottom = bitset<WIDTHPLUSWALL>().set();
  bitset<WIDTHPLUSWALL> row = bitset<WIDTHPLUSWALL>();
  row[0] = true;
  row[WIDTHPLUSWALL-1] = true;

  cave.push_back(bottom);

  int highestPoint = 0;
  int gap = 7;

  auto it = str.begin();

  int i = 0;

  for (; i < 2022; i++) {

    int amountToAdd = gap - (cave.size() - (highestPoint + 1));

    for (int j = 0; j < amountToAdd; j++) {
      cave.push_back(row);
    }

    rock* curr = rocks.front();
    rocks.pop();
    curr->resetOrigin(highestPoint);

    bool hasLanded = false;
    while (!hasLanded) {
      if (*it == '>') { // right
        curr->moveRight();
      } else { // left
        curr->moveLeft();
      }

      hasLanded = curr->moveDown();

      it++;
      if (it == str.end()) {
        it = str.begin();
      }
    }

    highestPoint = max(highestPoint, curr->getHighestPointRock());

    rocks.push(curr);
  }

  cout << "Part 1: " << highestPoint << endl;

  for (; i < 20220; i++) {

    int amountToAdd = gap - (cave.size() - (highestPoint + 1));

    for (int j = 0; j < amountToAdd; j++) {
      cave.push_back(row);
    }

    rock* curr = rocks.front();
    rocks.pop();
    curr->resetOrigin(highestPoint);

    bool hasLanded = false;
    while (!hasLanded) {
      if (*it == '>') { // right
        curr->moveRight();
      } else { // left
        curr->moveLeft();
      }

      hasLanded = curr->moveDown();

      it++;
      if (it == str.end()) {
        it = str.begin();
      }
    }

    highestPoint = max(highestPoint, curr->getHighestPointRock());

    rocks.push(curr);
  }

  int highestPointBefore = highestPoint;
  int amountOfRocksBefore = i;

  vector<bitset<WIDTHPLUSWALL>> match;

  for (int spot = highestPoint; spot > highestPoint - 8; spot--) {
    match.push_back(cave[spot]);
  }

  auto matchIt = match.begin();

  int amountNewRocks = 0;

  while (matchIt != match.end()) {

    matchIt = match.begin();

    int amountToAdd = gap - (cave.size() - (highestPoint + 1));

    for (int j = 0; j < amountToAdd; j++) {
      cave.push_back(row);
    }

    rock* curr = rocks.front();
    rocks.pop();
    curr->resetOrigin(highestPoint);

    bool hasLanded = false;
    while (!hasLanded) {
      if (*it == '>') { // right
        curr->moveRight();
      } else { // left
        curr->moveLeft();
      }

      hasLanded = curr->moveDown();

      it++;
      if (it == str.end()) {
        it = str.begin();
      }
    }
    amountNewRocks++;

    highestPoint = max(highestPoint, curr->getHighestPointRock());

    for (int j = highestPoint; matchIt != match.end(); j--) {
      if (cave[j] != *matchIt) {
        break;
      } else {
        matchIt++;
      }
    }

    rocks.push(curr);
  }

  int changeInHeight = highestPoint - highestPointBefore;
  // change in height for every amountNewRocks of rocks

  long long int amountAfterStart = 1000000000000 - i;
  long long int howManyTimesLoops = amountAfterStart / amountNewRocks;
  long long int howMuchLeft = amountAfterStart % amountNewRocks;

  long long int accumulative = highestPointBefore + changeInHeight*howManyTimesLoops;

  long long int finalHighestPointRef = highestPoint;

  for (int k = 0; k < howMuchLeft; k++) {
    int amountToAdd = gap - (cave.size() - (highestPoint + 1));

    for (int j = 0; j < amountToAdd; j++) {
      cave.push_back(row);
    }

    rock* curr = rocks.front();
    rocks.pop();
    curr->resetOrigin(highestPoint);

    bool hasLanded = false;
    while (!hasLanded) {
      if (*it == '>') { // right
        curr->moveRight();
      } else { // left
        curr->moveLeft();
      }

      hasLanded = curr->moveDown();

      it++;
      if (it == str.end()) {
        it = str.begin();
      }
    }

    highestPoint = max(highestPoint, curr->getHighestPointRock());

    rocks.push(curr);
  }
  long long int finalHeightChange = highestPoint - finalHighestPointRef;

  accumulative += finalHeightChange;

  cout << "Part 2: " << accumulative << endl;

  return 0;
}