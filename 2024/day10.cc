#include <iostream>
#include <string>
#include <utility>
#include <vector>

void Print(const std::vector<std::vector<int>>& puzzle, int r, int c) {
  int n = puzzle.size();
  int m = puzzle[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == r && j == c) {
        std::cout << 'X';
      } else {
        std::cout << puzzle[i][j];
      }
    }
    std::cout << '\n';
  }
    std::cout << '\n';
}

const std::vector<std::pair<int, int>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void Find(const std::vector<std::vector<int>>& puzzle, int i, int j, int height,
          int& sum, std::vector<std::vector<bool>>& visited) {
  int n = puzzle.size();
  int m = puzzle[0].size();
  if (i < 0 || i >= n || j < 0 || j >= m || puzzle[i][j] != height) {
    return;
  }

  // For part 1.
  // if (visited[i][j]) {
  //   return;
  // }
  // visited[i][j] = true;

  if (height == 9) {
    sum++;
    return;
  }

  for (auto [di, dj] : dirs) {
    Find(puzzle, i + di, j + dj, height + 1, sum, visited);
  }
}

void part1(const std::vector<std::vector<int>>& puzzle) {
  int n = puzzle.size();
  int m = puzzle[0].size();

  int sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (puzzle[i][j] == 0) {
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
        Find(puzzle, i, j, 0, sum, visited);
      }
    }
  }
  std::cout << sum << '\n';
}

int main() {
  std::string line;
  std::vector<std::vector<int>> puzzle;

  while (std::getline(std::cin, line)) {
    std::vector<int> row;
    for (char c : line) {
      row.push_back(c - '0');
    }
    puzzle.push_back(row);
  }

  part1(puzzle);
}
