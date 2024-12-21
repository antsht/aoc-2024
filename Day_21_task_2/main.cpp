#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

std::string encode(const std::string &input) {
  static const std::map<std::pair<char, char>, std::string>
      keypadMoves = {
          {{'A', '^'}, "<A"},   {{'A', '>'}, "vA"},  {{'A', 'v'}, "v<A"},
          {{'A', '<'}, "v<<A"}, {{'^', 'A'}, ">A"},  {{'^', '<'}, "v<A"},
          {{'^', 'v'}, "vA"},   {{'^', '>'}, "v>A"}, {{'<', 'A'}, ">>^A"},
          {{'<', '^'}, ">^A"},  {{'<', 'v'}, ">A"},  {{'<', '>'}, ">>A"},
          {{'v', 'A'}, ">^A"},  {{'v', '<'}, "<A"},  {{'v', '^'}, "^A"},
          {{'v', '>'}, ">A"},   {{'>', 'A'}, "^A"},  {{'>', '<'}, "<<A"},
          {{'>', 'v'}, "<A"},   {{'>', '^'}, "<^A"}, {{'A', 'A'}, "A"},
          {{'<', '<'}, "A"},    {{'>', '>'}, "A"},   {{'^', '^'}, "A"},
          {{'v', 'v'}, "A"}};

  std::string encoded;
  encoded.reserve(input.size() *
                  4);  // Preallocate to avoid frequent reallocations.
  char currentPos = 'A';
  for (char move : input) {
    encoded += keypadMoves.at({currentPos, move});
    currentPos = move;
  }
  return encoded;
}

int main() {
  using Code = std::pair<int, std::string>;
  std::vector<Code> codes = {{780, "^^^<<A>AvvvA>A"},
                             {539, "<^^Av>A^^AvvvA"},
                             {341, "^A<<^AvA>>vA"},
                             {189, "^<<A>^^A>AvvvA"},
                             {682, "^^A<^AvvAv>A"}};

  uint64_t result = 0;
  for (const auto &codePair : codes) {
    std::string enc1 = encode(codePair.second);

    // Limit growth to prevent memory issues
    for (size_t i = 1; i <= 24; ++i) {
      enc1 = encode(enc1);
      if (enc1.size() >
          1e12) {  // Arbitrary threshold to prevent runaway growth.
        std::cout << "Size exceeded limit. Stopping early.\n";
        break;
      }
    }
    result += static_cast<uint64_t>(codePair.first) * enc1.size();
  }
  std::cout << "Final result: " << result << std::endl;

  return 0;
}