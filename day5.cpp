
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "Helpers/HelperFunctions.h"

int main() {
  cout << "Day 5" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day5.txt)");
  string str;

  vector<string> input;

  while (getline(file, str)) {
    input.push_back(str);
  }

  int positionBottom = 7;
  int instructionStart = 10;
  int amountOfStacks = 9;

  vector<stack<char>> towers(amountOfStacks, stack<char>());

//  auto it = input.front();
//  auto itStacks = reverse_interator(it + positionBottom);
//  itStacks +=

  for (size_t i = positionBottom + 1; i--;) {
    string info = input[i];

    auto it = info.begin();
    it++;
    for (size_t j = 0; j < amountOfStacks; j++) {
      if (*it != ' ') {
        towers[j].push(*it);
      }
      it+= 4;
    }
  }

  auto it = input.begin();
  it += instructionStart;

//  while (it != input.end()) {
//
//    vector<string> out;
//    tokenize(*it, ' ', out);
//
//    int amount = stoi(out[1]);
//    int from = stoi(out[3]) - 1;
//    int to = stoi(out[5]) - 1;
//
//    for (int i = 0; i < amount; i++) {
//      char move = towers[from].top();
//      towers[from].pop();
//      towers[to].push(move);
//    }
//
//    it++;
//  }

  stack<char> temp;

  while (it != input.end()) {

    vector<string> out;
    tokenize(*it, ' ', out);

    int amount = stoi(out[1]);
    int from = stoi(out[3]) - 1;
    int to = stoi(out[5]) - 1;


    for (int i = 0; i < amount; i++) {
      char move = towers[from].top();
      towers[from].pop();
      temp.push(move);
    }

    for (int i = 0; i < amount; i++) {
      char move = temp.top();
      temp.pop();
      towers[to].push(move);
    }

    it++;
  }

  string ans;
  for (int i = 0; i < amountOfStacks; i++) {
    ans.push_back(towers[i].top());
  }



  cout << "Answer: " << ans << endl;
  return 0;
}
