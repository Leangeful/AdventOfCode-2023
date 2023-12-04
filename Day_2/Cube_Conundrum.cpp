#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

const map<string, int> theBag{{"red", 12}, {"green", 13}, {"blue", 14}};

void solve() {
  unsigned long long int result_one = 0;
  unsigned long long int result_two = 0;

  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  char delim = ' ';
  string line = "";
  while (getline(inputFile, line)) {
    stringstream ss(line);
    string num = "";

    getline(ss, num, delim);
    getline(ss, num, delim);
    int gameID = stoi(num);
    bool gameValid = true;
    map<string, int> maxCol{{"red", 1}, {"green", 1}, {"blue", 1}};

    while (getline(ss, num, delim)) {
      int n = stoi(num);
      string col;
      getline(ss, col, delim);

      if (n > theBag.find(col)->second) gameValid = false;
      if (n > maxCol.find(col)->second) maxCol[col] = n;
    }
    if (gameValid) {
      result_one += gameID;
    }
    cout << line << " ";

    result_two += (maxCol["red"]) * (maxCol["green"]) * (maxCol["blue"]);
    cout << result_two << endl;
  }

  cout << "Result Part One: " << result_one << endl;
  cout << "Result Part Two: " << result_two << endl;
  inputFile.close();
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 2" << endl;
  solve();  // 2416 63307
}