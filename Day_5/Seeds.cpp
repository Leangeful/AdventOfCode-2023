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
#include <chrono>

#define ull unsigned long long int

using namespace std;
using namespace std::chrono;

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

  for (ull seed : seeds) locations.push_back(getDestination(seed, almanac));

  result_1 = *min_element(locations.begin(), locations.end());

  for (int i = 0; i < seeds.size() - 1; i += 2) {
    for (int k = seeds[i]; k < seeds[i + 1]; k++) {
      ull location = getDestination(k, almanac);
      if (location < result_2) {
        result_2 = location;
      }
    }
  }

  cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 5" << endl;

  auto start = high_resolution_clock::now();
  solve();  // 340994526 52210644
            //            7 min 47 s 41 ms 166 μs

  auto stop = high_resolution_clock::now();

  const auto mins = duration_cast<minutes>(stop - start);
  const auto secs = duration_cast<seconds>(stop - start - mins);
  const auto ms = duration_cast<milliseconds>(stop - start - mins - secs);
  const auto mis = duration_cast<microseconds>(stop - start - mins - secs - ms);

  cout << "Execution time: " << mins.count() << " min " << secs.count() << " s "
       << ms.count() << " ms " << mis.count() << " μs" << endl;
}