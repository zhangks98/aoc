#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::vector<int> GetVector() {
  std::string tmp, line;
  std::getline(std::cin, line);
  std::stringstream ss(line);
  ss >> tmp;

  std::vector<int> vec;
  int x;
  while (ss >> x) {
    vec.push_back(x);
  }
  return vec;
}

int main() {
  /**
   * for given time t, start time s
   * dist = s * (t - s)
   **/
  // std::vector<int> time = GetVector();
  // std::vector<int> dist = GetVector();

  // int margin = 1;
  //   int winning = 0;
  //   for (int t = 0; t <= time[i]; t++) {
  //     if (t * (time[i] - t) > dist[i]) {
  //       winning++;
  //     }
  //   }
  //   margin *= winning;
  // }

  long time = 53916768;
  long dist = 250133010811025;
  long winning = 0;
  for (long t = 0; t <= time; t++) {
    if (t * (time - t) > dist) {
      winning++;
    }
  }

  std::cout << winning << std::endl;
}
