#include <re2/re2.h>

#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
#include <memory>
#include <numeric>
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

int Extract(std::vector<int> vals) {
  int s = 0;
  while (!std::all_of(vals.begin(), vals.end(), [](int v) { return v == 0; })) {
    s += *vals.rbegin();
    std::vector<int> next;
    for (int i = 1; i < vals.size(); i++) {
      next.push_back(vals[i] - vals[i - 1]);
    }
    vals.swap(next);
  }
  return s;
}

int ExtractFirst(std::vector<int> vals) {
  std::vector<int> first;
  while (!std::all_of(vals.begin(), vals.end(), [](int v) { return v == 0; })) {
    first.push_back(*vals.begin());
    std::vector<int> next;
    for (int i = 1; i < vals.size(); i++) {
      next.push_back(vals[i] - vals[i - 1]);
    }
    vals.swap(next);
  }
  int s = 0;
  for (auto it = first.rbegin(); it != first.rend(); it++) {
    s = *it - s;
  }
  return s;
}
int main() {
  std::string line;
  int sum = 0;
  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    int v;
    std::vector<int> oasis;
    while (ss >> v) {
      oasis.push_back(v);
    }
    sum += ExtractFirst(oasis);
  }

  std::cout << sum << std::endl;
  return 0;
}
