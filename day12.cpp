
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include "Helpers/HelperFunctions.h"

int xSize;
int ySize;

void calculateStepNext (vector<vector<int>> &heightMap, vector<vector<int>> &steps, pair<int,int> calculate, pair<int,int> &end, queue<pair<int,int>> &queue);

int main() {
  cout << "Day 12" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day12.txt)");
  string str;

  vector<string> data;

  while (getline(file, str)) {
    data.push_back(str);
  }

  xSize = data[0].size();
  ySize = data.size();

  vector<vector<int>> grid(
      xSize,
      vector<int>(ySize));

  pair<int, int> startPair;
  pair<int, int> endPair;

  queue<pair<int, int>> aPoints;

  for (int y = 0; y < ySize; y++) {
    for (int x = 0; x < xSize; x++) {
      if (data[y][x] == 'S') {
        grid[x][y] = 0;
        startPair = pair(x,y);
      } else if (data[y][x] == 'E') {
        grid[x][y] = 'z' - 'a';
        endPair = pair(x,y);
      } else {
        grid[x][y] = data[y][x] - 'a';
        if (data[y][x] == 'a') {
          aPoints.push(pair(x,y));
        }
      }
    }
  }

  vector<vector<int>> steps(
      xSize,
      vector<int>(ySize, INT16_MAX));

  steps[startPair.first][startPair.second] = 0;

  queue<pair<int,int>> queue;
  calculateStepNext(grid, steps, startPair, endPair, queue);

  cout << "Part 1: " << steps[endPair.first][endPair.second] << endl;

  while (!aPoints.empty()) {
    pair<int,int> next = aPoints.front();
    aPoints.pop();
    steps[next.first][next.second] = 0;
    calculateStepNext(grid, steps, next, endPair, queue);
  }

  cout << "Part 2: " << steps[endPair.first][endPair.second] << endl;

  return 0;
}

void calculateStepNext (vector<vector<int>> &heightMap, vector<vector<int>> &steps, pair<int,int> calculate, pair<int,int> &end, queue<pair<int,int>> &queue) {

  if (calculate == end) {
    if (!queue.empty()) {
      pair<int,int> next = queue.front();
      queue.pop();
      calculateStepNext(heightMap, steps, next, end, queue);
    }
    return;
  }
  int currX = calculate.first;
  int currY = calculate.second;

  int currStep = steps[currX][currY];

  if (currX > 0) {
    if (heightMap[currX - 1][currY] - heightMap[currX][currY] <= 1 && currStep + 1 < steps[currX - 1][currY]) {
      steps[currX - 1][currY] = currStep + 1;
      queue.push(pair<int, int>(currX - 1, currY));
    }
  }
  if (currX < xSize - 1) {
    if (heightMap[currX + 1][currY] - heightMap[currX][currY] <= 1 && currStep + 1 < steps[currX + 1][currY]) {
      steps[currX + 1][currY] = currStep + 1;
      queue.push(pair<int, int>(currX + 1, currY));
    }
  }
  if (currY > 0) {
    if (heightMap[currX][currY - 1] - heightMap[currX][currY] <= 1 && currStep + 1 < steps[currX][currY - 1]) {
      steps[currX][currY - 1] = currStep + 1;
      queue.push(pair<int, int>(currX, currY - 1));
    }
  }
  if (currY < ySize - 1) {
    if (heightMap[currX][currY + 1] - heightMap[currX][currY] <= 1 && currStep + 1 < steps[currX][currY + 1]) {
      steps[currX][currY + 1] = currStep + 1;
      queue.push(pair<int, int>(currX, currY + 1));
    }
  }

  if (!queue.empty()) {
    pair<int,int> next = queue.front();
    queue.pop();
    calculateStepNext(heightMap, steps, next, end, queue);
  }

}