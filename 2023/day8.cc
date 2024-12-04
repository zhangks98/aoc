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

static constexpr LazyRE2 kMapLine = {
    R"(([A-Z0-9]+) = \(([A-Z0-9]+), ([A-Z0-9]+)\))"};

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
struct Node {
  std::string label;
  Node *left = nullptr;
  Node *right = nullptr;
};

std::ostream &operator<<(std::ostream &os, const Node &v) {
  os << "(Node: " << v.label << ", Left: " << (v.left ? v.left->label : "null")
     << ", Right: " << (v.right ? v.right->label : "null") << ")";
  return os;
}

std::unordered_map<std::string, std::unique_ptr<Node>> node_map;
Node *GetNode(const std::string &label) {
  std::unique_ptr<Node> &node = node_map[label];
  if (node == nullptr) {
    node = std::make_unique<Node>();
    node->label = label;
  }
  return node.get();
}

int GetSteps(std::string_view dirs) {
  auto it = dirs.begin();
  Node *curr = GetNode("AAA");
  int steps = 0;

  while (curr->label != "ZZZ") {
    if (*it == 'L') {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
    steps++;
    if (++it == dirs.end()) {
      it = dirs.begin();
    }
  }
  return steps;
}

int GetSteps(std::string_view dirs, Node *curr) {
  auto it = dirs.begin();
  int steps = 0;

  while (curr->label[2] != 'Z') {
    if (*it == 'L') {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
    steps++;
    if (++it == dirs.end()) {
      it = dirs.begin();
    }
  }
  return steps;
}

long GetSteps2(std::string_view dirs) {
  std::vector<int> steps;
  for (auto &[label, node] : node_map) {
    if (label[2] == 'A') {
      steps.push_back(GetSteps(dirs, node.get()));
    }
  }
  long total_step = 1;
  for (const int s : steps) {
    total_step = std::lcm(total_step, s);
  }
  return total_step;
}

int main() {
  std::string dirs;
  std::cin >> dirs;

  std::string line;
  std::getline(std::cin, line);
  std::getline(std::cin, line);

  while (std::getline(std::cin, line)) {
    std::string label, left, right;
    RE2::FullMatch(line, *kMapLine, &label, &left, &right);
    Node *node = GetNode(label);
    node->left = GetNode(left);
    node->right = GetNode(right);
  }

  // for (const auto& [unused, node]: node_map) {
  //   std::cout << *node << "\n";
  // }

  std::cout << GetSteps2(dirs) << std::endl;
  return 0;
}
