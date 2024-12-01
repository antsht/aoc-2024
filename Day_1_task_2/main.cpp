#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>

void process_input_file(const char* fileName,
                        std::function<void(int, int)> processingFunction);

int main() {
  std::unordered_map<unsigned int, unsigned int> data;

  process_input_file("input", [&data](int left, [[maybe_unused]] int right) {
    data[left];
  });

  process_input_file("input", [&data]([[maybe_unused]] int left, int right) {
    if (data.contains(right)) {
      data[right]++;
    }
  });

  u_int64_t result = 0;
  for (const auto& [key, value] : data) {
    result += key * value;
  }

  std::cout << result << std::endl;
  return 0;
}

void process_input_file(const char* fileName,
                        std::function<void(int, int)> processingFunction) {
  {
    std::ifstream inputFS(fileName);
    if (inputFS.is_open()) {
      int left, right;
      while (inputFS >> left >> right) {
        processingFunction(left, right);
      }
    } else {
      throw std::runtime_error("Error: Unable to open input file.");
    }
  }
}