
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include "Helpers/HelperFunctions.h"

class Item {

 protected:
  string name;
  Item* parent = nullptr;
 public:
  virtual int getSize() {return 0;};
  virtual int getLessThan100000() {return 0;}
  virtual Item* getToDelete(int target) {return nullptr;}
  Item* getParent() {
    return parent;
  }
  void setParent(Item *parent) {
    this->parent = parent;
  }
  string getName() {
    return name;
  }
};

class Directory : public Item {
 private:
  map<string, Item*> contained;

 public:
  Directory(string name) {
    this->name = std::move(name);
  }
  int getSize() {
    int totalSize = 0;

    for (auto &it : contained) {
      totalSize += it.second->getSize();
    }
    return totalSize;
  }
  int getLessThan100000() {

    int sum = 0;

    for (auto &it : contained) {
      sum += it.second->getLessThan100000();
    }

    int size = getSize();

    if (size <= 100000) {
      sum += size;
    }

    return sum;
  }
  Item* findChild(string name) {
    return contained[name];
  }
  void addChild(string &name, Item *item) {
    contained[name] = item;
    item->setParent(this);
  }
  Item* getToDelete(int target) {

    Item* toDelete = nullptr;

    for (auto &it : contained) {
      Item* curr = it.second->getToDelete(target);
      if (curr != nullptr) { // is greater than
        if (toDelete == nullptr) {
          toDelete = curr;
        } else {
          if (curr->getSize() < toDelete->getSize()) {
            toDelete = curr;
          }
        }
      }

    }

    if (toDelete == nullptr) {
      if (getSize() >= target) {
        toDelete = this;
      }
    } else {
      if (getSize() < toDelete->getSize()) {
        toDelete = this;
      }
    }

    return toDelete;
  }

};

class File : public Item {

 private:
  int size;
 public:
  File(int size, string name) {
    this->size = size;
    this->name = std::move(name);
  }
  int getSize() {
    return size;
  }
  int getLessThan100000() {

    return 0;
  }
  Item* getToDelete(int target) {
    return nullptr;

  }
};



int main() {
  cout << "Day 7" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day7.txt)");
  string str;

  Directory *root = new Directory("/");

  Directory *curr = root;

  while (getline(file, str)) {
    if (str.find("$ cd") != string::npos) {
      vector<string> out;
      tokenize(str, ' ', out);
      string command = out[2];
      if (command == ("..")) {
        if (curr->getParent() == nullptr) continue;
        curr = (Directory *) (curr->getParent());
      } else if (command == ("/")) {
        curr = root;
      } else {
        curr = (Directory *) curr->findChild(command);
      }
    } else if (str.find("$ ls") != string::npos) {
      // none
    } else {
      vector<string> out;
      tokenize(str, ' ', out);
      if (out[0] == "dir") {
        if (curr->findChild(out[1]) == nullptr) {
          curr->addChild(out[1], new Directory(out[1]));
        }
      } else {
        if (curr->findChild(out[1]) == nullptr) {
          curr->addChild(out[1], new File(stoi(out[0]), out[1]));
        }
      }
    }
  }

  cout << "Part 1: " << root->getLessThan100000() << endl;

  int totalSize = root->getSize();

  int requiredDelete = 30000000 - (70000000 - totalSize);

  Item *selected = root->getToDelete(requiredDelete);

  cout << "Part 2: " << selected->getName() << ":" << selected->getSize() << endl;
//  cout << requiredDelete << endl;


  return 0;
}
