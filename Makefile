CXXFLAGS ?= -g -O2 -std=c++17 -Isrc
SRC := $(wildcard src/*.cpp)
BUILD_DIR := build
OBJ := $(BUILD_DIR)/$(SRC:.cpp=.o)
OUTPUT := triplet_challenge
UNIT_TEST := unit_test

all: $(OUTPUT) check

$(BUILD_DIR):
	mkdir -p $@/src $@/unit_test

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(OUTPUT): $(BUILD_DIR) $(OBJ)
	$(CXX) -o $@ $(OBJ)

check: $(OUTPUT) $(UNIT_TEST)
	./$(UNIT_TEST)

$(UNIT_TEST): test/unit_test.o $(BUILD_DIR)/src/triplet_challenge.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR) $(OUTPUT) $(UNIT_TEST)

.PHONY: clean check
