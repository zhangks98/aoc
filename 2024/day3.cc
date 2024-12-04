#include <re2/re2.h>

#include <cstdlib>
#include <iostream>
#include <string>

RE2 re(R"(mul\((\d+),(\d+)\))");
RE2 re_2(R"((.*?)(do\(\)|don't\(\)))");
int Compute(absl::string_view command) {
  int a, b;
  int sum = 0;
  while (RE2::FindAndConsume(&command, re, &a, &b)) {
    sum += a * b;
  }
  return sum;
}

int main() {
  std::string line, lines;
  int sum = 0;
  while (getline(std::cin, line)) {
    lines += line;
  }

  absl::string_view sv(lines);

  std::string command, state;
  std::string prev_state = "do()";
  absl::string_view last;
  while (RE2::FindAndConsume(&sv, re_2, &command,
                             &state)) {
    if (prev_state == "do()") {
      sum += Compute(command);
    }
    prev_state = state;
    last = sv;
  }

  if (prev_state == "do()") {
    sum += Compute(last);
  }
  std::cout << sum << '\n';
  return 0;
}
