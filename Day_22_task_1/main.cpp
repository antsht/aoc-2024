#include "main.hpp"

int main() {
  std::vector<uint64_t> secretNumbers;
  secretNumbers.reserve(2008);

  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  uint64_t a;
  while (inputFS >> a) {
    secretNumbers.emplace_back(a);
  }
  inputFS.close();
  uint64_t sum = 0;
  for (auto number : secretNumbers) {
      std::cout << "Init number: " << number;
      for (size_t i = 0; i < 2000; ++i) {
          number = generateNextSecretNumber(number);
      }
      sum += number;
      std::cout << "  Result secret number: " << number << std::endl;
  }
  std::cout << "Sum: " << sum << std::endl;
  return 0;
}

uint64_t generateNextSecretNumber(uint64_t prevNumber) {
  u_int64_t nextNumber = (prevNumber ^ (prevNumber << 6)) % 16777216;
  nextNumber = (nextNumber ^ (nextNumber >> 5)) % 16777216;
  nextNumber = (nextNumber ^ (nextNumber << 11)) % 16777216;

  return nextNumber;
}