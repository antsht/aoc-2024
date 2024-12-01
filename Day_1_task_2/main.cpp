#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <cstdint>

template <typename Func>
void process_input_file(const char* fileName, Func processingFunction);

int main() {
  std::unordered_map<unsigned int, unsigned int> data;

  process_input_file(
      "input", [&data](int left, [[maybe_unused]] int right) { data[left]; });

  process_input_file("input", [&data]([[maybe_unused]] int left, int right) {
    auto it = data.find(right);
    if (it != data.end()) {
      it->second++;
    }
  });

  std::uint64_t result = 0;
  for (const auto& [key, value] : data) {
    result += key * value;
  }

  std::cout << result << std::endl;
  return 0;
}

template <typename Func>
void process_input_file(const char* fileName, Func processingFunction) {
  {
    std::ifstream inputFS(fileName);
    if (!inputFS.is_open()) {
      throw std::runtime_error("Error: Unable to open input file." +
                               std::string(fileName));
    }
    int left, right;
    while (inputFS >> left >> right) {
      processingFunction(left, right);
    }
    if (!inputFS.eof() && inputFS.fail()) {
      throw std::runtime_error("Error: Corrupted or invalid file format.");
    }
  }
}