
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

queue<pair<int,int>*> getPairs(string str);
bool isCorrectValue(string &left, string trimmedLeft, queue<pair<int,int>*> &leftBrackets,
                    string &right, string trimmedRight, queue<pair<int,int>*> &rightBrackets);

bool hasDecided = false;
bool sortFunction(const string &lhs, const string &rhs);

int main() {
  cout << "Day 13" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day13.txt)");
  string str;


  int index = 1;
  int ans1 = 0;
  string left = "";
  string right = "";
  queue<pair<int,int>*> leftBrackets;
  queue<pair<int,int>*> rightBrackets;

  vector<string> order;

  while (getline(file, str)) {
    if (str.empty()) {
//      hasDecided = false;
//      if (isCorrectValue(left, left, leftBrackets,
//                         right, right, rightBrackets)) {
//        ans1 += index;
//        cout << "True!" << endl;
//      } else {
//        cout << "False!" << endl;
//      }
//      left.clear();
//      right.clear();
//      queue<pair<int,int>*> empty = queue<pair<int,int>*>();
//      swap(leftBrackets, empty);
//      empty = queue<pair<int,int>*>();
//      swap(rightBrackets, empty);
//      index++;
//      cout << "NEXT" << endl;
      continue;
    }
//    queue<pair<int,int>*> *writeTo;
//
//    if (left.empty()) {
//      left = str;
//      writeTo = &leftBrackets;
//    } else {
//      right = str;
//      writeTo = &rightBrackets;
//    }

    order.push_back(str);
  }

  sort(order.begin(), order.end(), sortFunction);

  cout << ans1 << endl;

//  for (auto &it: order) {
//    cout << it << endl;
//  }

  int ans2 = 1;

  for (int i = 0; i < order.size(); i++) {
    if (order[i] == "[[2]]" || order[i] == "[[6]]") {
      ans2 *= i+1;
    }
  }

  cout << ans2 << endl;

  return 0;
}

bool sortFunction(const string &lhs, const string &rhs) {

  queue<pair<int,int>*> leftBrackets = getPairs(lhs);
  queue<pair<int,int>*> rightBrackets = getPairs(rhs);

  hasDecided = false;

  string left = lhs;
  string right = rhs;
  return isCorrectValue(left, left, leftBrackets, right, right, rightBrackets);
}

queue<pair<int,int>*> getPairs(string str) {

  queue<pair<int,int>*> brackets;
  stack<pair<int,int>*> positionPairs;

  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '[') {
      pair<int,int> *currPair = new pair<int,int>(i,0);
      brackets.push(currPair);
      positionPairs.push(currPair);
    } else if (str[i] == ']') {
      pair<int,int> *corresponding = positionPairs.top();
      (*corresponding).second = i;
      positionPairs.pop();
    }
  }

  return brackets;
}
bool isCorrectValue(string &left, string trimmedLeft, queue<pair<int,int>*> &leftBrackets,
                    string &right, string trimmedRight, queue<pair<int,int>*> &rightBrackets) {

  if (hasDecided) return true;
  cout << "left: " << trimmedLeft << endl;
  cout << "right: " << trimmedRight << endl;
  if (trimmedLeft.empty() && trimmedRight.empty()) {
    return true;
  } else if (trimmedLeft.empty()) {
    hasDecided = true;
    return true;
  }
  if (trimmedRight.empty()) return false;


  // four cases
  if (trimmedLeft[0] == '[' && trimmedRight[0] == '[') {
    string nextLeft;
    pair<int,int> newLeftCurr;
    if (!leftBrackets.empty()) {
      newLeftCurr = *leftBrackets.front();
      leftBrackets.pop();
      nextLeft = left.substr(newLeftCurr.first+1, (newLeftCurr.second-newLeftCurr.first-1));
    } else {
      nextLeft = trimmedLeft.substr(1, trimmedLeft.length() - 2);
    }

    string nextRight;
    pair<int,int> newRightCurr;
    if (!rightBrackets.empty()) {
      newRightCurr = *rightBrackets.front();
      rightBrackets.pop();
      nextRight = right.substr(newRightCurr.first+1, (newRightCurr.second-newRightCurr.first-1));
    } else {
      nextRight = trimmedRight.substr(1, trimmedRight.length() - 2);
    }

    if (isCorrectValue(left, nextLeft, leftBrackets, right, nextRight, rightBrackets)) {

      string remainderLeft;
      if (trimmedLeft.length() == nextLeft.length() + 2) {
        remainderLeft = "";
      } else {
        remainderLeft = trimmedLeft.substr(nextLeft.length() + 3, -1);
      }
      string remainderRight;
      if (trimmedRight.length() == nextRight.length() + 2) {
        remainderRight = "";
      } else {
        remainderRight = trimmedRight.substr(nextRight.length() + 3, -1);
      }

      while (!leftBrackets.empty() && newLeftCurr.second > leftBrackets.front()->second) {
        leftBrackets.pop();
      }
      while (!rightBrackets.empty() && newRightCurr.second > rightBrackets.front()->second) {
        rightBrackets.pop();
      }

      return isCorrectValue(left, remainderLeft, leftBrackets, right, remainderRight, rightBrackets);
    } else {
      return false;
    }

  } else if (trimmedLeft[0] == '[') {

    string nextLeft;
    pair<int,int> newLeftCurr;
    if (!leftBrackets.empty()) {
      newLeftCurr = *leftBrackets.front();
      leftBrackets.pop();
      nextLeft = left.substr(newLeftCurr.first+1, (newLeftCurr.second-newLeftCurr.first-1));
    } else {
      nextLeft = trimmedLeft.substr(1, trimmedLeft.length() - 2);
    }

    size_t foundRight = trimmedRight.find(',');
    string nextRight = trimmedRight.substr(0, foundRight);

    if (isCorrectValue(left, nextLeft, leftBrackets, right, nextRight, rightBrackets)) {
      string remainderLeft;
      if (trimmedLeft.length() == nextLeft.length() + 2) {
        remainderLeft = "";
      } else {
        remainderLeft = trimmedLeft.substr(nextLeft.length() + 3, -1);
      }
      string remainderRight;
      if (trimmedRight.length() == nextRight.length()) {
        remainderRight = "";
      } else {
        remainderRight = trimmedRight.substr(nextRight.length() + 1, -1);
      }

      while (!leftBrackets.empty() && newLeftCurr.second > leftBrackets.front()->second) {
        leftBrackets.pop();
      }
      return isCorrectValue(left, remainderLeft, leftBrackets, right, remainderRight, rightBrackets);
    } else {
      return false;
    }

  } else if (trimmedRight[0] == '[') {
    size_t foundLeft = trimmedLeft.find(',');
    string nextLeft = trimmedLeft.substr(0, foundLeft);

    string nextRight;
    pair<int,int> newRightCurr;
    if (!rightBrackets.empty()) {
      newRightCurr = *rightBrackets.front();
      rightBrackets.pop();
      nextRight = right.substr(newRightCurr.first+1, (newRightCurr.second-newRightCurr.first-1));
    } else {
      nextRight = trimmedRight.substr(1, trimmedRight.length() - 2);
    }

    if (isCorrectValue(left, nextLeft, leftBrackets, right, nextRight, rightBrackets)) {
      string remainderLeft;
      if (trimmedLeft.length() == nextLeft.length()) {
        remainderLeft = "";
      } else {
        remainderLeft = trimmedLeft.substr(nextLeft.length() + 1, -1);
      }
      string remainderRight;
      if (trimmedRight.length() == nextRight.length() + 2) {
        remainderRight = "";
      } else {
        remainderRight = trimmedRight.substr(nextRight.length() + 3, -1);
      }

      while (!rightBrackets.empty() && newRightCurr.second > rightBrackets.front()->second) {
        rightBrackets.pop();
      }
      return isCorrectValue(left, remainderLeft, leftBrackets, right, remainderRight, rightBrackets);
    } else {
      return false;
    }

  } else {

    size_t foundLeft = trimmedLeft.find(',');
    size_t foundRight = trimmedRight.find(',');

    int valLeft = stoi(trimmedLeft.substr(0, foundLeft));
    int valRight = stoi(trimmedRight.substr(0, foundRight));

    if (valLeft < valRight) {
      hasDecided = true;
      return true;
    } else if (valLeft == valRight) {
      string nextLeft = (foundLeft != string::npos) ? trimmedLeft.substr(foundLeft + 1) : "";
      string nextRight = (foundRight != string::npos) ? trimmedRight.substr(foundRight + 1) : "";
      return isCorrectValue(left, nextLeft, leftBrackets, right, nextRight, rightBrackets);
    } else {
      return false;
    }
  }
}
