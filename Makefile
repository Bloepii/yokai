SRC_DIR=src
OBJ_DIR=obj
BUILD_DIR=bin
INC_DIR=include
TARGET=yokai
SOURCES=$(shell find $(SRC_DIR)/ -name '*.cpp')
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
CC=g++
CFLAGS=-march=native
CPPFLAGS=$(addprefix -I, $(INC_DIR)) -Wall -Wextra -pedantic -std=c++23
LIBS=-lFastNoise -Llib -static

.PHONY: all clean debug release
release: CFLAGS += -O3 -DNDEBUG
release: all
debug: CFLAGS += -O0 -DDEBUG -ggdb3
debug: all
all: dir $(BUILD_DIR)/$(TARGET)
clean:
	rm -f $(BUILD_DIR)/$(TARGET) $(OBJ_DIR)/*.o
$(BUILD_DIR)/$(TARGET):	$(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJECTS) $(LIBS)
$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< $(LIBS) -o $@
run: all
	$(BUILD_DIR)/$(TARGET)
dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)
redo: clean all
rr: redo run
rrr: clean release run
