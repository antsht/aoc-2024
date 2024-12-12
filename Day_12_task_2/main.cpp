#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint32_t;
void printData(const std::vector<std::string> &data);
std::pair<valueType, valueType> calculateAreaAndPerimeter(
    std::vector<std::string> &data, valueType row, valueType col, char type);

void markVisited(std::vector<std::string> &data,
                 std::vector<std::string> &dataTmp);

valueType calcFence(const std::vector<std::string> &data);
valueType calcCorners(const std::vector<std::string> &data, valueType row, valueType col);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<std::string> data;
  std::string line;
  while (std::getline(inputFS, line)) {
    data.push_back(line);
  }
  inputFS.close();

  printData(data);
  std::vector<std::string> dataCopy = data;
  std::uint64_t result = 0;
  for (size_t row = 0; row < data.size(); ++row) {
      for (size_t col = 0; col < data[row].size(); ++col) {
          if (data[row][col] != ' ') {
              std::vector<std::string> dataTmp = dataCopy;
              auto [area, perimeter] = calculateAreaAndPerimeter(dataTmp, row, col, data[row][col]);
              // printData(dataTmp);
              std::cout << "Area: " << area << ", Perimeter: " << perimeter << std::endl;
              valueType fences = calcFence(dataTmp);
              std::cout << "Corners: " << fences << std::endl;
              result += area * fences;
              markVisited(data, dataTmp);
          }
      }
  }
  std::cout << "Result: " << result << std::endl;
  return 0;
}

void printData(const std::vector<std::string> &data) {
  for (auto &row : data) {
    std::cout << row;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

std::pair<valueType, valueType> calculateAreaAndPerimeter(
    std::vector<std::string> &data, valueType row, valueType col, char type) {
  valueType area = 1;
  valueType perimeter = 0;
  data[row][col] = ' ';
  if (row > 0 && data[row - 1][col] == type) {
    std::pair<valueType, valueType> result =
        calculateAreaAndPerimeter(data, row - 1, col, type);
    area += result.first;
    perimeter += result.second;
  } else {
    if (row == 0 || (row > 0 && data[row - 1][col] != ' ')) {
      perimeter++;
    }
  }
  if (row < data.size() - 1 && data[row + 1][col] == type) {
    std::pair<valueType, valueType> result =
        calculateAreaAndPerimeter(data, row + 1, col, type);
    area += result.first;
    perimeter += result.second;
  } else {
    if (row == data.size() - 1 ||
        (row < data.size() - 1 && data[row + 1][col] != ' ')) {
      perimeter++;
    }
  }
  if (col > 0 && data[row][col - 1] == type) {
    std::pair<valueType, valueType> result =
        calculateAreaAndPerimeter(data, row, col - 1, type);
    area += result.first;
    perimeter += result.second;
  } else {
    if (col == 0 || (col > 0 && data[row][col - 1] != ' ')) {
      perimeter++;
    }
  }
  if (col < data[row].size() - 1 && data[row][col + 1] == type) {
    std::pair<valueType, valueType> result =
        calculateAreaAndPerimeter(data, row, col + 1, type);
    area += result.first;
    perimeter += result.second;
  } else {
    if (col == data[row].size() - 1 ||
        (col < data[row].size() - 1 && data[row][col + 1] != ' ')) {
      perimeter++;
    }
  }

  return std::make_pair(area, perimeter);
}

void markVisited(std::vector<std::string> &data,
                 std::vector<std::string> &dataTmp) {
  for (size_t row = 0; row < data.size(); ++row) {
    for (size_t col = 0; col < data[row].size(); ++col) {
      if (dataTmp[row][col] == ' ') {
        data[row][col] = ' ';
      }
    }
  }
}

valueType calcFence(const std::vector<std::string> &data){
  valueType result = 0;
  for (size_t row = 0; row < data.size(); ++row) {
      for (size_t col = 0; col < data[row].size(); ++col) {
          if (data[row][col] == ' ') {
              result += calcCorners(data, row, col);
          }
      }
  }
  return result;
}

valueType calcCorners(const std::vector<std::string> &data, valueType row, valueType col){
valueType result = 0;
/*
xTx
T x
xxx
*/
if ((row==0 || data[row-1][col]!=' ') && (col==0 || data[row][col-1]!=' ')){
  ++result;
}
/*
xTx
x T
xxx
*/
if ((row==0 || data[row-1][col]!=' ') && (col==(data[0].size()-1) || data[row][col+1]!=' ')){
  ++result;
}
/*
xxx
T x
xTx
*/
if ((row==data.size()-1 || data[row+1][col]!=' ') && (col==0 || data[row][col-1]!=' ')){
  ++result;
}
/*
xxx
x T
xTx
*/
if ((row==data.size()-1 || data[row+1][col]!=' ') && (col==data[0].size()-1 || data[row][col+1]!=' ')){
  ++result;
}

//////////////

/*
x x
  x
xxx
*/
if (row > 0 && col > 0 && data[row - 1][col] == ' ' &&
    data[row][col - 1] == ' ' && data[row-1][col-1] != ' ') {
  ++result;
}
/*
x x
x  
xxx
*/
if (row > 0 &&  (col < data[0].size() - 1) && data[row - 1][col] == ' ' &&
    data[row][col + 1] == ' ' && data[row - 1][col + 1] != ' ') {
  ++result;
}
/*
xxx
  x
x x
*/
if ((row < data.size() - 1) && col > 0 &&
    data[row][col-1] == ' ' && data[row+1][col] == ' ' &&
    data[row + 1][col - 1] != ' ') {
  ++result;
}
/*
xxx
x  
x x
*/
if ((row < data.size() - 1) && (col < data[0].size() - 1) &&
    data[row][col + 1] == ' ' && data[row + 1][col] == ' ' &&
    data[row + 1][col + 1] != ' ') {
  ++result;
}

return result;
}