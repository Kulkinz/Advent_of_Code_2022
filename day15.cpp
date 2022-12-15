
using namespace std;

#include <iostream>
#include <string>
#include <cstring>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

struct Point {
  int priority{};
  pair<int,int> data;

  friend bool operator< (Point const& lhs, Point const& rhs) {
    return lhs.priority > rhs.priority;
  }

  friend std::ostream& operator<< (std::ostream& os, Point const& e) {
    return os << "{ " << e.priority << ", '" << e.data.first << "," << e.data.second << "' } ";
  }
};

int getValueSurroundings(int x, int y, vector<pair<pair<int, int>, pair<int, int>>> &data);
int getLowestDistance(int x, int y, vector<pair<pair<int, int>, pair<int, int>>> &data);
int getValuePriority(int x, int y, vector<pair<pair<int, int>, int>> &data);
bool getAllLonger(int x, int y, vector<pair<pair<int, int>, int>> &data);
int main() {
  cout << "Day 15" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day15.txt)");
  string str;

//  int target = 10;
//  int bound = 20;
  int target = 2000000;
  int bound = 4000000;

//  set<pair<int,int>> sensors;
//  set<pair<int,int>> beacons;
  vector<pair<pair<int,int>,pair<int,int>>> pairs;
  vector<pair<pair<int,int>,pair<int,int>>> pairsPure;

  int minX = INT16_MAX;
  int maxX = INT16_MIN;
  int minY = INT16_MAX;
  int maxY = INT16_MIN;

  int maxDistance = 0;

  while (getline(file, str)) {
    vector<string> out;
    tokenize(str, "x=", out);
    // out[1] and out[2]
    string sensorCurr = out[1];
    sensorCurr = sensorCurr.substr(0, sensorCurr.find(','));
    int sensorX = stoi(sensorCurr);
    string beaconCurr = out[2];
    beaconCurr = beaconCurr.substr(0, beaconCurr.find(','));
    int beaconX = stoi(beaconCurr);

    out.clear();
    tokenize(str, "y=", out);
    // out[1] and out[2]
    sensorCurr = out[1];
    sensorCurr = sensorCurr.substr(0, sensorCurr.find(':'));
    int sensorY = stoi(sensorCurr);
    beaconCurr = out[2];
    int beaconY = stoi(beaconCurr);

    pairs.emplace_back(make_pair(sensorX, sensorY), make_pair(beaconX, beaconY));
    pairsPure.emplace_back(make_pair(sensorX, sensorY), make_pair(beaconX, beaconY));

    minX = min(minX, sensorX);
    minX = min(minX, beaconX);
    maxX = max(maxX, sensorX);
    maxX = max(maxX, beaconX);

    minY = min(minY, sensorY);
    minY = min(minY, beaconY);
    maxY = max(maxY, sensorY);
    maxY = max(maxY, beaconY);

    maxDistance = max(maxDistance, abs(sensorX - beaconX) + abs(sensorY - beaconY));

  }

  minX -= maxDistance;
  maxX += maxDistance;

  for (auto &it : pairs) {
    it.first.first -= minX;
    it.second.first -= minX;
    it.first.second -= minY;
    it.second.second -= minY;
  }

  int width = maxX - minX;
  int height = maxY - minY;

  vector<char> line(width + 1, '.');
//   grid[y][x]

  int rebasedTarget = target - minY;

  for (auto &it : pairs) {

    if (it.first.second == rebasedTarget) line[it.first.first] = 'S';
    if (it.second.second == rebasedTarget) line[it.second.first] = 'B';
  }

  for (auto &it : pairs) {
    int distance = abs(it.first.first - it.second.first) + abs(it.first.second - it.second.second);
    int sensorX = it.first.first;
    int sensorY = it.first.second;

    for (int x = sensorX - distance; x <= sensorX + distance; x++) {
      int upDistance = distance - abs(sensorX - x);
      if (sensorY - upDistance <= rebasedTarget && rebasedTarget <= sensorY + upDistance) {
//      for (int y = (sensorY - upDistance < 0) ? 0 : sensorY - upDistance;
//               y <= ((sensorY + upDistance <= height) ? sensorY + upDistance : height);
//               y++) {
        if (line[x] == '.') {
          line[x] = '#';
        }
      }
    }
  }

  int ans = 0;
  for (auto &it : line) {
    if (it != '.' && it != 'B') {
      ans++;
    }
  }

  cout << "Part 1: " << ans << endl;


  vector<pair<pair<int,int>, int>> pointDistances;

  for (auto &it : pairsPure) {
    pointDistances.emplace_back(it.first, abs(it.first.first - it.second.first) + abs(it.first.second - it.second.second));
  }

  vector<pair<int,int>> possiblePoints;

  for (auto &it : pointDistances) {

    pair<int, int> center = it.first;
    int distance = it.second + 1;

    pair<int, int> up = make_pair(center.first, center.second - distance);
    pair<int, int> down = make_pair(center.first, center.second + distance);
    pair<int, int> left = make_pair(center.first - distance, center.second);
    pair<int, int> right = make_pair(center.first + distance, center.second);

    pair<int, int> curr = up;

    while (curr != right) {
      curr.first += 1;
      curr.second += 1;

      if (0 <= curr.first && curr.first <= bound && 0 <= curr.second && curr.second <= bound) {
        possiblePoints.push_back(curr);
      }
    }
    if (0 <= right.first && right.first <= bound && 0 <= right.second && right.second <= bound) {
      possiblePoints.push_back(right);
    }

    while (curr != down) {
      curr.first -= 1;
      curr.second += 1;

      if (0 <= curr.first && curr.first <= bound && 0 <= curr.second && curr.second <= bound) {
        possiblePoints.push_back(curr);
      }
    }
    if (0 <= down.first && down.first <= bound && 0 <= down.second && down.second <= bound) {
      possiblePoints.push_back(down);
    }

    while (curr != left) {
      curr.first -= 1;
      curr.second -= 1;

      if (0 <= curr.first && curr.first <= bound && 0 <= curr.second && curr.second <= bound) {
        possiblePoints.push_back(curr);
      }
    }
    if (0 <= left.first && left.first <= bound && 0 <= left.second && left.second <= bound) {
      possiblePoints.push_back(left);
    }

    while (curr != up) {
      curr.first += 1;
      curr.second -= 1;

      if (0 <= curr.first && curr.first <= bound && 0 <= curr.second && curr.second <= bound) {
        possiblePoints.push_back(curr);
      }
    }
    if (0 <= up.first && up.first <= bound && 0 <= up.second && up.second <= bound) {
      possiblePoints.push_back(up);
    }


  }

  int x = 0;
  int y = 0;
  for (auto &it : possiblePoints) {
    if (getAllLonger(it.first, it.second, pointDistances)) {
      x = it.first;
      y = it.second;
      break;
    }
  }
//
//  int x = 0;
//  int y = 0;
//
//  while (y <= bound) {
//    if (getAllLonger(x, y, pointDistances)) break;
//
//    x++;
//    if (x > bound) {
//      x = 0;
//      y++;
//    }
//  }
//
//  priority_queue<Point> point_queue;
//
//  point_queue.push( Point{ getValuePriority(0, 0, pointDistances), make_pair(0,0)});
//
//  set<pair<int,int>> visited;
//
//  int x;
//  int y;
//
////  for (int y = 0; y <= 20; y++) {
////    for (int x = 0; x <= 20; x++) {
////      if (x == 14 && y == 11) cout << "!!!";
////      cout << "[" << getValuePriority(x, y, pointDistances) << "]";
////      if (x == 14 && y == 11) cout << "!!!";
////    }
////    cout << endl;
////  }
//
//  while (!point_queue.empty()) {
//    Point curr = point_queue.top();
//    point_queue.pop();
//
//    visited.insert(curr.data);
//    x = curr.data.first;
//    y = curr.data.second;
//
//    if (getAllLonger(x, y, pointDistances)) {
//      break;
//    }
//
//    unsigned long long size = visited.size();
//
//    Point set;
//    if (x > 0 && !visited.contains(make_pair(x - 1, y))) {
//      set = Point{ getValuePriority(x - 1, y, pointDistances), make_pair(x - 1, y) };
//      point_queue.push(set);
//    }
//
//    if (x < bound && !visited.contains(make_pair(x + 1, y))) {
//      set = Point{ getValuePriority(x + 1, y, pointDistances), make_pair(x + 1, y) };
//      point_queue.push(set);
//    }
//
//    if (y > 0 && !visited.contains(make_pair(x, y - 1))) {
//      set = Point{ getValuePriority(x, y - 1, pointDistances), make_pair(x, y - 1) };
//      point_queue.push(set);
//    }
//
//    if (y < bound && !visited.contains(make_pair(x, y + 1))) {
//      set = Point{ getValuePriority(x, y + 1, pointDistances), make_pair(x, y + 1) };
//      point_queue.push(set);
//    }
//
//  }


//  vector<vector<char>> grid(
//      bound + 1,
//      vector<char>(bound + 1, '.'));

//  int divideBy = 5;


//  int divideBy = 100;
//  long unit = bound/divideBy;
//
//  int currX = 0;
//  int currY = 0;
//  bool grid[unit*unit];
//  memset(grid, 0, unit*unit*sizeof(*grid));
//
//  cout << "HIT!" << endl;
//
//  int spot[unit];
//  memset(spot, 0, unit*sizeof(*spot));
//
//  int finalY = -1;
//
//  while (finalY == -1) {
//
//    for (auto &it : pairsPure) {
//      int distance = abs(it.first.first - it.second.first) + abs(it.first.second - it.second.second);
//      int sensorX = it.first.first;
//      int sensorY = it.first.second;
//      for (int x = (sensorX - distance < currX) ? currX : sensorX - distance;
//           x <= ((sensorX + distance < currX + unit) ? sensorX + distance : currX + unit - 1);
//           x++) {
//        int upDistance = distance - abs(sensorX - x);
//        for (int y = (sensorY - upDistance < currY) ? currY : sensorY - upDistance;
//             y <= ((sensorY + upDistance < currY + unit) ? sensorY + upDistance : currY + unit - 1);
//             y++) {
//
//          if (!grid[(y % unit) * unit + (x % unit)]) {
//            grid[(y % unit) * unit + (x % unit)] = true;
//            spot[y % unit]++;
//          }
//        }
//      }
//    }
//
//    for (int i = 0; i < unit; i++) {
//      if (spot[i] != unit) {
//        finalY = i;
//        break;
//      }
//    }
//
//    if (finalY == -1) {
//      currX += unit;
//      if (currX >= bound) {
//        currX = 0;
//        currY += unit;
//      }
//
//      memset(grid, 0, unit*unit*sizeof(*grid));
//      memset(spot, 0, unit*sizeof(*spot));
//    }
//
//  }
//
//  int finalX = 0;
//  for (int i = 0; i < unit; i++) {
//    if (!grid[finalY * unit + i]) {
//      finalX = i;
//      break;
//    }
//  }
//
//  finalX += currX;
//  finalY += currY;

//  for (auto &it1 : grid) {
//    for (auto &it2 : it1) {
//      cout << it2;
//    }
//    cout << endl;
//  }

  cout << x << "," << y << endl;
  cout << "Part 2: " << (unsigned long long) x * (unsigned long long) 4000000 + (unsigned long long) y << endl;


  return 0;
}
bool getAllLonger(int x, int y, vector<pair<pair<int, int>, int>> &data) {

  for (auto &it : data) {
    int distance = abs(x - it.first.first) + abs(y - it.first.second);
    if (distance - it.second <= 0) {
      return false;
    }
  }
  return true;
}

int getValuePriority(int x, int y, vector<pair<pair<int, int>, int>> &data) {
  int highest = 0;

  for (auto &it : data) {
    int distance = abs(x - it.first.first) + abs(y - it.first.second);
    highest = max(highest, it.second - distance);

  }

  return highest;

//  int val = 0;
//
//  for (auto &it : data) {
//    int distance = abs(x - it.first.first) + abs(y - it.first.second);
//    val += it.second - distance;
//
//  }
//
//  return val;
}

int getLowestDistance(int x, int y, vector<pair<pair<int, int>, pair<int, int>>> &data) {
  int lowest = INT32_MAX;

  for (auto &it : data) {
    lowest = min(lowest, abs(x - it.first.first) + abs(y - it.first.second));
  }

  return lowest;
}
int getValueSurroundings(int x, int y, vector<pair<pair<int, int>, pair<int, int>>> &data) {
  int acc = 0;

  for (auto &it : data) {
    acc += abs(x - it.second.first) + abs(y - it.second.second);
  }

  return acc;

}
