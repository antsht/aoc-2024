#ifndef MAIN_HPP
#define MAIN_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

enum class Command { ADV, BXL, BST, JNZ, BXC, OUT, BDV, CDV };

// Virtual Machine class
class VirtualMachine {
 public:
  using Operand = uint64_t;
  using CommandFunction = std::function<bool(Operand)>;

  VirtualMachine(uint64_t A, uint64_t B, uint64_t C) : A_(A), B_(B), C_(C) {
    commands_[Command::ADV] = [&](Operand op) {
      A_ = A_ / std::pow(2, getComboOperandValue(op));
      return true;
    };
    commands_[Command::BXL] = [&](Operand op) {
      B_ = B_ ^ op;
      return true;
    };
    commands_[Command::BST] = [&](Operand op) {
      B_ = getComboOperandValue(op) % 8;
      return true;
    };
    commands_[Command::JNZ] = [&](Operand op) {
      if (A_ != 0) {
        programPouint64_ter_ = op;
        return false;
      }
      return true;
    };
    commands_[Command::BXC] = [&]([[maybe_unused]] Operand op) {
      B_ = B_ ^ C_;
      return true;
    };
    commands_[Command::OUT] = [&](Operand op) {
      /*if (hasOutput_) {
        std::cout << ",";
      } else {
        hasOutput_ = true;
      }
      std::cout << getComboOperandValue(op) % 8;*/
      output.push_back(getComboOperandValue(op) % 8);
      return true;
    };
    commands_[Command::BDV] = [&](Operand op) {
      B_ = A_ / std::pow(2, getComboOperandValue(op));
      return true;
    };
    commands_[Command::CDV] = [&](Operand op) {
      C_ = A_ / std::pow(2, getComboOperandValue(op));
      return true;
    };
  };

  // Execute a program (sequence of commands and operands)
  void execute(const std::vector<uint64_t>& program) {
    if (program.size() % 2 != 0) {
      throw std::invalid_argument(
          "Program sequence is invalid (commands and operands must "
          "alternate).");
    }

    programPouint64_ter_ = 0;
    while (programPouint64_ter_ < static_cast<uint64_t>(program.size()) - 1) {
      Command command = static_cast<Command>(program[programPouint64_ter_]);
      Operand operand = program[programPouint64_ter_ + 1];
      if (commands_[command](operand)) {
        programPouint64_ter_ += 2;
      }
    }
  }

  uint64_t numMatch(const std::vector<uint64_t>& output,
                    const std::vector<uint64_t>& program) {
    int i{static_cast<int>(program.size() - 1)};
    int j{static_cast<int>(output.size() - 1)};
    uint64_t num{0};
    while (i >= 0 && j >= 0) {
      if (program[i] != output[j]) {
        return num;
      }
      ++num;
      --j;
      --i;
    }
    return num;
  }
  void findCloningA(std::vector<uint64_t>& program) {
    uint64_t B_original = B_;
    uint64_t C_original = C_;
    uint64_t a = 0;
    uint64_t a7 = 0;
    uint64_t n = 0;
    while (true) {
      A_ = a;
      B_ = B_original;
      C_ = C_original;
      output.clear();
      execute(program);
      uint64_t nMatch = numMatch(output, program);

      if (nMatch > n) {
        if (nMatch == static_cast<uint64_t>(program.size())) break;
        n = nMatch;
        a <<= 3;
      } else if (a7 == 7) {
        a >>= 3;
        ++a;
        --n;
      } else {
        ++a;
      }
      a7 = a & 7;
      // std::cout << "a: " << a << " a7: " << a7 << " n: " << n << std::endl;
    }

    std::cout << "Register A: " << a << std::endl;
  }

  // Display register values
  void displayRegisters() const {
    std::cout << "Register A: " << A_ << "\n";
    std::cout << "Register B: " << B_ << "\n";
    std::cout << "Register C: " << C_ << "\n";
  }

 private:
  uint64_t getComboOperandValue(uint64_t operand) {
    switch (operand) {
      case 0:
      case 1:
      case 2:
      case 3:
        return operand;
      case 4:
        return A_;
      case 5:
        return B_;
      case 6:
        return C_;
      default:
        throw std::invalid_argument("Invalid operand value.");
    }
  }

 private:
  uint64_t A_ = 0;
  uint64_t B_ = 0;
  uint64_t C_ = 0;
  uint64_t programPouint64_ter_ = 0;
  bool hasOutput_ = false;
  std::unordered_map<Command, CommandFunction> commands_;
  std::vector<uint64_t> output{};
};

#endif  // MAIN_HPP