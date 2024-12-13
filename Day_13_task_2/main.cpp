#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint64_t;

struct game {
  valueType a_x;
  valueType a_y;
  valueType b_x;
  valueType b_y;
  valueType p_x;
  valueType p_y;
};
void parseGameString(const std::string &line, game &newGame);
void printData(const std::vector<game> &data);
valueType findBestGame(const game &game_);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<game> games;
  std::string line;
  while (std::getline(inputFS, line)) {
    if (line.empty()) {
      continue;
    }
    game newGame{};

    parseGameString(line, newGame);
    std::getline(inputFS, line);
    parseGameString(line, newGame);
    std::getline(inputFS, line);
    parseGameString(line, newGame);
    newGame.p_x += 10000000000000;
    newGame.p_y += 10000000000000;
    games.push_back(newGame);
  }
  inputFS.close();

  printData(games);

  valueType sum = 0;
  for (auto &game : games) {
    valueType bestGame = findBestGame(game);
    std::cout << "Best Game: " << bestGame << std::endl;
    sum += bestGame;
  }

  std::cout << "Sum: " << sum << std::endl;

  return 0;
}

void parseGameString(const std::string &line, game &newGame) {
  if (line.find("Button A:") != std::string::npos) {
    sscanf(line.c_str(), "Button A: X+%lu, Y+%lu", &(newGame.a_x),
           &(newGame.a_y));
  } else if (line.find("Button B:") != std::string::npos) {
    sscanf(line.c_str(), "Button B: X+%lu, Y+%lu", &(newGame.b_x),
           &(newGame.b_y));
  } else if (line.find("Prize:") != std::string::npos) {
    sscanf(line.c_str(), "Prize: X=%lu, Y=%lu", &(newGame.p_x), &(newGame.p_y));
  }
}

void printData(const std::vector<game> &data) {
  for (auto &row : data) {
    std::cout << " A X:+" << row.a_x;
    std::cout << " A Y:+" << row.a_y;
    std::cout << " B X:+" << row.b_x;
    std::cout << " B Y:+" << row.b_y;
    std::cout << " P X:+" << row.p_x;
    std::cout << " P Y:+" << row.p_y;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


valueType findBestGame(const game &game_) {
  valueType cheapestWin = 0;
  std::int64_t d = game_.a_x * game_.b_y - game_.a_y * game_.b_x;
  if (d == 0) {
    return 0;
  }
  std::int64_t da = game_.p_x * game_.b_y - game_.p_y * game_.b_x;
  std::int64_t db = game_.a_x * game_.p_y - game_.a_y * game_.p_x;
if(da%d==0 && db%d==0){
  valueType a = da/d;
  valueType b = db/d;

  cheapestWin = a * 3 + b;
}
  return cheapestWin;
}

