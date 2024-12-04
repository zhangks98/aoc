#include <re2/re2.h>

#include <charconv>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

constexpr int kMaxRed = 12;
constexpr int kMaxGreen = 13;
constexpr int kMaxBlue = 14;

static constexpr LazyRE2 kRed = {R"((\d+) red,?)"};
static constexpr LazyRE2 kGreen = {R"((\d+) green,?)"};
static constexpr LazyRE2 kBlue = {R"((\d+) blue,?)"};

struct Draw {
  int red = 0;
  int green = 0;
  int blue = 0;
};

std::ostream& operator<<(std::ostream& os, const Draw& value) {
  os << "(red: " << value.red << ", green: " << value.green
     << ", blue: " << value.blue << ")\n";
  return os;
}

// Parse individual draw.
Draw ParseDraw(string_view sv) {
  Draw draw;
  int count;
  if (RE2::PartialMatch(sv, *kRed, &count)) {
    draw.red = count;
  }
  if (RE2::PartialMatch(sv, *kGreen, &count)) {
    draw.green = count;
  }
  if (RE2::PartialMatch(sv, *kBlue, &count)) {
    draw.blue = count;
  }

  return draw;
}

bool IsPossibleDraw(const Draw& draw) {
  return draw.red <= kMaxRed && draw.green <= kMaxGreen &&
         draw.blue <= kMaxBlue;
}

bool IsPossibleGame(string_view draws) {
  int draw_end;
  while (draw_end = draws.find(';'), draw_end != string_view::npos) {
    Draw draw = ParseDraw(draws.substr(0, draw_end));
    if (!IsPossibleDraw(draw)) {
      return false;
    }
    draws = draws.substr(draw_end + 2);
  }
  return IsPossibleDraw(ParseDraw(draws));
}

int GamePower(string_view draws) {
  int draw_end;
  int min_red = 0, min_green = 0, min_blue = 0;
  while (draw_end = draws.find(';'), draw_end != string_view::npos) {
    Draw draw = ParseDraw(draws.substr(0, draw_end));
    min_red = max(min_red, draw.red);
    min_green = max(min_green, draw.green);
    min_blue = max(min_blue, draw.blue);
    draws = draws.substr(draw_end + 2);
  }
  Draw draw = ParseDraw(draws);
  return max(min_red, draw.red) * max(min_green, draw.green) *
         max(min_blue, draw.blue);
}

int main() {
  string game;
  int sum = 0;
  while (getline(cin, game)) {
    string_view sv(game);
    // Parse game id.
    int colon_pos = sv.find(':');
    int game_id;
    from_chars(sv.data() + 5, sv.data() + colon_pos, game_id);

    string_view draws = sv.substr(colon_pos + 2);
    // if (IsPossibleGame(draws)) {
    // sum += game_id;
    //}
    sum += GamePower(draws);
  }
  cout << sum << '\n';
  return 0;
}
