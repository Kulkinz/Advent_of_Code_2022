
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

class Node {
 public:
  Node(long long int data) {
    this->data = data;
  }
  long long int data;
  Node* next;
  Node* prev;
};

void printFrom0(const vector<Node *> &ref, int zeroIndex);
int main() {
  cout << "Day 20" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day20.txt)");
  string str;

  vector<long long int> input;

  long long int decryptionKey = 811589153;

  while (getline(file, str)) {
    input.push_back((long long int) stoi(str));
  }

  for (auto &it : input) {
    it *= decryptionKey;
  }

  int length = input.size();

  Node* front = nullptr;
  Node* curr = nullptr;

  vector<Node*> ref;

  for (auto &it : input) {
    Node* last = curr;
    curr = new Node(it);
    ref.push_back(curr);
    curr->prev = last;
    if (last != nullptr) {
      last->next = curr;
    }

    if (front == nullptr) {
      front = curr;
    }

  }


  curr->next = front;
  front->prev = curr;


  int zeroIndex = 0;
  for (int i = 0; i < length; i++) {
    if (input[i] == 0) {
      zeroIndex = i;
      break;
    }
  }

  for (int n = 0; n < 10; n++) {
//    printFrom0(ref, zeroIndex);
    for (int i = 0; i < length; ++i) {

      if (input[i] == 0) continue;

      Node* pointer = ref[i];
      long long int distance = (input[i] % length) + (input[i] / (long long int) length) % (length-1);

      Node* originalPrev = pointer->prev;
      Node* originalNext = pointer->next;

      pointer->next->prev = pointer->prev;
      pointer->prev->next = pointer->next;

      Node* navigate = pointer;
      bool isForward = distance >= 0;
      distance = abs(distance);
      for (int j = 0; j < distance; j++) {

        if (isForward) {
//        if (navigate == originalPrev) j++;
          navigate = navigate->next;
        } else {
//        if (navigate == originalNext) j++;
          navigate = navigate->prev;
        }
      }

      if (isForward) {
        pointer->next = navigate->next;
        pointer->prev = navigate;
        navigate->next->prev = pointer;
        navigate->next = pointer;
      } else {
        pointer->next = navigate;
        pointer->prev = navigate->prev;
        navigate->prev->next = pointer;
        navigate->prev = pointer;
      }


    }
  }

  printFrom0(ref, zeroIndex);

  Node* final = ref[zeroIndex];
  long long int acc = 0;

  cout << "ANS: " << endl;
  for (int i = 1; i <= 3000; i++) {
    final = final->next;
    if (i % 1000 == 0) {
      cout << final->data << endl;
      acc += final->data;
    }
  }

  cout << acc << endl;

  return 0;
}
void printFrom0(const vector<Node *> &ref, int zeroIndex) {
  Node* print = ref[zeroIndex];
  cout << print->data << ",";
  print = print->next;
  while (print != ref[zeroIndex]) {

    cout << print->data << ",";
    print = print->next;
  }
  cout << endl;
}
