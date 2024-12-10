CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -pedantic -O2

TARGET = main
SRC = main.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
