
using namespace std;

#include <iostream>
#include <fstream>
#include <string>

int main() {
  cout << "MAIN" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day1.txt)");
  string str;
  while (getline(file, str)) {
    cout << str << endl;
  }

  return 0;
}
