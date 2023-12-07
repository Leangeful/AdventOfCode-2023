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

enum Type {
  HIGH_CARD,
  PAIR,
  TWO_PAIR,
  THREE_OAK,
  FULL_HOUSE,
  FOUR_OAK,
  FIVE_OAK
};

const map<string, Type> handTypes{
    {"11111", HIGH_CARD},  //
    {"1112", PAIR},        //
    {"122", TWO_PAIR},     //
    {"113", THREE_OAK},    //
    {"23", FULL_HOUSE},    //
    {"14", FOUR_OAK},      //
    {"5", FIVE_OAK},       //
};

const map<char, int> cardValues{
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3},  {'6', 4},  {'7', 5},  {'8', 6},
    {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12},
};
const map<char, int> cardValuesPt2{
    {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3},  {'5', 4},  {'6', 5}, {'7', 6},
    {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12}};

struct Hand {
  string cards;
  Type type;
  unsigned int bid;
};

Type getType(string& handStr, bool jokers = false) {
  unordered_map<char, int> cards;

  for (char c : handStr) cards[c]++;

  string nStr = "";

  for (auto& cardCount : cards) nStr += string() + to_string(cardCount.second);

  sort(nStr.begin(), nStr.end());

  return handTypes.at(nStr);
}

struct {
  bool operator()(Hand a, Hand b) const {
    if (a.type != b.type) return a.type < b.type;

    for (int i = 0; i < a.cards.size(); i++) {
      if (a.cards[i] != b.cards[i])
        return cardValues.at(a.cards[i]) < cardValues.at(b.cards[i]);
    }
  }
} compareHands;

void solve() {
  ull result_1 = 0;
  ull result_2 = 0;

  vector<Hand> hands(1000);

  ifstream inputFile("./input");

  if (!inputFile) {
    cout << "Couldn't read file: " << strerror(errno) << endl;
    exit(-1);
  }

  string line = "";

  int handsIdx = 0;
  while (getline(inputFile, line)) {
    string handStr;
    unsigned int bid;

    stringstream ss(line);

    ss >> handStr >> bid;

    hands[handsIdx] = {handStr, getType(handStr), bid};
    handsIdx++;

    // cout << handStr << bid << endl;
  }

  sort(hands.begin(), hands.end(), compareHands);

  inputFile.close();

  for (int i = 0; i < hands.size(); i++) {
    result_1 += hands[i].bid * (i + 1);
  }

  cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 7" << endl;

  solve();  //
            //
}