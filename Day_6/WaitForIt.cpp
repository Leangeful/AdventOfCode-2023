#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <sstream>

#define ull unsigned long long int

using namespace std;

void solve() {
  ull result_1 = 1;
  ull result_2 = 0;
  vector<int> times;
  vector<int> distances;

  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  string timeLine, recordLine = "";

  getline(inputFile, timeLine);
  getline(inputFile, recordLine);

  inputFile.close();

  vector<string> timeStrs(4);
  stringstream ss(timeLine);

  ss >> timeStrs[0];
  ss >> timeStrs[0] >> timeStrs[1] >> timeStrs[2] >> timeStrs[3];

  vector<string> distStrs(4);
  ss = stringstream(recordLine);

  ss >> distStrs[0];
  ss >> distStrs[0] >> distStrs[1] >> distStrs[2] >> distStrs[3];

  string timePt2Str = "";
  string distPt2Str = "";

  for (int i = 0; i < timeStrs.size(); i++) {
    times.push_back(stoi(timeStrs[i]));
    timePt2Str += string() + timeStrs[i];

    distances.push_back(stoi(distStrs[i]));
    distPt2Str += string() + distStrs[i];
  }

  for (int i = 0; i < times.size(); i++) {
    int currentPossible = 0;
    for (int k = 0; k <= times[i] / 2; k++) {
      if (k * (times[i] - k) > distances[i]) currentPossible += 2;
    }
    result_1 *= currentPossible;
  }

  ull timePt2 = stoull(timePt2Str);
  ull distPt2 = stoull(distPt2Str);

  for (int i = 0; i <= timePt2 / 2; i++) {
    if (i * (timePt2 - i) > distPt2) result_2 += 2;
  }

  cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 6" << endl;

  solve();  //  316800
            //  45647654
}