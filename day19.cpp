
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_map>
#include "Helpers/HelperFunctions.h"

struct blueprint {
  int id;
  int oreCost;
  int clayCost;
  int obsidianCostOre;
  int obsidianCostClay;
  int geodeCostOre;
  int geodeCostObsidian;
};

struct available {
  int ore = 0;
  int clay = 0;
  int obsidian = 0;
  int geode = 0;

  int oreMachine = 1;
  int clayMachine = 0;
  int obsidianMachine = 0;
  int geodeMachine = 0;

  bool operator==(const available &other) const {
    return (ore == other.ore
        && clay == other.clay
        && obsidian == other.obsidian
        && geode == other.geode
        && oreMachine == other.oreMachine
        && clayMachine == other.clayMachine
        && obsidianMachine == other.obsidianMachine
        && geodeMachine == other.geodeMachine);
  }
};

namespace std {
template<>
struct hash<available> {
  std::size_t operator()(const available &k) const {
    using std::hash;
    return (((hash<int>()(k.ore) & 0b11111111)
        & ((hash<int>()(k.clay) & 0b11111111) << 8)
        & ((hash<int>()(k.obsidian) & 0b11111111) << 16)
        & ((hash<int>()(k.geode) & 0b11111111) << 24)
        & ((hash<int>()(k.oreMachine) & 0b11111111) << 32)
        & ((hash<int>()(k.clayMachine) & 0b11111111) << 40)
        & ((hash<int>()(k.obsidianMachine) & 0b11111111) << 48)
        & ((hash<int>()(k.geodeMachine) & 0b11111111) << 56)));
  }
};
}

int main() {
  cout << "Day 19" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day19.txt)");
  string str;

  vector<blueprint> blueprints;

  while (getline(file, str)) {
    vector<string> out;
    tokenize(str, ' ', out);

    blueprints.push_back({ stoi(out[1].substr(0,out[1].length()-1)),
                           stoi(out[6]),
                           stoi(out[12]),
                           stoi(out[18]),
                           stoi(out[21]),
                           stoi(out[27]),
                           stoi(out[30]) });

  }

  int acc = 0;

  for (auto &bp : blueprints) {
    available curr;

    int maxOreRequired = bp.oreCost;
    maxOreRequired = max(maxOreRequired, bp.clayCost);
    maxOreRequired = max(maxOreRequired, bp.obsidianCostOre);
    maxOreRequired = max(maxOreRequired, bp.geodeCostOre);

    int maxGeode = 0;

    queue<available> currQueue;
    queue<available> next;
//    unordered_map<available, bool> seen;

    currQueue.push(curr);

    for (int n = 1; n <= 24; ++n) {

      int x = currQueue.size();

      int bestSoFar = 0;

      while (!currQueue.empty()) {
        available curr = currQueue.front();
        currQueue.pop();

        bool buildGeode = false;
        bool buildObsidian = false;
        bool buildClay = false;
        bool buildOre = false;

        if (curr.ore >= bp.oreCost && curr.oreMachine < maxOreRequired) buildOre = true;
        if (curr.ore >= bp.clayCost && curr.clayMachine < bp.obsidianCostClay) buildClay = true;
        if (curr.ore >= bp.obsidianCostOre && curr.clay >= bp.obsidianCostClay && curr.obsidianMachine < bp.geodeCostObsidian) buildObsidian = true;
        if (curr.ore >= bp.geodeCostOre && curr.obsidian >= bp.geodeCostObsidian) buildGeode = true;

        curr.ore += curr.oreMachine;
        curr.clay += curr.clayMachine;
        curr.obsidian += curr.obsidianMachine;
        curr.geode += curr.geodeMachine;

        bestSoFar = max(bestSoFar, curr.geode);

        if (bestSoFar > curr.geode) continue;

//        if (!seen[curr]) {
//          seen[curr] = true;
          next.push(curr);
//        }

        if (buildOre) {
          available upcoming = curr;
          upcoming.ore -= bp.oreCost;
          upcoming.oreMachine++;
//          if (!seen[upcoming]) {
//            seen[upcoming] = true;
            next.push(upcoming);
//          }
        }
        if (buildClay) {
          available upcoming = curr;
          upcoming.ore -= bp.clayCost;
          upcoming.clayMachine++;
//          if (!seen[upcoming]) {
//            seen[upcoming] = true;
            next.push(upcoming);
//          }
        }
        if (buildObsidian) {
          available upcoming = curr;
          upcoming.ore -= bp.obsidianCostOre;
          upcoming.clay -= bp.obsidianCostClay;
          upcoming.obsidianMachine++;
//          if (!seen[upcoming]) {
//            seen[upcoming] = true;
            next.push(upcoming);
//          }
        }
        if (buildGeode) {
          available upcoming = curr;
          upcoming.ore -= bp.geodeCostOre;
          upcoming.obsidian -= bp.geodeCostObsidian;
          upcoming.geodeMachine++;
//          if (!seen[upcoming]) {
//            seen[upcoming] = true;
            next.push(upcoming);
//          }
        }
      }

      swap(currQueue, next);
//      seen.clear();
    }

    while (!currQueue.empty()) {
      available curr = currQueue.front();
      currQueue.pop();

      maxGeode = max(maxGeode, curr.geode);
    }

    cout << "ID: " << bp.id << " Geodes: " << maxGeode << " Quality Number: " << bp.id * maxGeode << endl;
    acc += bp.id * maxGeode;

  }

  cout << "Part 1: " << acc << endl;

  return 0;
}