#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <sstream>
#include <set>
#include <numeric>

#define ull unsigned long long int

using namespace std;

void solve() {
  ull result_1 = 0;
  ull result_2 = 0;

  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  vector<int> allWins;
  string line = "";
  while (getline(inputFile, line)) {
    set<string> winningNumbers;

    stringstream ss(line);
    string item;
    ss >> item;
    ss >> item;

    int wins = 0;

    while (ss >> item) {
      if (item == "|") break;
      winningNumbers.insert(item);
    }

    while (ss >> item)
      if (winningNumbers.find(item) != winningNumbers.end()) {
        wins++;
      }

    allWins.push_back(wins);

    if (wins) result_1 += pow(2, wins - 1);
  }

  inputFile.close();

  vector<int> copies(allWins.size(), 1);

  for (int i = 0; i < allWins.size(); i++) {
    for (int k = allWins[i]; k > 0; k--) {
      copies[i + k] += copies[i];
    }
  }

  result_2 = accumulate(copies.begin(), copies.end(), 0u);

  cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 5" << endl;
  solve();  // 23678 15455663
}