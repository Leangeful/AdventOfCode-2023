#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <sstream>
#include <unordered_map>
#include <map>
#include <algorithm>

#define ull unsigned long long int

using namespace std;

struct Node {
  string key;
  string leftKey, rightKey;
  vector<int> idxs = vector<int>(2);
};

void solve() {
  ull result_1 = 0;
  ull result_2 = 0;

  vector<int> instr;
  vector<Node> nodes;
  map<string, int> keyIdxs;

  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  string line = "";

  getline(inputFile, line);
  cout << line << endl;

  instr = vector<int>(line.size());

  for (int i = 0; i < line.size(); i++)
    if (line[i] == 'R') instr[i] = 1;

  getline(inputFile, line);

  int keyIdx = 0;

  while (getline(inputFile, line)) {
    string keyStr, leftStr, rightStr;
    keyStr = line.substr(0, 3);
    leftStr = line.substr(7, 3);
    rightStr = line.substr(12, 3);

    keyIdxs.insert({keyStr, keyIdx});

    Node n;

    n.key = keyStr;
    n.leftKey = leftStr;
    n.rightKey = rightStr;

    nodes.push_back(n);

    keyIdx++;
  }

  inputFile.close();

  for (Node& n : nodes) {
    n.idxs[0] = keyIdxs.at(n.leftKey);
    n.idxs[1] = keyIdxs.at(n.rightKey);
  }

  ull instrCount = 0;
  int instrIdx = 0;
  int idx = keyIdxs.at("AAA");

  while (nodes[idx].key != "ZZZ") {
    instrCount++;

    idx = nodes[idx].idxs[instr[instrIdx]];

    instrIdx = (instrIdx + 1) % (instr.size());
  }

  result_1 = instrCount;

  cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 8" << endl;

  solve();  //  20777
            //
}