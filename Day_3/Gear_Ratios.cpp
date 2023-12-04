#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

void solve() {
  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }
  unsigned long long int result_1 = 0;
  unsigned long long int result_2 = 0;
  vector<unsigned int> schematic(140 * 140);

  vector<unsigned int> nums{0};
  vector<unsigned int> symbolPos;
  vector<char> symbols;

  string numStr;
  unsigned int pos = 0;
  char ch;
  int numIdx = 1;
  while (inputFile >> noskipws >> ch) {
    if (ch >= '0' && ch <= '9') {
      if (!numStr.size()) nums.push_back(0);
      numStr += string() + ch;
      schematic[pos] = numIdx;
      pos++;
    } else {
      if (numStr.size()) {
        nums[nums.size() - 1] = stoi(numStr);
        numIdx++;
        numStr = "";
      }
      if (ch != '\n') {
        if (ch != '.') {
          symbolPos.push_back(pos);
          symbols.push_back(ch);
        }
        pos++;
      }
    }
  }

  inputFile.close();

  vector<int> idxsAround(8);
  for (int i = 0; i < symbolPos.size(); i++) {
    unsigned int spos = symbolPos[i];
    char sym = symbols[i];

    set<unsigned int> pointers;

    idxsAround[0] = spos + 1;
    idxsAround[1] = spos - 1;
    idxsAround[2] = spos + 139;
    idxsAround[3] = spos + 140;
    idxsAround[4] = spos + 141;
    idxsAround[5] = spos - 139;
    idxsAround[6] = spos - 140;
    idxsAround[7] = spos - 141;

    for (int i : idxsAround) {
      if (i > 0 && i < 19600)
        if (schematic[i] != 0) pointers.insert(schematic[i]);
    }

    for (auto p : pointers) {
      result_1 += nums[p];
    }

    if (sym == '*' && pointers.size() == 2) {
      unsigned int gearRatio = 1;
      for (auto p : pointers) {
        gearRatio *= nums[p];
      }
      result_2 += gearRatio;
    }
  }
  cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 3" << endl;
  solve();  // 533784 78826761
}