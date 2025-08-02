#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

// Definición de tipos
using State = unsigned char;
using Position = std::pair<int, int>;

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
  void setPosition(Position newPosition) { position_ = newPosition; }
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
  Lattice(int rows, int cols);
  Lattice(const std::string& fileName);

  // Destructor
  ~Lattice();

  // Getters
  const Cell& getCell(const Position& pos) const;
  int getRows() const { return rows_; }
  int getCols() const { return cols_; }
  std::string getBorderType() const { return border_type_; }
  std::size_t Population() const;

  // Setters
  void setBorderType(const std::string& borderType) { border_type_ = borderType; }

  // Metodo para cargar la configuración inicial
  void loadInitialConfiguration(const std::string& fileName);

  // Guarda el estado actual en un archivo
  void saveToFile(const std::string& fileName) const;

  // Implementa la lógica de evolución
  void nextGeneration();

  // Sobrecarga del operador de inserción
  friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);

  // Sobrecarga del operador de acceso
  Cell& operator[](const Position& pos) const;

 private:
  std::vector<std::vector<Cell*>> cells_;
  int rows_;
  int cols_;
  std::string border_type_;
};

// Definiciones de métodos de Cell

Cell::Cell() : position_(std::make_pair(0, 0)), state_('0'), nextState_('0') {}

Cell::Cell(const Position& pos, const State& st) : position_(pos), state_(st), nextState_('0') {}

State Cell::setState(State newState) {
  state_ = newState;
  return state_;
}

void Cell::updateState() { state_ = nextState_; }

int Cell::nextState(const Lattice& lattice) {
  int live_neighbors = 0;
  std::string border_type = lattice.getBorderType();

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) continue; // Skip the cell itself

      Position neighbor(position_.first + i, position_.second + j);
      State neighbor_state;

      if (border_type == "reflective") {
        if (neighbor.first < 0 || neighbor.first >= lattice.getRows() || neighbor.second < 0 || neighbor.second >= lattice.getCols()) {
          neighbor_state = state_;
        } else {
          neighbor_state = lattice.getCell(neighbor).getState();
        }
      } 
      if (border_type == "noborder") {
        if (neighbor.first < 0 || neighbor.first >= lattice.getRows() || neighbor.second < 0 || neighbor.second >= lattice.getCols()) {
          neighbor_state = '0'; // Consider out-of-bounds cells as dead
        } else {
          neighbor_state = lattice.getCell(neighbor).getState();
        }
      }

      live_neighbors += (neighbor_state == '1' ? 1 : 0);
    }
  }
// Modificacion de las reglas del juego pasando de la 23/3 a la 35/234
  if (state_ == '1' && (live_neighbors == 3 || live_neighbors == 5)) {
    nextState_ = '1';
  } else if (state_ == '0' && (live_neighbors == 2 || live_neighbors == 3 || live_neighbors == 4)) {
    nextState_ = '1';
  } else {
    nextState_ = '0';
  }
  return nextState_;
}


std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << (cell.getState() == '1' ? 'X' : '-');
  return os;
}

// Definiciones de métodos de Lattice

Lattice::Lattice(int rows, int cols) : rows_(rows), cols_(cols) {
  cells_.resize(rows, std::vector<Cell*>(cols, nullptr));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells_[i][j] = new Cell(std::make_pair(i, j));
    }
  }
}

Lattice::Lattice(const std::string& fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
    return;
  }
  file >> rows_ >> cols_;
  cells_.resize(rows_, std::vector<Cell*>(cols_, nullptr));
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      cells_[i][j] = new Cell(std::make_pair(i, j));
      char state;
      file >> state;
      if (state == '1') {
        cells_[i][j]->setState('1');
      } else {
        cells_[i][j]->setState('0');
      }
    }
  }
  file.close();
}

Lattice::~Lattice() {
  for (auto& row : cells_) {
    for (auto& cell : row) {
      delete cell;
    }
  }
}

const Cell& Lattice::getCell(const Position& pos) const {
  int x = pos.first;
  int y = pos.second;
  return *cells_[x][y];
}

void Lattice::nextGeneration() {
  // Calculate the next state for each cell
  for (auto& row : cells_) {
    for (auto& cell : row) {
      cell->nextState(*this);
    }
  }
  if (border_type_ == "noborder") {
  // Check if any border cell is alive
  bool topRowAlive = false, bottomRowAlive = false, leftColumnAlive = false, rightColumnAlive = false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (cells_[i][j]->getState() == '1') {
        if (i == 0) topRowAlive = true;
        if (i == rows_ - 1) bottomRowAlive = true;
        if (j == 0) leftColumnAlive = true;
        if (j == cols_ - 1) rightColumnAlive = true;
      }
    }
  }

  // Add new row/column if necessary
  if (topRowAlive) {
    cells_.insert(cells_.begin(), std::vector<Cell*>(cols_, nullptr));
    for (int j = 0; j < cols_; ++j) {
      cells_[0][j] = new Cell(std::make_pair(0, j), '0');
    }
    ++rows_;
  }
  if (bottomRowAlive) {
    cells_.push_back(std::vector<Cell*>(cols_, nullptr));
    for (int j = 0; j < cols_; ++j) {
      cells_[rows_][j] = new Cell(std::make_pair(rows_, j), '0');
    }
    ++rows_;
  }
  if (leftColumnAlive) {
    for (auto& row : cells_) {
      row.insert(row.begin(), new Cell(std::make_pair(row[0]->getPosition().first, 0), '0'));
    }
    ++cols_;
  }
  if (rightColumnAlive) {
    for (auto& row : cells_) {
      row.push_back(new Cell(std::make_pair(row[0]->getPosition().first, cols_), '0'));
    }
    ++cols_;
  }
  }

  // Update the state of each cell
  for (auto& row : cells_) {
    for (auto& cell : row) {
      cell->updateState();
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (const auto& row : lattice.cells_) {
    for (const auto& cell : row) {
      os << *cell;
    }
    os << std::endl;
  }
  return os;
}

Cell& Lattice::operator[](const Position& pos) const {
  int row = pos.first;
  int col = pos.second;
  if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
    return *cells_[row][col];
  } else {
    throw std::out_of_range("Position out of range");
  }
}

std::size_t Lattice::Population() const {
  std::size_t population = 0;
  for (const auto& row : cells_) {
    for (const auto& cell : row) {
      if (cell->getState() == '1') {
        ++population;
      }
    }
  }
  return population;
}

void Lattice::saveToFile(const std::string& fileName) const {
  std::ofstream file(fileName);
  if (!file) {
    std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
    return;
  }
  file << rows_ << " " << cols_ << "\n";
  for (const auto& row : cells_) {
    for (const auto& cell : row) {
      file << (cell->getState() == '1' ? '1' : '0') << " ";
    }
    file << "\n";
  }
  file.close();
}

// Función main

int main(int argc, char* argv[]) {
  std::string fileName;
  std::string borderType;
  int rows = 0, cols = 0;


  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-init" && i + 1 < argc) {
      fileName = argv[++i];
    } else if (arg == "-border" && i + 1 < argc) {
      borderType = argv[++i];
    } else if (arg == "-size" && i + 2 < argc) {
      rows = std::stoi(argv[++i]);
      cols = std::stoi(argv[++i]);
    } else {
      std::cerr << "Uso: " << argv[0] << " -init [fichero] -border [borderType] -size [M] [N]\n";
      return 1;
    }
  }

  if (borderType.empty()) {
    std::cerr << "Debe proporcionar -border\n";
    return 1;
  }

  // Inicializa el autómata celular con un retículo cargado desde un archivo
  if (!fileName.empty()) {
    Lattice lattice(fileName);
    lattice.setBorderType(borderType);
    // Simula la evolución del autómata celular
  std::cout << lattice; // Muestra el retículo
  char command;
  do {
    std::cout << "Comando: ";
    std::cin >> command;
    switch (command) {
      case 'x':
        return 0;
      case 'n':
        lattice.nextGeneration();
        std::cout << lattice << std::endl;
        break;
      case 'L':
        for (int i = 0; i < 5; ++i) {
          lattice.nextGeneration();
          std::cout << lattice << std::endl;
        }
        break;
      case 'c':
        std::cout << "Población: " << lattice.Population() << std::endl;
        break;
      case 's':  {
        std::string fileName;
        std::cout << "Nombre del archivo: ";
        std::cin >> fileName;
        lattice.saveToFile(fileName);
        break;
      }
        break;
    }
  } while (true);

    // Inicializa el autómata celular con un retículo de tamaño MxN
    } else if (rows > 0 && cols > 0) {
      Lattice lattice(rows, cols);
      lattice.setBorderType(borderType);
      int numCells;
      std::cout << "¿Cuántas células vivas desea inicializar? ";
      std::cin >> numCells;
      for (int i = 0; i < numCells; ++i) {
        int row, col;
        std::cout << "Introduzca las coordenadas de la célula viva " << i + 1 << " (fila columna): ";
        std::cin >> row >> col;
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
          lattice[Position(row, col)].setState('1');
        } else {
          std::cerr << "Las coordenadas están fuera de rango. Inténtalo de nuevo.\n";
          --i;
        }
      }
  // Simula la evolución del autómata celular
  std::cout << lattice; // Muestra el retículo
  char command;
  do {
    std::cout << "Comando: ";
    std::cin >> command;
    switch (command) {
      case 'x':
        return 0;
      case 'n':
        lattice.nextGeneration();
        std::cout << lattice << std::endl;
        break;
      case 'L':
        for (int i = 0; i < 5; ++i) {
          lattice.nextGeneration();
          std::cout << lattice << std::endl;
        }
        break;
      case 'c':
        std::cout << "Población: " << lattice.Population() << std::endl;
        break;
      case 's':  {
        std::string fileName;
        std::cout << "Nombre del archivo: ";
        std::cin >> fileName;
        lattice.saveToFile(fileName);
        break;
      }
        break;
    }
  } while (true);
  // Si no se proporciona un archivo o un tamaño, se muestra un mensaje de error
    } else {
      std::cerr << "Debe proporcionar -init o -size\n";
      return 1;
    }
  return 0;
}