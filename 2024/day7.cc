#include <absl/strings/str_split.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool HasValidOps(const std::vector<int>& input, long long goal, int i,
                 long long sum) {
  if (i > input.size()) {
    return false;
  }

  if (i == input.size()) {
    return sum == goal;
  }

  return HasValidOps(input, goal, i + 1, sum + input[i]) ||
         HasValidOps(input, goal, i + 1, sum * input[i]);
}

bool HasValidOps2(const std::vector<int>& input, long long goal, int i,
                 long long sum) {
  if (i > input.size()) {
    return false;
  }

  if (i == input.size()) {
    return sum == goal;
  }
  
  int num_digits = std::to_string(input[i]).size();

  return HasValidOps2(input, goal, i + 1, sum + input[i]) ||
         HasValidOps2(input, goal, i + 1, sum * input[i]) ||
         HasValidOps2(input, goal, i + 1, sum * std::pow(10, num_digits) + input[i]);
}

int main() {
  std::string line;

  long long sum = 0;
  while (std::getline(std::cin, line)) {
    std::vector<std::string> v = absl::StrSplit(line, ':');
    long long goal = std::stoll(v[0]);
    std::istringstream buf(v[1]);
    std::vector<int> input;
    int val;
    while (buf >> val) {
      input.push_back(val);
    }

    if (HasValidOps2(input, goal, 1, input[0])) {
      sum += goal;
    }
  }
  std::cout << sum << "\n";
}
