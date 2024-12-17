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
  using Operand = int;
  using CommandFunction = std::function<bool(Operand)>;

  VirtualMachine(int A, int B, int C) : A_(A), B_(B), C_(C) {
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
        programPointer_ = op;
        return false;
      }
      return true;
    };
    commands_[Command::BXC] = [&]([[maybe_unused]] Operand op) {
      B_ = B_ ^ C_;
      return true;
    };
    commands_[Command::OUT] = [&](Operand op) {
      if (hasOutput_) {
        std::cout << ",";
      } else {
        hasOutput_ = true;
      }
      std::cout << getComboOperandValue(op) % 8;
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
  void execute(const std::vector<int>& program) {
    if (program.size() % 2 != 0) {
      throw std::invalid_argument(
          "Program sequence is invalid (commands and operands must "
          "alternate).");
    }

    programPointer_ = 0;
    while (programPointer_ < static_cast<int>(program.size()) - 1) {
      Command command = static_cast<Command>(program[programPointer_]);
      Operand operand = program[programPointer_ + 1];
      if (commands_[command](operand)) {
        programPointer_ += 2;
      }
    }
    std::cout << std::endl;
  }

  // Display register values
  void displayRegisters() const {
    std::cout << "Register A: " << A_ << "\n";
    std::cout << "Register B: " << B_ << "\n";
    std::cout << "Register C: " << C_ << "\n";
  }

 private:
  int getComboOperandValue(int operand) {
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
  int A_ = 0;
  int B_ = 0;
  int C_ = 0;
  int programPointer_ = 0;
  bool hasOutput_ = false;
  std::unordered_map<Command, CommandFunction> commands_;
};

#endif  // MAIN_HPP