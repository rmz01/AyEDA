#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

// Definición de tipos
using State = unsigned char;
using Position = int;

class Lattice;

class Cell {
 public:
  // Constructores
  Cell();
  Cell(const Position& pos, const State& st = '0');
  
  // Getters
  State getState() const { return state_; }
  Position getPosition() const { return position_; }

  // Setters
  State setState(State newState);
  
	// Métodos
  void updateState();
  int nextState(const Lattice& lattice);

  // Sobrecarga del operador de inserción
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

 private:
  Position position_;
  State state_;
  State nextState_;
};

class Lattice {
 public:
  // Constructor
  Lattice(int size);

  // Getters
  const Cell& getCell(const Position& pos) const { return cells_[pos]; }
  int getSize() const { return size_; }
  std::string getBorderType() const { return border_type_; }
  State getBorderValue() const { return border_value_; }


  // Metodo para cargar la configuración inicial
  void loadInitialConfiguration(const std::string& fileName, const std::string& borderType, const State& borderValue);

  // Implementa la lógica de evolución
  void nextGeneration();

  // Sobrecarga del operador de inserción
  friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);

 private:
  std::vector<Cell> cells_;
  int size_;
  std::string border_type_;
  State border_value_;
};

// Definiciones de métodos de Cell

Cell::Cell() : position_(0), state_('0'), nextState_('0') {}

Cell::Cell(const Position& pos, const State& st) : position_(pos), state_(st), nextState_('0') {}

State Cell::setState(State newState) {
  state_ = newState;
  return state_;
}

void Cell::updateState() { state_ = nextState_; }

int Cell::nextState(const Lattice& lattice) {
  State left_neighbor_state, right_neighbor_state;
  std::string border_type = lattice.getBorderType();
  State border_value = lattice.getBorderValue();
  State central_state = lattice.getCell(position_).getState();

  if (border_type == "open") {
    if (position_ == 0) {
      left_neighbor_state = border_value;
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    } else if (position_ == lattice.getSize() - 1) {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = border_value;
    } else {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    }
  } else if (border_type == "periodic") {
    if (position_ == 0) {
      left_neighbor_state = lattice.getCell(lattice.getSize() - 1).getState();
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    } else if (position_ == lattice.getSize() - 1) {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = lattice.getCell(0).getState();
    } else {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    }
  }

  // Implementa la lógica de evolución con la formula
  int left = left_neighbor_state - '0';
  int center = central_state - '0';
  int right = right_neighbor_state - '0';

  nextState_ = (center + right + center * right + left * center * right) % 2 + '0';  

  return nextState_;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << (cell.getState() == '1' ? 'X' : 'Y');
  return os;
}

// Definiciones de métodos de Lattice

Lattice::Lattice(int size) {
  // El constructor del retículo crea las células en memoria dinámica.
  size_ = size;
  cells_.resize(size, Cell());
  for (int i = 0; i < getSize(); ++i) {
    cells_[i] = Cell(i);
  }
}

void Lattice::loadInitialConfiguration(const std::string& fileName, const std::string& borderType, const State& borderValue) {
  border_type_ = borderType;
  border_value_ = borderValue;

  if (!fileName.empty()) {
    std::ifstream file(fileName);
    if (!file) {
      std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
      return;
    }
    char state;
    int i = 0;
    while (file.get(state)) {
      if (i >= size_) {
        std::cerr << "Error: El archivo tiene más celdas que el tamaño de la retícula." << std::endl;
        return;
      }
      if (state == '1') {
        cells_[i].setState('1');
      } else {
        cells_[i].setState('0');
      }
      ++i;
    }
    file.close();
  } else {
    // Configuración inicial por defecto (célula central en estado '1')
    cells_[getSize() / 2].setState('1');
  }
}

void Lattice::nextGeneration() {
  // En el primer recorrido cada célula accede a su vecindad y aplica la función de transición para calcular su estado siguiente.
  for (int i = 0; i < getSize(); ++i) {
    cells_[i].nextState(*this);
  }
  // En el segundo recorrido cada célula actualiza su estado.
  for (int i = 0; i < getSize(); ++i) {
    cells_[i].updateState();
  }
}

std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  // Implementa la sobrecarga del operador de inserción para mostrar el retículo
  for (int i = 0; i < lattice.getSize(); ++i) {
    os << lattice.cells_[i];
  }
  os << std::endl;
  return os;
}

// Función main
int main(int argc, char* argv[]) {
  int size = 0;
  std::string borderType = "open";
  State borderValue = '0';
  std::string fileName = "";
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-size") {
      size = std::atoi(argv[i + 1]);
    } else if (std::string(argv[i]) == "-border") {
      borderType = argv[i + 1];
      borderValue = argv[i + 2][0];
    } else if (std::string(argv[i]) == "-init") {
      fileName = argv[i + 1];
    }
  }
  if (size <= 0 || (borderType != "open" && borderType != "periodic")) {
    std::cerr << "Error: Argumentos incorrectos." << std::endl;
    return 1;
  }
  Lattice lattice(size);
  lattice.loadInitialConfiguration(fileName, borderType, borderValue);
  // Simula la evolución del autómata celular
  char stopChar;
  do {
    std::cout << lattice; // Muestra el retículo
    lattice.nextGeneration(); // Evoluciona a la siguiente generación
    std::cout << "Presiona 'q' para detener la simulación, o cualquier otra tecla para continuar: ";
    std::cin >> stopChar;
  } while (stopChar != 'q');
  return 0;
}
