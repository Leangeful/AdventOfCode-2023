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
const map<string, Type> handTypesPt2{
    {"1111", PAIR},      //
    {"111", THREE_OAK},  //
    {"11", FOUR_OAK},    //
    {"1", FIVE_OAK},     //
    {"112", THREE_OAK},  //
    {"12", FOUR_OAK},    //
    {"2", FIVE_OAK},     //
    {"22", FULL_HOUSE},  //
    {"13", FOUR_OAK},    //
    {"3", FIVE_OAK},     //
    {"4", FIVE_OAK},     //
    {"", FIVE_OAK},      //
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
  Type typeJoker;
  unsigned int bid;
};

struct {
  bool operator()(Hand a, Hand b) const {
    if (a.type != b.type) return a.type < b.type;

    for (int i = 0; i < a.cards.size(); i++) {
      if (a.cards[i] != b.cards[i])
        return cardValues.at(a.cards[i]) < cardValues.at(b.cards[i]);
    }
    return true;
  }
} compareHands;

struct {
  bool operator()(Hand a, Hand b) const {
    if (a.typeJoker != b.typeJoker) return a.typeJoker < b.typeJoker;

    for (int i = 0; i < a.cards.size(); i++) {
      if (a.cards[i] != b.cards[i])
        return cardValuesPt2.at(a.cards[i]) < cardValuesPt2.at(b.cards[i]);
    }
    return true;
  }
} compareHandsPt2;

void getTypes(Hand& hand) {
  unordered_map<char, int> cards;
  int jokerCount = 0;

  for (char c : hand.cards) {
    if (c == 'J')
      jokerCount++;
    else
      cards[c]++;
  }

  string noJokerCountStr = "";

  for (auto& cardCount : cards)
    noJokerCountStr += string() + to_string(cardCount.second);

  sort(noJokerCountStr.begin(), noJokerCountStr.end());

  if (jokerCount) {
    string countStr = string() + noJokerCountStr + to_string(jokerCount);
    sort(countStr.begin(), countStr.end());
    hand.typeJoker = handTypesPt2.at(noJokerCountStr);
    hand.type = handTypes.at(countStr);
  } else {
    hand.type = handTypes.at(noJokerCountStr);
    hand.typeJoker = hand.type;
  }
}

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

    Hand hand;

    hand.cards = handStr;
    hand.bid = bid;

    getTypes(hand);

    hands[handsIdx] = hand;
    handsIdx++;
  }
  inputFile.close();

  sort(hands.begin(), hands.end(), compareHands);

  for (int i = 0; i < hands.size(); i++) {
    result_1 += hands[i].bid * (i + 1);
  }

  sort(hands.begin(), hands.end(), compareHandsPt2);

  for (int i = 0; i < hands.size(); i++) {
    result_2 += hands[i].bid * (i + 1);
  }

  cout << result_1 << endl;
  cout << result_2 << endl;
}

int main() {
  cout << "Advent of Code 2023" << endl << "Day 7" << endl;

  solve();  // 246912307
            // 246894760
}