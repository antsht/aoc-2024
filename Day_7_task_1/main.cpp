#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint64_t;
valueType checkLine(const std::vector<valueType> &line);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<std::vector<valueType>> inputData;
  inputData.reserve(850);
  std::string line;
  while (std::getline(inputFS, line)) {
    std::stringstream lineStream(line);
    std::vector<valueType> lineToCheck;
    valueType num;
    char c;
    lineStream >> num >> c;
    lineToCheck.push_back(num);
    while (lineStream >> num) {
      lineToCheck.push_back(num);
    }
    inputData.push_back(lineToCheck);
  }
  inputFS.close();

  // print inputData
  for (const auto &line : inputData) {
    for (const auto &num : line) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
  valueType result = 0;
  for (const auto &line : inputData) {
      result+=checkLine(line);
  }
  std::cout << result << std::endl;
      return 0;
  }

  valueType checkLine(const std::vector<valueType> &line) {
      valueType result = line[0];
      std::vector<valueType> resultV1;
      resultV1.push_back(line[1]);
      std::vector<valueType> resultV2;
      for (size_t i = 2; i < line.size(); ++i) {
      for (auto &num : resultV1) {
      resultV2.push_back(num + line[i]);
      resultV2.push_back(num * line[i]);
    }
    std::swap(resultV1, resultV2);
    resultV2.clear();
  }
  for (auto &num : resultV1) {
    if (num == result) {
      return result;
    }
  }
  return 0;
  }