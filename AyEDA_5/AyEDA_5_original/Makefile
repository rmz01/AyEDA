CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS =

# Directorios de origen y destino
SRC_DIR = src
INC_DIR = INC
OBJ_DIR = obj

# Archivos de origen y destino
SRC_FILES = $(wildcard $(SRC_DIR)/*.cc)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))
INC_FILES = $(wildcard $(INC_DIR)/*.h)

# Nombre del ejecutable
TARGET = programa

# Crear la carpeta obj si no existe
$(shell mkdir -p $(OBJ_DIR))

# Regla para generar el ejecutable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para generar los archivos de objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(INC_FILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
