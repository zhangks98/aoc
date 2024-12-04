#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

bool IsSpecial(char c) { return !std::isdigit(c) && c != '.'; }

int GetPartNumber(const std::vector<std::string> &engine) {
  int nrows = engine.size();
  int ncols = engine[0].size();
  int sum = 0;
  std::vector<std::pair<int, int>> delta = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                            {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  for (int i = 0; i < nrows; i++) {
    std::string_view row(engine[i]);
    int j = 0;
    while (j < ncols) {
      while (j < ncols && !std::isdigit(row[j])) {
        j++;
      }

      int num_begin = j;
      bool is_part = false;
      while (j < ncols && std::isdigit(row[j])) {
        for (const auto &[di, dj] : delta) {
          if (i + di >= 0 && i + di < nrows && j + dj >= 0 && j + dj < ncols &&
              IsSpecial(engine[i + di][j + dj])) {
            is_part = true;
          }
        }
        j++;
      }

      if (is_part) {
        int part_num;
        std::from_chars(row.data() + num_begin, row.data() + j, part_num);
        sum += part_num;
      }
    }
  }

  return sum;
}

int GetNumberNear(std::string_view row, int j) {
  int begin = j;
  while (begin >= 0 && std::isdigit(row[begin])) {
    begin--;
  }
  begin++;

  int end = j;
  while (end <= row.size() && std::isdigit(row[end])) {
    end++;
  }

  int num;
  std::from_chars(row.data() + begin, row.data() + end, num);
  return num;
}

void AdjRow(int i, int j, const std::vector<std::string> &engine,
            std::vector<std::pair<int, int>> &adj) {
  std::string_view row = engine[i];
  if (std::isdigit(row[j])) {
    adj.push_back({i, j});
  } else {
    if (j > 0 && std::isdigit(row[j - 1])) {
      adj.push_back({i, j - 1});
    }
    if (j <= row.size() && std::isdigit(row[j + 1])) {
      adj.push_back({i, j + 1});
    }
  }
}

int GetGearRatio(const std::vector<std::string> &engine) {
  int nrows = engine.size();
  int ncols = engine[0].size();
  int sum = 0;
  std::vector<int> deltas = {-1, 0, 1};

  for (int i = 0; i < nrows; i++) {
    std::string_view row(engine[i]);
    int j = 0;
    while (j < ncols) {
      while (j < ncols && row[j] != '*') {
        j++;
      }
      if (j >= ncols) {
        break;
      }

      std::vector<std::pair<int, int>> adjs;
      for (const auto &di : deltas) {
        if (i + di >= 0 && i + di < nrows) {
          AdjRow(i + di, j, engine, adjs);
        }
      }

      if (adjs.size() == 2) {
        int ratio = 1;
        for (const auto &[x, y] : adjs) {
          ratio *= GetNumberNear(engine[x], y);
        }
        sum += ratio;
      }
      j++;
    }
  }

  return sum;
}
int main() {
  std::vector<std::string> engine;
  std::string line;
  while (std::getline(std::cin, line)) {
    engine.push_back(line);
  }
  std::cout << GetGearRatio(engine) << std::endl;
}
