#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <sstream>
#include <set>
#include <numeric>
#include <algorithm>

#define ull unsigned long long int

using namespace std;

struct Entry {
  ull destination, source, range;
};

ull getDestination(ull source, vector<vector<Entry>>& almanac) {
  ull destination = source;

  for (vector<Entry>& category : almanac) {
    source = destination;
    for (Entry& entry : category) {
      if (source >= entry.source && source < entry.source + entry.range) {
        destination = entry.destination + (source - entry.source);
        break;
      }
    }
  }

  return destination;
}

void solve() {
  ull result_1 = 0;
  ull result_2 = ULLONG_MAX;

  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  vector<ull> seeds;
  vector<vector<Entry>> almanac;
  string line = "";
  getline(inputFile, line);

  stringstream ss(line);
  string item;
  ss >> item;

  while (ss >> item) {
    seeds.push_back(stoull(item));
  }

  while (getline(inputFile, line)) {
    if (line.size()) {
      if (line[line.size() - 1] == ':') {
        almanac.push_back(vector<Entry>());
      } else {
        stringstream ss(line);

        string dest, src, rng;

        ss >> dest >> src >> rng;

        Entry entry = {stoull(dest), stoull(src), stoull(rng)};

        almanac[almanac.size() - 1].push_back(entry);
      }
    }
  }

  vector<ull> locations;

  for (ull seed : seeds) {
    locations.push_back(getDestination(seed, almanac));
  }

  result_1 = *min_element(locations.begin(), locations.end());

    cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 5" << endl;
  solve();  // 340994526
}