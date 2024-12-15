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
bool moveBoxRight(int box_row, int box_col,
                  std::vector<std::vector<char>> &dataMap);
bool moveBoxLeft(int box_row, int box_col,
                 std::vector<std::vector<char>> &dataMap);
bool moveBoxUp(int box_row, int box_col,
               std::vector<std::vector<char>> &dataMap);
bool moveBoxDown(int box_row, int box_col,
                 std::vector<std::vector<char>> &dataMap);

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
      if (c == '@') {
        lineData.push_back(c);
        robotCol = lineData.size() - 1;
        robotRow = dataMap.size();

        lineData.push_back('.');
      } else if (c == 'O') {
        lineData.push_back('[');
        lineData.push_back(']');
      } else {
        lineData.push_back(c);
        lineData.push_back(c);
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

    //printMap(dataMap);
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
  int dest_row = row + velocity_row;
  int dest_col = col + velocity_col;
  if (dataMap[dest_row][dest_col] == '.') {
    dataMap[row][col] = '.';
    dataMap[dest_row][dest_col] = '@';
    row = dest_row;
    col = dest_col;

  } else if (dataMap[dest_row][dest_col] == '#') {
    return;
  } else if (dataMap[dest_row][dest_col] == '[' && velocity_col == 1) {
    if (moveBoxRight(dest_row, dest_col, dataMap)) {
      dataMap[row][col] = '.';
      dataMap[dest_row][dest_col] = '@';
      row = dest_row;
      col = dest_col;
    }
  } else if (dataMap[dest_row][dest_col] == ']' && velocity_col == -1) {
    if (moveBoxLeft(dest_row, dest_col - 1, dataMap)) {
      dataMap[row][col] = '.';
      dataMap[dest_row][dest_col] = '@';
      row = dest_row;
      col = dest_col;
    }
  } else if (dataMap[dest_row][dest_col] == '[' && velocity_row == -1) {
    if (moveBoxUp(dest_row, dest_col, dataMap)) {
      dataMap[row][col] = '.';
      dataMap[dest_row][dest_col] = '@';
      row = dest_row;
      col = dest_col;
    }
  } else if (dataMap[dest_row][dest_col] == ']' && velocity_row == -1) {
    if (moveBoxUp(dest_row, dest_col - 1, dataMap)) {
      dataMap[row][col] = '.';
      dataMap[dest_row][dest_col] = '@';
      row = dest_row;
      col = dest_col;
    }
  } else if (dataMap[dest_row][dest_col] == '[' && velocity_row == 1) {
    if (moveBoxDown(dest_row, dest_col, dataMap)) {
      dataMap[row][col] = '.';
      dataMap[dest_row][dest_col] = '@';
      row = dest_row;
      col = dest_col;
    }
  } else if (dataMap[dest_row][dest_col] == ']' && velocity_row == 1) {
    if (moveBoxDown(dest_row, dest_col - 1, dataMap)) {
      dataMap[row][col] = '.';
      dataMap[dest_row][dest_col] = '@';
      row = dest_row;
      col = dest_col;
    }
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

std::uint64_t calculateGPS(std::vector<std::vector<char>> &dataMap) {
  std::uint64_t gps = 0;
  for (size_t row = 0; row < dataMap.size(); ++row) {
    for (size_t col = 0; col < dataMap[row].size(); ++col) {
      if (dataMap[row][col] == '[') {
        gps += (row * 100) + (col);
      }
    }
  }
  return gps;
}

bool moveBoxRight(int box_row, int box_col,
                  std::vector<std::vector<char>> &dataMap) {
  if (dataMap[box_row][box_col + 2] == '.') {
    dataMap[box_row][box_col + 1] = '[';
    dataMap[box_row][box_col + 2] = ']';
    return true;
  }
  if (dataMap[box_row][box_col + 2] == '#') {
    return false;
  }
  if (dataMap[box_row][box_col + 2] == '[') {
    if(moveBoxRight(box_row, box_col + 2, dataMap)){
      dataMap[box_row][box_col + 1] = '[';
      dataMap[box_row][box_col + 2] = ']';
      return true;
    }
  }
  return false;
}
bool moveBoxLeft(int box_row, int box_col,
                 std::vector<std::vector<char>> &dataMap) {
  if (dataMap[box_row][box_col - 1] == '.') {
    dataMap[box_row][box_col - 1] = '[';
    dataMap[box_row][box_col] = ']';
    return true;
  }
  if (dataMap[box_row][box_col - 1] == '#') {
    return false;
  }
  if (dataMap[box_row][box_col - 1] == ']') {
    if(moveBoxLeft(box_row, box_col - 2, dataMap))
    {
      dataMap[box_row][box_col - 1] = '[';
      dataMap[box_row][box_col] = ']';
      return true;
    }
  }
  return false;
}
bool moveBoxUp(int box_row, int box_col,
               std::vector<std::vector<char>> &dataMap) {
    std::vector<std::vector<char>> tmpMap = dataMap;
    if (dataMap[box_row - 1][box_col] == '.' && dataMap[box_row - 1][box_col + 1] == '.') {
        dataMap[box_row - 1][box_col] = '[';
        dataMap[box_row - 1][box_col + 1] = ']';
        dataMap[box_row][box_col] = '.';
        dataMap[box_row][box_col + 1] = '.';
        return true;
    } else if (dataMap[box_row - 1][box_col] == '#' || dataMap[box_row - 1][box_col + 1] == '#') {
        return false;
    } else if (dataMap[box_row - 1][box_col] == '[') {
        if (moveBoxUp(box_row - 1, box_col, dataMap)) {
            dataMap[box_row - 1][box_col] = '[';
            dataMap[box_row - 1][box_col + 1] = ']';
            dataMap[box_row][box_col] = '.';
            dataMap[box_row][box_col + 1] = '.';
            return true;
        }
    } else if (dataMap[box_row - 1][box_col] == ']' && dataMap[box_row - 1][box_col + 1] == '.') {
        if (moveBoxUp(box_row - 1, box_col - 1, dataMap)) {
            dataMap[box_row - 1][box_col] = '[';
            dataMap[box_row - 1][box_col + 1] = ']';
            dataMap[box_row][box_col] = '.';
            dataMap[box_row][box_col + 1] = '.';
            return true;
        }
    } else if (dataMap[box_row - 1][box_col] == '.' && dataMap[box_row - 1][box_col + 1] == '[') {
        if (moveBoxUp(box_row - 1, box_col + 1, dataMap)) {
            dataMap[box_row - 1][box_col] = '[';
            dataMap[box_row - 1][box_col + 1] = ']';
            dataMap[box_row][box_col] = '.';
            dataMap[box_row][box_col + 1] = '.';
            return true;
        }
    } else if (dataMap[box_row - 1][box_col] == ']' && dataMap[box_row - 1][box_col + 1] == '[') {
        if (moveBoxUp(box_row - 1, box_col - 1, dataMap) && moveBoxUp(box_row - 1, box_col + 1, dataMap)) {
            dataMap[box_row - 1][box_col] = '[';
            dataMap[box_row - 1][box_col + 1] = ']';
            dataMap[box_row][box_col] = '.';
            dataMap[box_row][box_col + 1] = '.';
            return true;
        }
    }
    dataMap = tmpMap;
  return false;
}
bool moveBoxDown(int box_row, int box_col,
                 std::vector<std::vector<char>> &dataMap) {
  std::vector<std::vector<char>> tmpMap = dataMap;
  if (dataMap[box_row + 1][box_col] == '.' &&
      dataMap[box_row + 1][box_col + 1] == '.') {
    dataMap[box_row + 1][box_col] = '[';
    dataMap[box_row + 1][box_col + 1] = ']';
    dataMap[box_row][box_col] = '.';
    dataMap[box_row][box_col + 1] = '.';
    return true;
  } else if (dataMap[box_row + 1][box_col] == '#' ||
             dataMap[box_row + 1][box_col + 1] == '#') {
    return false;
  } else if (dataMap[box_row + 1][box_col] == '[') {
    if (moveBoxDown(box_row + 1, box_col, dataMap)) {
      dataMap[box_row + 1][box_col] = '[';
      dataMap[box_row + 1][box_col + 1] = ']';
      dataMap[box_row][box_col] = '.';
      dataMap[box_row][box_col + 1] = '.';
      return true;
    }
  } else if (dataMap[box_row + 1][box_col] == ']' &&
             dataMap[box_row + 1][box_col + 1] == '.') {
    if (moveBoxDown(box_row + 1, box_col - 1, dataMap)) {
      dataMap[box_row + 1][box_col] = '[';
      dataMap[box_row + 1][box_col + 1] = ']';
      dataMap[box_row][box_col] = '.';
      dataMap[box_row][box_col + 1] = '.';
      return true;
    }
  } else if (dataMap[box_row + 1][box_col] == '.' &&
             dataMap[box_row + 1][box_col + 1] == '[') {
    if (moveBoxDown(box_row + 1, box_col + 1, dataMap)) {
      dataMap[box_row + 1][box_col] = '[';
      dataMap[box_row + 1][box_col + 1] = ']';
      dataMap[box_row][box_col] = '.';
      dataMap[box_row][box_col + 1] = '.';
      return true;
    }
  } else if (dataMap[box_row + 1][box_col] == ']' &&
             dataMap[box_row + 1][box_col + 1] == '[') {
    if (moveBoxDown(box_row + 1, box_col - 1, dataMap) &&
        moveBoxDown(box_row + 1, box_col + 1, dataMap)) {
      dataMap[box_row + 1][box_col] = '[';
      dataMap[box_row + 1][box_col + 1] = ']';
      dataMap[box_row][box_col] = '.';
      dataMap[box_row][box_col + 1] = '.';
      return true;
    }
  }
  dataMap = tmpMap;
  return false;
}