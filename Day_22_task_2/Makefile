CXX = g++
CXXFLAGS = -std=c++20 -pedantic -O2

TARGET = main
SRC = main.cpp

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
