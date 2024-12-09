#include <iostream>
#include <string>
#include <utility>
#include <vector>

void part1(std::vector<int>& disk_map) {
  int i = 0, j = disk_map.size() - 1;
  while (i < j) {
    while (i < disk_map.size() && disk_map[i] >= 0) {
      i++;
    }
    while (j > i && disk_map[j] < 0) {
      j--;
    }
    while (i < j && disk_map[i] < 0 && disk_map[j] >= 0) {
      std::swap(disk_map[i], disk_map[j]);
      i++;
      j--;
    }
  }

  long long sum = 0;
  for (int pos = 0; pos < disk_map.size(); pos++) {
    if (disk_map[pos] >= 0) {
      sum += pos * disk_map[pos];
    }
  }
  std::cout << sum << "\n";
}

long long Checksum(const std::vector<int>& blocks, const std::vector<int>& holes,
             const std::vector<std::vector<int>>& filled_holes,
             const std::vector<bool>& block_moved) {
  long long sum = 0;
  int pos = 0;
  int id = 0, j = 0;
  while (id < blocks.size() && j < holes.size()) {
    for (int k = 0; k < blocks[id]; k++) {
      if (!block_moved[id]) {
        sum += pos * id;
      }
      pos++;
    }
    id++;

    for (int k = 0; k < holes[j]; k++) {
      if (k < filled_holes[j].size()) {
        sum += pos * filled_holes[j][k];
      }
      pos++;
    }
    j++;
  }

  while (id < blocks.size()) {
    for (int k = 0; k < blocks[id]; k++) {
      if (!block_moved[id]) {
        sum += pos * id;
      }
      pos++;
    }
    id++;

    for (int k = 0; k < holes[j]; k++) {
      if (k < filled_holes[j].size()) {
        sum += pos * filled_holes[j][k];
      }
      pos++;
    }
    j++;
  }
  return sum;
}

void part2(const std::vector<int>& blocks, const std::vector<int>& holes) {
  std::vector<std::vector<int>> filled_holes(holes.size());
  std::vector<int> holes_left = holes;
  std::vector<bool> block_moved(blocks.size(), false);

  for (int id = blocks.size() - 1; id >= 0; id--) {
    for (int i = 0; i < id; i++) {
      if (blocks[id] <= holes_left[i]) {
        block_moved[id] = true;
        holes_left[i] -= blocks[id];
        for (int j = 0; j < blocks[id]; j++) {
          filled_holes[i].push_back(id);
        }
        break;
      }
    }
  }

  std::cout << Checksum(blocks, holes, filled_holes, block_moved) << '\n';
}

int main() {
  std::string input;
  std::cin >> input;

  std::vector<int> disk_map;
  std::vector<int> blocks;
  std::vector<int> holes;
  int id = 0;
  for (int i = 0; i < input.size(); i++) {
    int size = input[i] - '0';
    if (i % 2 == 0) {
      blocks.push_back(size);
      while (size > 0) {
        disk_map.push_back(id);
        size--;
      }
      id++;
    } else {
      holes.push_back(size);
      while (size > 0) {
        disk_map.push_back(-1);
        size--;
      }
    }
  }
  // part1(disk_map);
  part2(blocks, holes);
}
