#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool IsBad(int curr, int prev, bool is_increasing) {
  int diff = curr - prev;
  const bool not_monotonic = is_increasing != (diff > 0);
  int abs_diff = std::abs(diff);
  const bool large_diff = (abs_diff < 1) || (abs_diff > 3);
  return not_monotonic || large_diff;
}

bool IsSafe(const std::vector<int>& level) {
  bool is_increasing = level[1] > level[0];
  for (int i = 0; i < level.size() - 1; i++) {
    if (IsBad(level[i + 1], level[i], is_increasing)) {
      return false;
    }
  }
  return true;
}

bool IsSafe2(const std::vector<int>& level) {
  if (IsSafe(level)) {
    return true;
  }
  for (int i = 0; i < level.size(); i++) {
    std::vector<int> level_copy = level;
    level_copy.erase(level_copy.begin() + i);
    if (IsSafe(level_copy)) {
      return true;
    }
  }
  return false;
}

int main() {
  std::string line;
  int sum = 0;
  while (getline(std::cin, line)) {
    std::stringstream ss(line);

    std::vector<int> level;
    int data;
    while (ss >> data) {
      level.push_back(data);
    }
    sum += IsSafe2(level);
  }
  std::cout << sum << '\n';
  return 0;
}
