#include <absl/container/flat_hash_set.h>
#include <absl/strings/str_split.h>

#include <iostream>
#include <string>
#include <utility>
#include <vector>

int Sort(std::vector<int>& v,
         const absl::flat_hash_set<std::pair<int, int>>& orders) {
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (orders.find({v[i], v[j]}) == orders.end()) {
        std::swap(v[i], v[j]);
      }
    }
  }
  return v[v.size() / 2];
}

int IsInOrder(const std::vector<int>& v,
              const absl::flat_hash_set<std::pair<int, int>>& orders) {
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (orders.find({v[i], v[j]}) == orders.end()) {
        return 0;
      }
    }
  }
  return v[v.size() / 2];
}

int main() {
  absl::flat_hash_set<std::pair<int, int>> orders;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    std::vector<std::string> v = absl::StrSplit(line, '|');
    orders.emplace(std::stoi(v[0]), std::stoi(v[1]));
  }

  int sum = 0;
  while (std::getline(std::cin, line)) {
    std::vector<std::string> input = absl::StrSplit(line, ',');
    std::vector<int> v;
    input.reserve(input.size());
    for (const auto& i : input) {
      v.push_back(std::stoi(i));
    }
    // sum += IsInOrder(v, orders);
    if (IsInOrder(v, orders) == 0) {
      sum += Sort(v, orders);
    }
  }

  std::cout << sum << "\n";
}
