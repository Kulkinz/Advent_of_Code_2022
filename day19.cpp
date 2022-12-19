
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

    for (int i = 1; i <= 24; ++i) {
      cout << "== Minute " << i << " ==" << endl;


      bool buildGeode = false;
      bool buildObsidian = false;
      bool buildClay = false;
      bool buildOre = false;

      // actual complicated logic:

      // priority: build geode-cracking machine
      if (curr.obsidian >= bp.geodeCostObsidian && curr.ore >= bp.geodeCostOre) {
        curr.ore -= bp.geodeCostOre;
        curr.obsidian -= bp.geodeCostObsidian;
        buildGeode = true;
        cout << "Spend " << bp.geodeCostOre << " ore and " << bp.geodeCostObsidian << " obsidian to start building a geode-cracking robot." << endl;
      } else {

        // calculate how many turns until can build each at current rate
        int currentRateGeode = INT16_MAX;
        if (curr.obsidianMachine) {
          currentRateGeode = max((bp.geodeCostOre - curr.ore + curr.oreMachine - 1) / curr.oreMachine,
                                 (bp.geodeCostObsidian - curr.obsidian + curr.obsidianMachine - 1) / curr.obsidianMachine);

        }
        int currentRateObsidian = INT16_MAX;
        if (curr.clayMachine) {
          currentRateObsidian = max((bp.obsidianCostOre - curr.ore + curr.oreMachine - 1) / curr.oreMachine,
              (bp.obsidianCostClay - curr.clay + curr.clayMachine - 1) / curr.clayMachine);
        }
        int currentRateClay = (bp.clayCost - curr.ore + curr.oreMachine - 1) / curr.oreMachine;
        int currentRateOre = (bp.oreCost - curr.ore + curr.oreMachine - 1) / curr.oreMachine;

        if (currentRateObsidian <= 0 && bp.geodeCostObsidian > curr.obsidianMachine) {
          int newRateGeode = max((bp.geodeCostOre - (curr.ore - bp.obsidianCostOre) + curr.oreMachine - 1) / curr.oreMachine,
                                 (bp.geodeCostObsidian - curr.obsidian + (curr.obsidianMachine + 1) - 1) / (curr.obsidianMachine + 1));
          if (newRateGeode <= currentRateGeode) {
            curr.ore -= bp.obsidianCostOre;
            curr.clay -= bp.obsidianCostClay;
            buildObsidian = true;
            cout << "Spend " << bp.obsidianCostOre << " ore and " << bp.obsidianCostClay << " clay to start building an obsidian-collecting robot." << endl;
          }
        }

        if (currentRateOre <= 0 && !buildObsidian && !buildClay && maxOreRequired > curr.oreMachine) {
          int newRateGeode = INT16_MAX;
          if (curr.obsidianMachine) {
            newRateGeode = max((bp.geodeCostOre - (curr.ore - bp.oreCost) + (curr.oreMachine + 1) - 1) / (curr.oreMachine + 1),
                               (bp.geodeCostObsidian - curr.obsidian + curr.obsidianMachine - 1) / curr.obsidianMachine);

          }
          int newRateObsidian = INT16_MAX;
          if (curr.clayMachine) {
            newRateObsidian = max((bp.obsidianCostOre - (curr.ore - bp.oreCost) + (curr.oreMachine + 1) - 1) / (curr.oreMachine + 1),
                                  (bp.obsidianCostClay - curr.clay + curr.clayMachine - 1) / curr.clayMachine);
          }
          int newRateClay = (bp.clayCost - (curr.ore - bp.oreCost) + (curr.oreMachine + 1) - 1) / (curr.oreMachine + 1);

          if (newRateGeode < currentRateGeode
              || (newRateGeode == currentRateGeode && newRateObsidian <= currentRateObsidian)
              || (newRateGeode == currentRateGeode && newRateObsidian == currentRateObsidian && newRateClay <= currentRateClay)) {
            curr.ore -= bp.oreCost;
            buildOre = true;
            cout << "Spend " << bp.oreCost << " ore to start building a ore-collecting robot." << endl;
          }
        }
        if (currentRateClay <= 0 && !buildObsidian && !buildOre && bp.obsidianCostClay > curr.clayMachine) {

          int newRateGeode = INT16_MAX;
          if (curr.obsidianMachine) {
            newRateGeode = max((bp.geodeCostOre - (curr.ore - bp.clayCost) + curr.oreMachine) - 1 / curr.oreMachine,
                               (bp.geodeCostObsidian - curr.obsidian + curr.obsidianMachine) - 1 / curr.obsidianMachine);
          }
          int newRateObsidian = max((bp.obsidianCostOre - (curr.ore - bp.clayCost) + curr.oreMachine - 1) / curr.oreMachine,
                                    (bp.obsidianCostClay - curr.clay + (curr.clayMachine + 1) - 1) / (curr.clayMachine + 1));

          if (newRateGeode < currentRateGeode
          || (newRateGeode == currentRateGeode && newRateObsidian <= currentRateObsidian)) {
            curr.ore -= bp.clayCost;
            buildClay = true;
            cout << "Spend " << bp.clayCost << " ore to start building a clay-collecting robot." << endl;
          }
        }

      }

      if (curr.oreMachine) {
        curr.ore += curr.oreMachine;
        cout << curr.oreMachine << " ore-collecting robot collects " << curr.oreMachine << " ore; you now have " << curr.ore << " ore." << endl;
      }
      if (curr.clayMachine) {
        curr.clay += curr.clayMachine;
        cout << curr.clayMachine << " clay-collecting robot collects " << curr.clayMachine << " clay; you now have " << curr.clay << " clay." << endl;
      }
      if (curr.obsidianMachine) {
        curr.obsidian += curr.obsidianMachine;
        cout << curr.obsidianMachine << " obsidian-collecting robot collects " << curr.obsidianMachine << " obsidian; you now have " << curr.obsidian << " obsidian." << endl;
      }
      if (curr.geodeMachine) {
        curr.geode += curr.geodeMachine;
        cout << curr.geodeMachine << " geode-collecting robot cracks " << curr.geodeMachine << " geode; you now have " << curr.geode << " open geode." << endl;
      }

      // builds machine
      if (buildGeode) {
        curr.geodeMachine++;
        cout << "The new geode-cracking robot is ready; you now have " << curr.geodeMachine << " of them." << endl;
      }
      if (buildObsidian) {
        curr.obsidianMachine++;
        cout << "The new obsidian-collecting robot is ready; you now have " << curr.obsidianMachine << " of them." << endl;
      }
      if (buildClay) {
        curr.clayMachine++;
        cout << "The new clay-collecting robot is ready; you now have " << curr.clayMachine << " of them." << endl;
      }
      if (buildOre) {
        curr.oreMachine++;
        cout << "The new ore-collecting robot is ready; you now have " << curr.oreMachine << " of them." << endl;
      }

      cout << endl;
    }

    cout << "ID: " << bp.id << " Geodes: " << curr.geode << " Quality Number: " << bp.id * curr.geode << endl;
    acc += bp.id * curr.geode;

  }

  cout << "Part 1: " << acc << endl;

  return 0;
}