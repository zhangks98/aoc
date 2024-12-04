#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &value) {
  os << "[ ";
  for (const auto &elem : value) {
    os << elem << ' ';
  }
  os << "]";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::multiset<T> &value) {
  for (const auto &elem : value) {
    os << elem << ' ';
  }
  return os;
}

/**
  Five of a kind, where all five cards have the same label: AAAAA
Four of a kind, where four cards have the same label and one card has a
different label: AA8AA Full house, where three cards have the same label, and
the remaining two cards share a different label: 23332 Three of a kind, where
three cards have the same label, and the remaining two cards are each different
from any other card in the hand: TTT98 Two pair, where two cards share one
label, two other cards share a second label, and the remaining card has a third
label: 23432 One pair, where two cards share one label, and the other three
cards have a different label from the pair and each other: A23A4 High card,
where all cards' labels are distinct: 23456
 */
// enum HandType {
//   HighCard,
//   OnePair,
//   TwoPair,
//   ThreeKind,
//   FullHouse,
//   FourKind,
//   FiveKind,
// };

std::vector<std::vector<int>> Patterns{
    {1, 1, 1, 1, 1}, {1, 1, 1, 2}, {1, 2, 2}, {1, 1, 3}, {2, 3}, {1, 4}, {5},
};

// When one J is present, the maximum increase in hand type
std::vector<std::vector<int>> j_map = {
    {0, 1, 2, 3, 4, 5, 6}, {1, 3, 4, 5, 0, 6, 0}, {0, 3, 5, 0, 6, 0, 0},
    {0, 0, 0, 5, 6, 0, 0}, {0, 0, 0, 0, 0, 6, 0}, {0, 0, 0, 0, 0, 0, 6},
};

std::unordered_map<char, int> card_map({
    {'J', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'Q', 12},
    {'K', 13},
    {'A', 14},
});
// A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
// std::unordered_map<char, int> card_map({
//     {'2', 2},
//     {'3', 3},
//     {'4', 4},
//     {'5', 5},
//     {'6', 6},
//     {'7', 7},
//     {'8', 8},
//     {'9', 9},
//     {'T', 10},
//     {'J', 11},
//     {'Q', 12},
//     {'K', 13},
//     {'A', 14},
// });

struct Hand {
  int type;
  std::vector<int> cards{};
  int bid;

  bool operator<(const Hand &other) {
    if (type < other.type) {
      return true;
    }
    if (type == other.type) {
      return cards < other.cards;
    }
    return false;
  }
};

std::ostream &operator<<(std::ostream &os, const Hand &v) {
  os << "(type: " << v.type << ", cards: [" << v.cards << "], rank: " << v.bid
     << ")";
  return os;
}

Hand ParseHand(std::string_view hand_sv, int bid) {
  Hand hand;
  hand.bid = bid;
  std::multiset<char> cards;
  std::multiset<int> num_cards;
  int num_j = 0;
  for (char c : hand_sv) {
    hand.cards.push_back(card_map.at(c));
    cards.insert(c);
    if (c == 'J') {
      num_j++;
    }
  }

  for (auto it = cards.begin(); it != cards.end();
       it = cards.upper_bound(*it)) {
    num_cards.insert(cards.count(*it));
  }

  for (int i = 0; i < Patterns.size(); i++) {
    if (std::equal(Patterns[i].begin(), Patterns[i].end(), num_cards.begin(),
                   num_cards.end())) {
      hand.type = i;
      break;
    }
  }

  if (num_j > 0) {
    hand.type = j_map[num_j][hand.type];
  }

  return hand;
}

int main() {
  std::vector<Hand> hands;
  std::string hand_str;
  int bid;

  std::vector<std::vector<int>> delta_map;

  while (std::cin >> hand_str >> bid) {
    hands.push_back(ParseHand(hand_str, bid));
  }
  std::sort(hands.begin(), hands.end());

  int sum = 0;
  for (int i = 0; i < hands.size(); i++) {
    sum += (i + 1) * hands[i].bid;
  }
  // std::cout << hands << "\n";
  std::cout << sum << "\n";

  return 0;
}
