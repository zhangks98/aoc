#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

struct RangeMap {
  long src_start = 0;
  long dst_start = 0;
  long count = 0;
};

struct Range {
  long start;
  long count;
};

std::ostream &operator<<(std::ostream &os, const RangeMap &value) {
  // os << "(src_start: " << value.src_start << ", dst_start: " <<
  // value.dst_start
  //    << ", range: " << value.count << ")\n";
  os << "(src: " << value.src_start << "..."
     << value.src_start + value.count - 1 << ", dst: " << value.dst_start
     << "..." << value.dst_start + value.count - 1 << ")\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Range &value) {
  // os << "(start: " << value.start << ", count: " << value.count << ")";
  os << "(" << value.start << "..." << value.start + value.count - 1 << ")";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &value) {
  for (const auto &elem : value) {
    std::cout << elem << ' ';
  }
  return os;
}

// Assumes sorted range_map by src.
std::vector<long> ApplyRangeMap(const std::vector<RangeMap> &range_map,
                                std::vector<long> &input) {
  int rp = 0;
  int ip = 0;
  std::vector<long> output;
  std::sort(input.begin(), input.end());
  while (ip < input.size() && rp < range_map.size()) {
    while (ip < input.size() && range_map[rp].src_start > input[ip]) {
      output.push_back(input[ip++]);
    }

    while (ip < input.size() && range_map[rp].src_start <= input[ip] &&
           input[ip] < range_map[rp].src_start + range_map[rp].count) {
      output.push_back(range_map[rp].dst_start + input[ip++] -
                       range_map[rp].src_start);
    }
    rp++;
  }

  while (ip < input.size()) {
    output.push_back(input[ip++]);
  }
  return output;
}

// Assumes sorted range_map by src.
std::vector<Range> ApplyRangeMap(const std::vector<RangeMap> &range_map,
                                 std::vector<Range> input) {
  std::vector<Range> output;
  for (const auto &[src_start, dst_start, count] : range_map) {
    std::vector<Range> next_round;
    for (const auto &ir : input) {
      if (ir.start + ir.count - 1 < src_start ||
          ir.start > src_start + count - 1) {
        next_round.push_back(ir);
      } else if (ir.start < src_start) {
        next_round.push_back({ir.start, src_start - ir.start});
        if (ir.start + ir.count - 1 <= src_start + count - 1) {
          output.push_back({dst_start, ir.start + ir.count - src_start});
        } else {
          output.push_back({dst_start, count});
          next_round.push_back(
              {src_start + count, ir.start + ir.count - src_start - count});
        }
      } else {
        if (ir.start + ir.count - 1 <= src_start + count - 1) {
          output.push_back({dst_start + ir.start - src_start, ir.count});
        } else {
          output.push_back(
              {dst_start + ir.start - src_start, src_start + count - ir.start});
          next_round.push_back(
              {src_start + count, ir.start + ir.count - src_start - count});
        }
      }
    }
    input.swap(next_round);
  }
  output.insert(output.end(), input.begin(), input.end());
  return output;
}

std::vector<RangeMap> ParseRangeMap() {
  std::string maps_str;
  std::vector<RangeMap> maps;
  while (std::getline(std::cin, maps_str)) {
    if (maps_str.empty()) {
      break;
    }
    long src_start, dst_start, range;
    std::stringstream maps_ss(maps_str);
    maps_ss >> dst_start >> src_start >> range;
    maps.push_back({src_start, dst_start, range});
  }
  std::sort(maps.begin(), maps.end(), [](const RangeMap &a, const RangeMap &b) {
    return a.src_start < b.src_start;
  });
  return maps;
}

int main() {
  std::vector<Range> seeds;
  std::string seeds_str;
  std::getline(std::cin, seeds_str);
  int colon_pos = seeds_str.find(':');
  std::stringstream seeds_ss(seeds_str.substr(colon_pos + 2));
  long seed;
  long seed_range;
  while (seeds_ss >> seed >> seed_range) {
    seeds.push_back({seed, seed_range});
  }

  std::string tmp;
  std::getline(std::cin, tmp);

  // std::vector<long> input = seeds;
  std::vector<Range> input = seeds;
  for (int stage = 1; stage <= 7; stage++) {
    std::getline(std::cin, tmp);
    auto map = ParseRangeMap();
    // std::cout << "\nStage " << stage << " map:\n " << map;
    std::vector<Range> output = ApplyRangeMap(map, input);
    // std::cout << "Stage " << stage << " output: " << output << "\n";
    input.swap(output);
  }
  std::cout << *std::min_element(input.begin(), input.end(),
                                 [](const Range &a, const Range &b) {
                                   return a.start < b.start;
                                 })
            << std::endl;

  return 0;
}
