
#include "main.hpp"

int main() {
  using Code = std::pair<int, std::string>;
  std::vector<Code> codes;
  codes.push_back({780, "^^^<<A>AvvvA>A"});
  codes.push_back({539, "<^^Av>A^^AvvvA"});
  codes.push_back({341, "^A<<^AvA>>vA"});
  codes.push_back({189, "^<<A>^^A>AvvvA"});
  codes.push_back({682, "^^A<^AvvAv>A"});
  /*codes.push_back({29, "<A^A>^^AvvvA"});
  codes.push_back({980, "^^^A<AvvvA>A"});
  codes.push_back({179, "^<<A^^A>>AvvvA"});
  codes.push_back({456, "^^<<A>A>AvvA"});
  codes.push_back({379, "^A<<^^A>>AvvvA"});*/

  std::string code;
  uint64_t result = 0;
  for (auto& codePair : codes) {
    std::string enc1 = encode(codePair.second);

    //std::cout << enc1 << std::endl;

    std::string enc2 = encode(enc1);
    std::cout << enc2 << std::endl;
   result += codePair.first * enc2.size();
  }
  std::cout << result << std::endl;
  
  std::cout << std::endl;
  return 0;
}

std::string encode(const std::string& input) {
  std::map<std::pair<char, char>, std::string> keypadMoves;
  keypadMoves[{'A', '^'}] = "<A";
  keypadMoves[{'A', '>'}] = "vA";
  keypadMoves[{'A', 'v'}] = "v<A";
  keypadMoves[{'A', '<'}] = "v<<A";
  keypadMoves[{'^', 'A'}] = ">A";
  keypadMoves[{'^', '<'}] = "v<A";
  keypadMoves[{'^', 'v'}] = "vA";
  keypadMoves[{'^', '>'}] = "v>A";
  keypadMoves[{'<', 'A'}] = ">>^A";
  keypadMoves[{'<', '^'}] = ">^A";
  keypadMoves[{'<', 'v'}] = ">A";
  keypadMoves[{'<', '>'}] = ">>A";
  keypadMoves[{'v', 'A'}] = ">^A";
  keypadMoves[{'v', '<'}] = "<A";
  keypadMoves[{'v', '^'}] = "^A";
  keypadMoves[{'v', '>'}] = ">A";
  keypadMoves[{'>', 'A'}] = "^A";
  keypadMoves[{'>', '<'}] = "<<A";
  keypadMoves[{'>', 'v'}] = "<A";
  keypadMoves[{'>', '^'}] = "<^A";

  keypadMoves[{'A', 'A'}] = "A";
  keypadMoves[{'<', '<'}] = "A";
  keypadMoves[{'>', '>'}] = "A";
  keypadMoves[{'^', '^'}] = "A";
  keypadMoves[{'v', 'v'}] = "A";

  std::string encoded;
  char currentPos = 'A';
  for (char move : input) {
    encoded += keypadMoves[{currentPos, move}];
    //std::cout << keypadMoves[{currentPos, move}];
    currentPos = move;
  }
  return encoded;
}