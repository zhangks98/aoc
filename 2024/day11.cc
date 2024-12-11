#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<int64_t> arrange1(std::vector<int64_t>& stones) {
  std::vector<int64_t> new_stones;
  for (const auto s : stones) {
    int num_digits = std::to_string(s).size();
    if (s == 0) {
      new_stones.push_back(1);
    } else if (num_digits % 2 == 0) {
      long long div = std::pow(10, num_digits / 2);
      new_stones.push_back(s / div);
      new_stones.push_back(s % div);
    } else {
      new_stones.push_back(s * 2024);
    }
  }
  return new_stones;
}

void part1(const std::vector<int64_t>& stones) {
  std::vector<int64_t> new_stones = stones;
  for (int i = 0; i < 25; i++) {
    new_stones = arrange1(new_stones);
  }
  std::cout << new_stones.size() << "\n";
}

int64_t arrange2(
    int64_t s, int blinks_left,
    std::unordered_map<int64_t, std::unordered_map<int64_t, int64_t>>& dp) {
  if (blinks_left == 0) {
    return 1;
  }
  auto it = dp[s].find(blinks_left);
  if (it != dp[s].end()) {
    return it->second;
  }

  int64_t count = 0;
  int64_t num_digits = std::to_string(s).size();
  if (s == 0) {
    count = arrange2(1, blinks_left - 1, dp);
  } else if (num_digits % 2 == 0) {
    int64_t div = std::pow(10, num_digits / 2);
    count = arrange2(s / div, blinks_left - 1, dp) + arrange2(s % div, blinks_left - 1, dp);
  } else {
    count = arrange2(s * 2024, blinks_left - 1, dp);
  }
  dp[s][blinks_left] = count;
  return count;
}

void part2(const std::vector<int64_t>& stones) {
  int64_t count = 0;
  std::unordered_map<int64_t, std::unordered_map<int64_t, int64_t>> dp;
  for (const auto s : stones) {
    count += arrange2(s, 75, dp);
  }
  std::cout << count << '\n';
}

int main() {
  std::vector<int64_t> stones;
  int s;
  while (std::cin >> s) {
    stones.push_back(s);
  }

  part2(stones);
}
