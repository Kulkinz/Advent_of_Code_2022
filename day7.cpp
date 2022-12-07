
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
  int size;
  Item* parent;
 public:
  Item(string name, int size, Item* parent) {
    this->name = std::move(name);
    this->size = size;
    this->parent = parent;
  }
  virtual int getSize() {
    return size;
  }
  virtual int getLessThan100000Sum() { return 0; }
  virtual Item* getToDelete(int target) { return nullptr; }
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
  Directory(string name) : Item(std::move(name), 0, nullptr) {
  }
  int getSize() override {

    if (size == 0) {
      int totalSize = 0;

      for (auto &it : contained) {
        totalSize += it.second->getSize();
      }

      size = totalSize;
    }

    return size;
  }
  int getLessThan100000Sum() override {

    int sum = 0;

    for (auto &it : contained) {
      sum += it.second->getLessThan100000Sum();
    }

    int size = getSize();

    if (size <= 100000) {
      sum += size;
    }

    return sum;
  }
  Item* findChild(const string& name) {
    return contained[name];
  }
  void addChild(string &name, Item *item) {
    contained[name] = item;
    item->setParent(this);
  }
  Item* getToDelete(int target) override {

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

 public:
  File(int size, string name) : Item(std::move(name), size, nullptr) { }
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

  cout << "Part 1: " << root->getLessThan100000Sum() << endl;

  int totalSize = root->getSize();

  int requiredDelete = 30000000 - (70000000 - totalSize);

  Item *selected = root->getToDelete(requiredDelete);

  cout << "Part 2: " << selected->getName() << ":" << selected->getSize() << endl;


  return 0;
}
