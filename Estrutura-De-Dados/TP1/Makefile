CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
SRC_DIR = src
INC_DIR = include
BUILD_DIR = obj
BIN_DIR = bin

$(BIN_DIR)/program.exe: $(BUILD_DIR)/main.o $(BUILD_DIR)/pilha.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/pilha.h
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BUILD_DIR)/pilha.o: $(SRC_DIR)/pilha.cpp $(INC_DIR)/pilha.h
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

.PHONY: clean run

clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/*.exe

run: $(BIN_DIR)/program.exe
	./$<