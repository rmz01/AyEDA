CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Lista de archivos fuente y objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cc)
OBJECTS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/Cellular_automaton_1D

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean
