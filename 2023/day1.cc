#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

std::unordered_map<std::string_view, int> d3_map = {
    {"one", 1},
    {"two", 2},
    {"six", 6},
};

std::unordered_map<std::string_view, int> d4_map = {
    {"four", 4},
    {"five", 5},
    {"nine", 9},
};

std::unordered_map<std::string_view, int> d5_map = {
    {"three", 3},
    {"seven", 7},
    {"eight", 8},
};

int get_digit_forward(std::string_view s) {
  for (int i = 0; i < s.size(); i++) {
    if (std::isdigit(s[i])) {
      return s[i] - '0';
    }
    if (i + 3 < s.size()) {
      auto it = d3_map.find(s.substr(i, 3));
      if (it != d3_map.end()) {
        return it->second;
      }
    }
    if (i + 4 < s.size()) {
      auto it = d4_map.find(s.substr(i, 4));
      if (it != d4_map.end()) {
        return it->second;
      }
    }
    if (i + 5 < s.size()) {
      auto it = d5_map.find(s.substr(i, 5));
      if (it != d5_map.end()) {
        return it->second;
      }
    }
  }
  throw std::invalid_argument("no digit found");
}

int get_digit_backward(std::string_view s) {
  for (int i = s.size() - 1; i >= 0; i--) {
    if (std::isdigit(s[i])) {
      return s[i] - '0';
    }
    if (i >= 3) {
      auto it = d3_map.find(s.substr(i - 2, 3));
      if (it != d3_map.end()) {
        return it->second;
      }
    }
    if (i >= 4) {
      auto it = d4_map.find(s.substr(i - 3, 4));
      if (it != d4_map.end()) {
        return it->second;
      }
    }
    if (i >= 5) {
      auto it = d5_map.find(s.substr(i - 4, 5));
      if (it != d5_map.end()) {
        return it->second;
      }
    }
  }
  throw std::invalid_argument("no digit found");
}
int main() {
  int sum = 0;
  std::string s;

  while (std::cin >> s) {
    int digit_forward = get_digit_forward(s);
    int digit_backward = get_digit_backward(s);
    int number = digit_forward * 10 + digit_backward;
    sum += number;
  }
  std::cout << '\n' << sum << '\n';

  return 0;
}
