#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

vector<string> numWords{"",     "one", "two",   "three", "four",
                        "five", "six", "seven", "eight", "nine"};

void partOne() {
  unsigned long long int result = 0;

  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  char ch;
  string line = "";
  while (inputFile >> noskipws >> ch) {
    if (ch >= '1' && ch <= '9') {
      line += ch;
    } else if (ch == '\n') {
      string twoDig = string() + line[0] + line[line.size() - 1];
      result += stoi(twoDig);
      line = "";
    }
  }
  cout << "Result Part One: " << result << endl;
  inputFile.close();
}

void partTwo() {
  unsigned long long int result = 0;
  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  char ch;
  string line = "";
  while (getline(inputFile, line)) {
    // cout << line;
    for (int i = 1; i <= 9; i++) {
      size_t found = line.find(numWords[i]);
      while (found != string::npos) {
        line.replace(found + 1, 1, to_string(i));
        found = line.find(numWords[i]);
      }
    }
    // cout << "  " << line;

    string lineDigits = "";
    for (char ch : line) {
      if (ch >= '1' && ch <= '9') {
        lineDigits += string() + ch;
      }
    }
    // cout << "  " << lineDigits;
    string twoDig =
        string() + lineDigits[0] + lineDigits[lineDigits.size() - 1];
    result += stoi(twoDig);
    // cout << "  " << twoDig << "  " << result << endl;
  }
  cout << "Result Part Two: " << result << endl;
  inputFile.close();
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 1" << endl;

  partOne();  // 54644
  partTwo();  // 53348

  return 0;
}