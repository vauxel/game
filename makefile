CXX						:= g++
CXXFLAGS			:= -std=c++20 -g -Wall -Wl,-rpath=lib/
UNAME					:= $(shell uname)
LDFLAGS				:= -Llib/ -lopengl32 -lglfw3 -lglew32 -lassimp
BUILD					:= ./bin
OBJ_DIR				:= $(BUILD)/objects
APP_DIR				:= $(BUILD)
TARGET				:= game
TEST_TARGET		:= test
INCLUDE				:= -Iinclude/ -Isrc/
SRC						:= $(shell find src -name '*.cpp')
TEST					:= $(wildcard test/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJECTS := $(TEST:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)
test: build $(APP_DIR)/$(TEST_TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)

$(APP_DIR)/$(TEST_TARGET): $(TEST_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TEST_TARGET) $(filter-out $(OBJ_DIR)/src/main.o, $(OBJECTS)) $(TEST_OBJECTS) $(LDFLAGS)

.PHONY: all build clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
