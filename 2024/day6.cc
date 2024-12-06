#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

void GetStartingPos(const std::vector<std::string>& puzzle, int& i, int& j) {
  int n = puzzle.size();
  int m = puzzle[0].size();

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      if (puzzle[r][c] == '^') {
        i = r;
        j = c;
        return;
      }
    }
  }
}

std::vector<std::pair<int, int>> dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
void part1(std::vector<std::string> puzzle) {
  int n = puzzle.size();
  int m = puzzle[0].size();

  int i = 0, j = 0;
  GetStartingPos(puzzle, i, j);
  int d = 0;

  while (i >= 0 && i < n && j >= 0 && j < m) {
    puzzle[i][j] = 'X';
    auto [di, dj] = dirs[d];
    int ii = i + di, jj = j + dj;

    if (ii >= 0 && ii < n && jj >= 0 && jj < m && puzzle[ii][jj] == '#') {
      d = (d + 1) % 4;
      continue;
    }
    i = ii;
    j = jj;
  }

  int sum = 0;
  for (const auto& row : puzzle) {
    for (const auto& pos : row) {
      if (pos == 'X') {
        sum++;
      }
    }
  }
  std::cout << sum << "\n";
}

bool HasLoop(const std::vector<std::string>& puzzle, int i, int j) {
  int n = puzzle.size();
  int m = puzzle[0].size();
  int d = 0;
  std::set<std::tuple<int, int, int>> visited;
  while (i >= 0 && i < n && j >= 0 && j < m) {
    auto [di, dj] = dirs[d];
    int ii = i + di, jj = j + dj;

    if (ii >= 0 && ii < n && jj >= 0 && jj < m && puzzle[ii][jj] == '#') {
      d = (d + 1) % 4;
      auto [it, inserted] = visited.insert({ii, jj, d});
      if (!inserted) {
        return true;
      }
      continue;
    }
    i = ii;
    j = jj;
  }

  return false;
}

void part2(const std::vector<std::string>& puzzle) {
  int i = 0, j = 0;
  GetStartingPos(puzzle, i, j);

  int n = puzzle.size();
  int m = puzzle[0].size();

  int sum = 0;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      if (puzzle[r][c] == '.') {
        std::vector<std::string> new_puzzle = puzzle;
        new_puzzle[r][c] = '#';
        if (HasLoop(new_puzzle, i, j)) {
          sum++;
        }
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

  part2(puzzle);
}
