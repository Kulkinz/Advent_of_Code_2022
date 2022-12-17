
using namespace std;

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <vector>
#include <cmath>
#include "Helpers/HelperFunctions.h"

struct valve {
  string name;
  int rate;

  vector<valve*> connections;

  friend std::ostream& operator<< (std::ostream& os, valve const& e) {
    return os << "{ " << e.name << ", '" << e.rate << "' } ";
  }

};

struct step {
  bitset<64> active;
  int minute = 0;
  int rate = 0;
  int acc = 0;
  string human = "AA";
  int willReachH = 0;
  int possibleH = 0;
  int rateH = 0;
  string elephant = "AA";
  int willReachE = 0;
  int possibleE = 0;
  int rateE = 0;

  friend std::ostream& operator<< (std::ostream& os, step const& e) {
    return os << "{ shared: " << e.active << ", " << e.minute + 1  << ", " << e.rate << ", " << e.acc
              << ", human: " << e.human << ", " << e.willReachH  << ", " << e.rateH << ", " << e.possibleH
              << ", elephant: " << e.elephant << ", " << e.willReachE  << ", " << e.rateE << ", " << e.possibleE << " } ";
  }

  friend bool operator> (step const& lhs, step const& rhs) {
    return lhs.acc > rhs.acc;
  }
};

map<string, int> getDistances(valve *start);

int main() {
  cout << "Day 16" << endl;
  ifstream file(R"(C:\Users\gwen\Documents\2_Programming\Advent of Code\Advent of Code 2022\inputs\day16.txt)");
  string str;

  map<string, valve*> listValves;

  vector<string> data;

  while (getline(file, str)) {
    data.push_back(str);

  }

  int length = data.size();

  for (auto &it : data) {
    vector<string> out;
    tokenize(it, ' ', out);

    vector<string> flow;
    tokenize(out[4], '=', flow);

    string name = out[1];
    int rate = stoi(flow[1].substr(0, flow[1].length() - 1));

    listValves[name] = new valve;

    listValves[name]->name = name;
    listValves[name]->rate = rate;

  }

  for (auto &it : data) {

    vector<string> out;
    tokenize(it, ' ', out);
    string name = out[1];

    out.clear();
    tokenize(it, "valves", out);

    vector<string> connects;
    tokenize(out[1], ',', connects);

    for (auto &it2 : connects) {
      string trimmed = it2.substr(1);
      listValves[name]->connections.push_back(listValves[trimmed]);
    }
  }

  map<string, map<string, int>> distances;

  for (auto &it : listValves) {
    distances[it.first] = getDistances(it.second);
  }

  map<string, int> positions;

  int i = 0;
  for (auto &it : listValves) {
    positions[it.first] = i;
    i++;
  }

  string curr = "AA";

  queue<step> queue;

  int maxMinute = 26;

  for (auto &it1 : listValves) {
    for (auto &it2 : listValves) {
      if (it1.second->rate > 0 && it2.second->rate > 0 && it1 != it2) {
        int distanceAwayH = distances[curr][it1.first] + 1;
        int possibleH = (maxMinute - distanceAwayH) * listValves[it1.first]->rate;

        int distanceAwayE = distances[curr][it2.first] + 1;
        int possibleE = (maxMinute - distanceAwayE) * listValves[it2.first]->rate;

        step next;
        next.active[positions[it1.first]] = true;
        next.active[positions[it2.first]] = true;
//        next.acc += possibleH;
//        next.rate += listValves[it1.first]->rate;
//        next.minute = distanceAwayH;
        next.human = it1.first;
        next.possibleH = possibleH;
        next.willReachH = distanceAwayH;
        next.rateH = listValves[it1.first]->rate;

        next.elephant = it2.first;
        next.possibleE = possibleE;
        next.willReachE = distanceAwayE;
        next.rateE = listValves[it2.first]->rate;

//        cout << next << endl;
        queue.push(next);
      }
    }
  }

  int maxVal = 0;

  while (!queue.empty()) {
    step next = queue.front();
    queue.pop();

    if (next.willReachE < next.willReachH) {
      next.minute += next.willReachE;

      if (next.minute >= maxMinute) continue;
      next.acc += next.possibleE;
      next.rate += next.rateE;

      next.willReachH -= next.willReachE;

//      cout << "Elephant " << next << endl;
      maxVal = max(maxVal, next.acc);

      bool hasFoundOne = false;
      for (auto &it : listValves) {
        if (it.second->rate > 0 && !next.active[positions[it.first]]) {
          hasFoundOne = true;
          int distanceAway = distances[next.elephant][it.first] + 1;
          int possible = ((maxMinute - next.minute) - distanceAway) * listValves[it.first]->rate;

          step newStep = next;
          newStep.active[positions[it.first]] = true;

          newStep.elephant = it.first;
          newStep.possibleE = possible;
          newStep.willReachE = distanceAway;
          newStep.rateE = listValves[it.first]->rate;

          if (newStep.minute + distanceAway < maxMinute) {
            queue.push(newStep);
          }

        }
      }
      if (!hasFoundOne) {
        next.willReachE = maxMinute;
        queue.push(next);
      }
    } else if (next.willReachH < next.willReachE) {
      next.minute += next.willReachH;

      if (next.minute >= maxMinute) continue;
      next.acc += next.possibleH;
      next.rate += next.rateH;

      next.willReachE -= next.willReachH;

//      cout << "Human " << next << endl;
      maxVal = max(maxVal, next.acc);

      bool hasFoundOne = false;
      for (auto &it : listValves) {
        if (it.second->rate > 0 && !next.active[positions[it.first]]) {
          hasFoundOne = true;
          int distanceAway = distances[next.human][it.first] + 1;
          int possible = ((maxMinute - next.minute) - distanceAway) * listValves[it.first]->rate;

          step newStep = next;
          newStep.active[positions[it.first]] = true;

          newStep.human = it.first;
          newStep.possibleH = possible;
          newStep.willReachH = distanceAway;
          newStep.rateH = listValves[it.first]->rate;

          if (newStep.minute + distanceAway < maxMinute) {
            queue.push(newStep);
          }

        }
      }

      if (!hasFoundOne) {
        next.willReachH = maxMinute;
        queue.push(next);
      }

    } else {

      next.minute += next.willReachE;

      next.acc += next.possibleE;
      next.rate += next.rateE;

      next.acc += next.possibleH;
      next.rate += next.rateH;

//      cout << "Both " << next << endl;
      maxVal = max(maxVal, next.acc);

      for (auto &it1 : listValves) {
        for (auto &it2 : listValves) {
          if (it1.second->rate > 0 && it2.second->rate > 0 && !next.active[positions[it1.first]] && !next.active[positions[it2.first]] && it1.first != it2.first) {
            int distanceAwayH = distances[next.human][it1.first] + 1;
            int possibleH = ((maxMinute - next.minute) - distanceAwayH) * listValves[it1.first]->rate;
            int distanceAwayE = distances[next.elephant][it2.first] + 1;
            int possibleE = ((maxMinute - next.minute) - distanceAwayE) * listValves[it2.first]->rate;

            step newStep = next;
            newStep.active[positions[it1.first]] = true;
            newStep.active[positions[it2.first]] = true;

            newStep.human = it1.first;
            newStep.possibleH = possibleH;
            newStep.willReachH = distanceAwayH;
            newStep.rateH = listValves[it1.first]->rate;

            newStep.elephant = it2.first;
            newStep.possibleE = possibleE;
            newStep.willReachE = distanceAwayE;
            newStep.rateE = listValves[it2.first]->rate;

            if (newStep.minute + min(distanceAwayH, distanceAwayE) < maxMinute) {
              queue.push(newStep);
            }

          }
        }
      }

    }
  }

  cout << maxVal << endl;

  return 0;
}

map<string, int> getDistances(valve *start) {

  set<string> visited;
  visited.insert(start->name);

  map<string, int> mapped = map<string, int>();
  mapped[start->name] = 0;

  queue<valve*> queue;
  for (auto &it : start->connections) {
    if (!visited.contains(it->name)) {
      queue.push(it);
      visited.insert(it->name);
      mapped[it->name] = mapped[start->name] + 1;
    }
  }

  while (!queue.empty()) {
    valve* curr = queue.front();
    queue.pop();
    for (auto &it : curr->connections) {
      if (!visited.contains(it->name)) {
        queue.push(it);
        visited.insert(it->name);
        mapped[it->name] = mapped[curr->name] + 1;
      }
    }
  }

  return mapped;

}
