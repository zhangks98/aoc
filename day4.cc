#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

int GetNumCards(const std::vector<int> &matches) {
  std::vector<int> num_cards(matches.size(), 1);
  for (int i = 0; i < matches.size(); i++) {
    int match = matches[i];
    for (int j = 1; j <= match; j++) {
      if (i + j < num_cards.size()) {
        num_cards[i + j] += num_cards[i];
      }
    }
  }
  return std::accumulate(num_cards.begin(), num_cards.end(), 0);
}

int main() {
  std::string game;
  // int sum = 0;
  std::vector<int> matches;
  while (getline(std::cin, game)) {
    int colon_pos = game.find(':');
    int divider_pos = game.find('|');

    std::stringstream winning_ss(
        game.substr(colon_pos + 2, divider_pos - colon_pos - 3));
    std::unordered_set<int> winning_set;
    int winning_num;
    while (winning_ss >> winning_num) {
      winning_set.insert(winning_num);
    }

    std::stringstream card_ss(game.substr(divider_pos + 2));
    int num_match = 0;
    int card_num;
    while (card_ss >> card_num) {
      if (winning_set.find(card_num) != winning_set.end()) {
        num_match++;
      }
    }
    matches.push_back(num_match);
    // if (num_match > 0) {
    //   sum += 1 << (num_match - 1);
    // }
  }
  std::cout << GetNumCards(matches) << '\n';
  return 0;
}
