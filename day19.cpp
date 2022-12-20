
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <vector>
//#include <cstdlib>
#include <random>
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

int calculateNextMinute(available curr, int minute, map<int, int> &bestSoFar, int maxOreRequired, blueprint &bp);
int calculatePossible(const blueprint &bp, int minutes);
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
  int multi = 1;

  int x = 0;
  for (auto &bp : blueprints) {

    int maxGeode = 0;

    for (int i = 0; i < 100000; i++) {
      int temp = calculatePossible(bp, 24);

      maxGeode = max(maxGeode,  temp);
    }
    if (x < 3) {
      int maxGeode32 = 0;
      for (int i = 0; i < 5000000; i++) {
        int temp = calculatePossible(bp, 32);

        maxGeode32 = max(maxGeode32,  temp);
      }
      multi *= maxGeode32;
      cout << "32: " << maxGeode32 << " ";
      x++;
    }

    cout << "ID: " << bp.id << " Geodes: " << maxGeode << " Quality Number: " << bp.id * maxGeode << endl;

    acc += bp.id * maxGeode;

  }

  cout << "Part 1: " << acc << endl;
  cout << "Part 2: " << multi << endl;

  return 0;
}
int calculatePossible(const blueprint &bp, int minutes) {
  available curr;

  for (int i = 1; i <= minutes; ++i) {

//    int random = rand() % 100;
    random_device rd;
    int random = rd() % 100;

    bool buildGeode = false;
    bool buildObsidian = false;
    bool buildClay = false;
    bool buildOre = false;

    // actual complicated logic:

    if (curr.ore >= bp.geodeCostOre && curr.obsidian >= bp.geodeCostObsidian) buildGeode = true;
    if (!buildGeode && curr.ore >= bp.obsidianCostOre && curr.clay >= bp.obsidianCostClay && random <= 80) buildObsidian = true;
    if (!buildGeode && !buildObsidian && curr.ore >= bp.clayCost && random <= 50) buildClay = true;
    if (!buildGeode && !buildObsidian && !buildClay && curr.ore >= bp.oreCost && random <= 60) buildOre = true;

    if (curr.oreMachine) {
      curr.ore += curr.oreMachine;
    }
    if (curr.clayMachine) {
      curr.clay += curr.clayMachine;
    }
    if (curr.obsidianMachine) {
      curr.obsidian += curr.obsidianMachine;
    }
    if (curr.geodeMachine) {
      curr.geode += curr.geodeMachine;
    }

    // builds machine
    if (buildGeode) {
      curr.geodeMachine++;
      curr.obsidian -= bp.geodeCostObsidian;
      curr.ore -= bp.geodeCostOre;
    }
    if (buildObsidian) {
      curr.obsidianMachine++;
      curr.clay -= bp.obsidianCostClay;
      curr.ore -= bp.obsidianCostOre;
    }
    if (buildClay) {
      curr.clayMachine++;
      curr.ore -= bp.clayCost;
    }
    if (buildOre) {
      curr.oreMachine++;
      curr.ore -= bp.oreCost;
    }

  }

  return curr.geode;
}
int calculateNextMinute(available curr, int minute, map<int, int> &bestSoFar, const int maxOreRequired, blueprint &bp) {

  if (minute == 24) {
    bestSoFar[24] = max(bestSoFar[24], curr.geode);
    return curr.geode;
  }

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

  bestSoFar[minute] = max(bestSoFar[minute], curr.geode);

  int remainingTime = 24 - minute;
  if (curr.geode + (remainingTime)*(remainingTime + 1)/2 < bestSoFar[24]) return -1;

  int maxThisLevel = 0;

  if (buildGeode) {
    available upcoming = curr;
    upcoming.ore -= bp.geodeCostOre;
    upcoming.obsidian -= bp.geodeCostObsidian;
    upcoming.geodeMachine++;
    return calculateNextMinute(upcoming, minute+1, bestSoFar, maxOreRequired, bp);
  } else {
    maxThisLevel = max(maxThisLevel, calculateNextMinute(curr, minute+1, bestSoFar, maxOreRequired, bp));

    if (buildOre) {
      available upcoming = curr;
      upcoming.ore -= bp.oreCost;
      upcoming.oreMachine++;
      maxThisLevel = max(maxThisLevel, calculateNextMinute(upcoming, minute+1, bestSoFar, maxOreRequired, bp));
    }
    if (buildClay) {
      available upcoming = curr;
      upcoming.ore -= bp.clayCost;
      upcoming.clayMachine++;
      maxThisLevel = max(maxThisLevel, calculateNextMinute(upcoming, minute+1, bestSoFar, maxOreRequired, bp));
    }
    if (buildObsidian) {
      available upcoming = curr;
      upcoming.ore -= bp.obsidianCostOre;
      upcoming.clay -= bp.obsidianCostClay;
      upcoming.obsidianMachine++;
      maxThisLevel = max(maxThisLevel, calculateNextMinute(upcoming, minute+1, bestSoFar, maxOreRequired, bp));
    }
  }

  return maxThisLevel;
}
