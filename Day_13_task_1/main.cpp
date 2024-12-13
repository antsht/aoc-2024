#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

struct game {
  std::uint32_t a_x;
  std::uint32_t a_y;
  std::uint32_t b_x;
  std::uint32_t b_y;
  std::uint32_t p_x;
  std::uint32_t p_y;
};
using valueType = std::uint32_t;
void parseGameString(const std::string &line, game &newGame);
void printData(const std::vector<game> &data);
valueType findBestGame(const game &game);

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
    sscanf(line.c_str(), "Button A: X+%u, Y+%u", &(newGame.a_x),
           &(newGame.a_y));
  } else if (line.find("Button B:") != std::string::npos) {
    sscanf(line.c_str(), "Button B: X+%u, Y+%u", &(newGame.b_x),
           &(newGame.b_y));
  } else if (line.find("Prize:") != std::string::npos) {
    sscanf(line.c_str(), "Prize: X=%u, Y=%u", &(newGame.p_x), &(newGame.p_y));
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

valueType findBestGame(const game &game) {
  valueType cheapestWin = 0;
  for (valueType a = 0; a <= 100; ++a) {
    for (valueType b = 0; b <= 100; ++b) {
      if (game.a_x * a + game.b_x * b == game.p_x &&
          game.a_y * a + game.b_y * b == game.p_y) {
        if (cheapestWin == 0 || a * 3 + b < cheapestWin) {
          cheapestWin = a * 3 + b;
        }
      }
    }
  }
  return cheapestWin;
}