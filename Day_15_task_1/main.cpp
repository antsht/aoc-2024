#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void move(int &row, int &col, char direction,
          std::vector<std::vector<char>> &dataMap);
void printMap(std::vector<std::vector<char>> &dataMap);
std::uint64_t calculateGPS(std::vector<std::vector<char>> &dataMap);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::string line;
  int robotRow = 0;
  int robotCol = 0;
  std::vector<std::vector<char>> dataMap;
  while (std::getline(inputFS, line)) {
    std::stringstream lineStream(line);
    std::vector<char> lineData;
    char c;
    while (lineStream >> c) {
      lineData.push_back(c);
      if (c == '@') {
        robotCol = lineData.size() - 1;
        robotRow = dataMap.size();
      }
    }
    dataMap.push_back(lineData);
  }
  inputFS.close();

  std::vector<char> dataMoves;
  std::ifstream inputFSMove("./input_moves");
  if (!inputFSMove.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  char c;
  while (inputFSMove >> c) {
    dataMoves.push_back(c);
  }
  inputFSMove.close();

  printMap(dataMap);
  for (char direction : dataMoves) {
    move(robotRow, robotCol, direction, dataMap);
  }

  printMap(dataMap);

  std::cout << calculateGPS(dataMap) << std::endl;
  return 0;
}

void move(int &row, int &col, char direction,
          std::vector<std::vector<char>> &dataMap) {
  int velocity_row = 0;
  int velocity_col = 0;
  switch (direction) {
    case 'v':
      velocity_row = 1;
      break;
    case '>':
      velocity_col = 1;
      break;
    case '^':
      velocity_row = -1;
      break;
    case '<':
      velocity_col = -1;
      break;
    default:
      break;
  }
  int dest_row = row;
  int dest_col = col;
  bool canMove = false;
  while (dataMap[dest_row][dest_col] != '#') {
    dest_row += velocity_row;
    dest_col += velocity_col;
    if (dataMap[dest_row][dest_col] == '.') {
      canMove = true;
      break;
    }
  }

  if (canMove) {
    dataMap[row][col] = '.';
    if (dataMap[row + velocity_row][col + velocity_col] == 'O') {
      dataMap[dest_row][dest_col] = 'O';
    }
    dataMap[row + velocity_row][col + velocity_col] = '@';
    row += velocity_row;
    col += velocity_col;
  }
}

void printMap(std::vector<std::vector<char>> &dataMap) {
  for (const auto &row : dataMap) {
    for (const auto &cell : row) {
      std::cout << cell;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

std::uint64_t calculateGPS(std::vector<std::vector<char>> &dataMap){
  std::uint64_t gps = 0;
  for (size_t row=0; row<dataMap.size(); ++row){
    for (size_t col=0; col<dataMap[row].size(); ++col){
      if (dataMap[row][col] == 'O'){
        gps += (row*100)+(col);
      }
    }
  }
  return gps;
}