#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void FindAntinodes(const std::vector<std::pair<int, int>>& pos,
                   std::vector<std::vector<bool>>& antinodes) {
  int n = antinodes.size();
  int m = antinodes[0].size();

  auto IsInMap = [=](int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
  };

  for (int i = 0; i < pos.size(); i++) {
    for (int j = i + 1; j < pos.size(); j++) {
      auto [i1, j1] = pos[i];
      auto [i2, j2] = pos[j];
      int di = i2 - i1;
      int dj = j2 - j1;

      int a1i = i1 - di;
      int a1j = j1 - dj;
      if (IsInMap(a1i, a1j)) {
        antinodes[a1i][a1j] = true;
      }

      int a2i = i2 + di;
      int a2j = j2 + dj;
      if (IsInMap(a2i, a2j)) {
        antinodes[a2i][a2j] = true;
      }
    }
  }
}

void FindAntinodes2(const std::vector<std::pair<int, int>>& pos,
                   std::vector<std::vector<bool>>& antinodes) {
  int n = antinodes.size();
  int m = antinodes[0].size();

  auto IsInMap = [=](int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
  };

  for (int i = 0; i < pos.size(); i++) {
    for (int j = i + 1; j < pos.size(); j++) {
      auto [i1, j1] = pos[i];
      auto [i2, j2] = pos[j];

      int di = i2 - i1;
      int dj = j2 - j1;
      int gcd = std::gcd(di, dj);
      di /= gcd;
      dj /= gcd;
      int a1i = i1;
      int a1j = j1;
      while (IsInMap(a1i, a1j)) {
        antinodes[a1i][a1j] = true;
        a1i -= di;
        a1j -= dj;
      }

      int a2i = i2;
      int a2j = j2;
      while (IsInMap(a2i, a2j)) {
        antinodes[a2i][a2j] = true;
        a2i += di;
        a2j += dj;
      }
    }
  }
}

void solve(const std::vector<std::string>& puzzle) {
  int n = puzzle.size();
  int m = puzzle[0].size();
  std::vector<std::vector<bool>> antinodes(n, std::vector<bool>(m, false));

  std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char pos = puzzle[i][j];
      if (pos != '.') {
        antennas[pos].push_back({i, j});
      }
    }
  }

  for (const auto& [_not_used, v] : antennas) {
    // FindAntinodes(v, antinodes);
    FindAntinodes2(v, antinodes);
  }

  int sum = 0;
  for (const auto& row : antinodes) {
    for (const bool node : row) {
      if (node) {
        sum++;
      }
    }
  }

  std::cout << sum << "\n";
}

int main() {
  std::string line;

  std::vector<std::string> puzzle;
  while (std::getline(std::cin, line)) {
    puzzle.push_back(line);
  }

  solve(puzzle);
}
