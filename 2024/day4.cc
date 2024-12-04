#include <iostream>
#include <string>
#include <utility>
#include <vector>

const std::vector<std::pair<int, int>> dir{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                           {0, 1},   {1, -1}, {1, 0},  {1, 1}};
const std::string word = "XMAS";

void find(const std::vector<std::string>& puzzle, int di, int dj, int i, int j,
          int depth, int& sum) {
  int n = puzzle.size();
  int m = puzzle[0].size();

  if (i < 0 || i >= n || j < 0 || j >= m) {
    return;
  }

  if (puzzle[i][j] == word[depth]) {
    if (depth == word.size() - 1) {
      sum++;
      return;
    }
    find(puzzle, di, dj, i + di, j + dj, depth + 1, sum);
  }
}

void part1(const std::vector<std::string>& puzzle) {
  int sum = 0;
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle[i].size(); j++) {
      for (auto [di, dj] : dir) {
        find(puzzle, di, dj, i, j, 0, sum);
      }
    }
  }
  std::cout << sum << "\n";
}

const std::vector<std::pair<int, int>> clockwise{
    {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
bool IsValid(const std::vector<std::string>& puzzle, int i, int j) {
  int n = puzzle.size();
  int m = puzzle[0].size();
  std::vector<char> x;
  for (auto [di, dj] : clockwise) {
    int ii = i + di;
    int jj = j + dj;
    if (ii < 0 || ii >= n || jj < 0 || jj >= m) {
      return false;
    }
    x.push_back(puzzle[ii][jj]);
  }

  if (!(x[0] == x[1] && x[2] == x[3]) && !(x[0] == x[3] && x[1] == x[2])) {
    return false;
  }
  return (x[0] == 'M' && x[2] == 'S') || (x[0] == 'S' && x[2] == 'M');
}

void part2(const std::vector<std::string>& puzzle) {
  int sum = 0;
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle[i].size(); j++) {
      if (puzzle[i][j] == 'A' && IsValid(puzzle, i, j)) {
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

  part2(puzzle);
}
