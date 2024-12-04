#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

void part1(std::vector<int>&left, std::vector<int>&right) {
  std::sort(left.begin(), left.end());
  std::sort(right.begin(),right.end());

  int sum = 0;
  for (int i = 0; i < left.size(); i++) {
    sum += std::abs(left[i] - right[i]);
  }
  std::cout << '\n' << sum << '\n';
}

void part2(std::vector<int>&left, std::vector<int>&right) {
  std::unordered_map<int, int> freq;
  for (const int loc : right) {
    freq[loc] += 1;
  }

  int sum = 0;
  for (const int loc: left) {
    sum += loc * freq[loc];
  }
  std::cout << '\n' << sum << '\n';
}

int main() {
  int l, r;
  std::vector<int> left, right;
  while (std::cin >> l >> r) {
    left.push_back(l);
    right.push_back(r);
  }

  part2(left, right);

  return 0;
}
