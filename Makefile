CXXFLAGS ?= -O3
CXXFLAGS_EXTRA := -march=native -std=c++17 -Isrc -pedantic -Wall -Wextra -Werror -MMD -MP -pthread
#CXXFLAGS_EXTRA += -fsanitize=address -fsanitize=undefined
#CXXFLAGS_EXTRA += -fsanitize=thread
BUILD_DIR := build

SRC := $(wildcard src/*.cpp)
OBJ := $(foreach file,$(SRC),$(BUILD_DIR)/$(file:.cpp=.o))
DEP := $(OBJ:.o=.d)
OUTPUT := triplet_challenge

UT_SRC := $(wildcard test/*.cpp) $(filter-out src/main.cpp,$(SRC))
UT_OBJ := $(foreach file,$(UT_SRC),$(BUILD_DIR)/$(file:.cpp=.o))
UT_DEP := $(UT_OBJ:.o=.d)
UT_OUTPUT := unit_test

$(OUTPUT):

all: $(OUTPUT) check

$(BUILD_DIR):
	mkdir -p $@/src $@/test

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_EXTRA) -c -o $@ $<

$(OUTPUT): $(BUILD_DIR) $(OBJ)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_EXTRA) -o $@ $(OBJ)

check: $(OUTPUT) $(UT_OUTPUT)
	./$(UT_OUTPUT)

$(UT_OUTPUT): $(BUILD_DIR) $(UT_OBJ)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_EXTRA) -o $@ $(UT_OBJ)

clean:
	rm -rf $(BUILD_DIR) $(OUTPUT) $(UT_OUTPUT)

.PHONY: clean check

dbg-%:
	@echo "$* = $($*)"

-include $(DEP) $(UT_DEP)
