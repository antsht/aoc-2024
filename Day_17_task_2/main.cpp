#include "main.hpp"

int main() {
  VirtualMachine vm{51064159, 0, 0};
  std::vector<uint64_t> program = {2, 4, 1, 5, 7, 5, 1, 6,
                                   0, 3, 4, 6, 5, 5, 3, 0};

  try {
    vm.findCloningA(program);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}

