CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -pedantic -O2

TARGET = main
SRC = main.cpp

.PHONY: $(TARGET)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

.PHONY: profile
profile: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -g -pg
	./$(TARGET)
	gprof $(TARGET) > profile.txt

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
