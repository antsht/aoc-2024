#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>

bool checkDataRowValidity(const std::vector<int> &dataRow, const std::unordered_multimap<int, int> &rules);

int main() {

  std::ifstream inputFS("./input1");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }

  std::unordered_multimap<int, int> rules;
    int a, b;
    while (inputFS >> a >> b) {
        rules.emplace(a, b);
    }
  inputFS.close();

  // print rules
  for (const auto& rule : rules) {
    std::cout << "Rule: " << rule.first << " -> " << rule.second << std::endl;
  }

std::ifstream input2FS("./input2");
if (!input2FS) {
    std::cerr << "Unable to open file\n";
    return 1; 
}

std::vector<std::vector<int>> data;
std::string line;
while (std::getline(input2FS, line)) {
    // Skip empty lines
    if (line.empty()) continue;

    std::istringstream iss(line);
    std::vector<int> row;

    int value;
    while (iss >> value) {
        row.push_back(value);
    }

    data.push_back(row);
}
input2FS.close();

  std::uint32_t result = 0;
for (const auto& row : data) {
  if( checkDataRowValidity(row, rules)){
    std::cout << "Row is valid: "<<row[row.size() / 2]<< std::endl;
  result += row[row.size() / 2];
  }
}




  std::cout << result << std::endl;

  return 0;
}

bool checkDataRowValidity(const std::vector<int> &dataRow, const std::unordered_multimap<int, int> &rules) {
  for (size_t i = 1; i < dataRow.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      // check if there a rule that connects the two numbers dattaRow[i] and dataRow[j]
      auto range = rules.equal_range(dataRow[i]);
      for (auto it = range.first; it != range.second; ++it) {
        if (it->second == dataRow[j]) {
          // found a rule that connects the two numbers
          return false;
        }
      }
    }
  }
  return true;
}

