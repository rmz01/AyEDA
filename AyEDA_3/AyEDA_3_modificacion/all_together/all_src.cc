#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "all_headers.h"

std::ostream& operator<<(std::ostream& os, Cell& cell) {
  cell.display(os);
  return os;
}

// Clase ACE 110 --------------------------------------------------------------------------------

void CellACE110::updateState() {
  state_ = nextState_;
}


void CellACE110::display(std::ostream& os) {
  if (state_ == '0') {
    os << "-";
  } else {
    os << "X";
  }
}


void CellACE110::nextState(const Lattice& reticulo) {
  const State C = state_;
  State next_state{0};

  int position = position_[0];

  Position* Left = new PositionDim<1>(1, position - 1);
  Position* Right = new PositionDim<1>(1, position + 1);

  State L = reticulo[*Left].getState();
  State R = reticulo[*Right].getState();

  next_state = (C + R + C * R + L * C * R) % 2;
  if (next_state == 0) {
    nextState_ = '0';
  } else {
    nextState_ = '1';
  }
}

// Clase ACE 30 --------------------------------------------------------------------------------

void CellACE30::updateState() {
  state_ = nextState_;
}


void CellACE30::display(std::ostream& os) {
  if (state_ == '0') {
    os << "-";
  } else {
    os << "X";
  }
}


void CellACE30::nextState(const Lattice& reticulo) {
  const State C = state_;
  State next_state{0};

  int position = position_[0];

  Position* Left = new PositionDim<1>(1, position - 1);
  Position* Right = new PositionDim<1>(1, position + 1);

  State L = reticulo[*Left].getState();
  State R = reticulo[*Right].getState();

  next_state = (L + C + R + C * R) % 2;
  if (next_state == 0) {
    nextState_ = '0';
  } else {
    nextState_ = '1';
  }
}


// Clase Life 23_3 --------------------------------------------------------------------------------

void CellLife23_3::updateState() {
  state_ = nextState_;
}


void CellLife23_3::display(std::ostream& os) {
  if (state_ == '0') {
    os << "-";
  } else {
    os << "X";
  }
}


void CellLife23_3::nextState(const Lattice& reticulo) {
  int alive_neighbours{0};
  State next_state;

  const State C = state_;

  int position_x = position_[1];
  int position_y = position_[0];

  Position* aux_pos;
  aux_pos = new PositionDim<2>(2, position_x + 1, position_y);
  State E = reticulo[*aux_pos].getState();
  if (E == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x - 1, position_y);
  State W = reticulo[*aux_pos].getState();
  if (W == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x, position_y + 1);
  State S = reticulo[*aux_pos].getState();
  if (S == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x, position_y - 1);
  State N = reticulo[*aux_pos].getState();
  if (N == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x + 1, position_y + 1);
  State SE = reticulo[*aux_pos].getState();
  if (SE == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x - 1, position_y - 1);
  State NW = reticulo[*aux_pos].getState();
  if (NW == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x + 1, position_y - 1);
  State NE = reticulo[*aux_pos].getState();
  if (NE == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x - 1, position_y + 1);
  State SW = reticulo[*aux_pos].getState();
  if (SW == '1') alive_neighbours++;
  

  if (C == '0') {
    if (alive_neighbours == 3) {
      next_state = '1';
    } else {
      next_state = '0';
    }
  } else {
    if (alive_neighbours == 2 || alive_neighbours == 3) {
      next_state = '1';
    } else {
      next_state = '0';
    }
  }
  nextState_ = next_state;
}

// Clase Life 51_346 --------------------------------------------------------------------------------

void CellLife51_346::updateState() {
  state_ = nextState_;
}


void CellLife51_346::display(std::ostream& os) {
  if (state_ == '0') {
    os << "-";
  } else {
    os << "X";
  }
}


void CellLife51_346::nextState(const Lattice& reticulo) {
  int alive_neighbours{0};
  State next_state;

  const State C = state_;

  int position_x = position_[1];
  int position_y = position_[0];

  Position* aux_pos;
  aux_pos = new PositionDim<2>(2, position_x + 1, position_y);
  State E = reticulo[*aux_pos].getState();
  if (E == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x - 1, position_y);
  State W = reticulo[*aux_pos].getState();
  if (W == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x, position_y + 1);
  State S = reticulo[*aux_pos].getState();
  if (S == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x, position_y - 1);
  State N = reticulo[*aux_pos].getState();
  if (N == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x + 1, position_y + 1);
  State SE = reticulo[*aux_pos].getState();
  if (SE == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x - 1, position_y - 1);
  State NW = reticulo[*aux_pos].getState();
  if (NW == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x + 1, position_y - 1);
  State NE = reticulo[*aux_pos].getState();
  if (NE == '1') alive_neighbours++;
  aux_pos = new PositionDim<2>(2, position_x - 1, position_y + 1);
  State SW = reticulo[*aux_pos].getState();
  if (SW == '1') alive_neighbours++;

  if (C == '0') {
    if (alive_neighbours == 3 || alive_neighbours == 4 || alive_neighbours == 6) {
      next_state = '1';
    } else {
      next_state = '0';
    }
  } else {
    if (alive_neighbours == 5 || alive_neighbours == 1) {
      next_state = '1';
    } else {
      next_state = '0';
    }
  }
  nextState_ = next_state;
}

std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  lattice.display(os);
  return os;
}

std::ofstream& operator<<(std::ofstream& os, const Lattice& lattice) {
  lattice.displayfile(os);
  return os;
}

// CLase 1D --------------------------------------------------------------------------------

Lattice1D::Lattice1D(const int& size, FactoryCell& factory) {
  size_ = size;
  lattice_.resize(size);
  Position* pos;
  for (int i = 0; i < size; i++) {
    pos = new PositionDim<1>(1, i);
    lattice_[i] = factory.createCell(*pos, '0');
  }
  for (int i{0}; i < size; ++i) {
    std::cout << "Introduce el estado de la pos: " << i << std::endl;
    unsigned char state;
    std::cin >> state;
    lattice_[i]->setState(state);
  }
}

Lattice1D::Lattice1D(std::fstream& file, FactoryCell& factory) {
  char dimension;
  file >> dimension;
  std::cout << "Dimension: " << dimension << std::endl;

  file >> size_;
  lattice_.resize(size_);
  Position* pos;
  State state;

  std::string line;
  std::getline(file, line);
  std::getline(file, line);
  for (int i = 0; i < size_; i++) {
    pos = new PositionDim<1>(1, i);
    state = line[i];
    lattice_[i] = factory.createCell(*pos, state);
  }
}

Lattice1D::~Lattice1D() {
  std::cout << "Destructor" << std::endl;
  for (int i = 0; i < size_; i++) {
    delete lattice_[i];
  }
}

void Lattice1D::nextGeneration() {
  for (int i = 0; i < size_; i++) {
    lattice_[i]->nextState(*this);
  }
  for (int i = 0; i < size_; i++) {
    lattice_[i]->updateState();
  }
}

std::size_t Lattice1D::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < size_; i++) {
    if (lattice_[i]->getState() == '1') {
      population++;
    }
  }
  return population;
}

std::ostream& Lattice1D::display(std::ostream& os) const {
  for (int i = 0; i < size_; i++) {
    os << *lattice_[i];
  }
  os << std::endl;
  return os;
}

std::ofstream& Lattice1D::displayfile(std::ofstream& os) const {
  os << 1 << std::endl;
  os << size_ << std::endl;
  for (int i = 0; i < size_; i++) {
    os << *lattice_[i];
  }
  os << std::endl;
  return os;
}

// Clase open --------------------------------------------------------------------------------

Lattice1D_open::Lattice1D_open(const int& size, FactoryCell& factory, bool open_type) : Lattice1D(size, factory), open_type_(open_type) {
  Position* position;
  if (open_type_ == 0) {
    position = new PositionDim<1>(1, -1);
    border_ = factory.createCell(*position, '0');
  } else {
    position = new PositionDim<1>(1, -1);
    border_ = factory.createCell(*position, '1');
  }
}


Lattice1D_open::Lattice1D_open(std::fstream& file, FactoryCell& factory, bool open_type) : Lattice1D(file, factory), open_type_(open_type) {
  Position* position;
  if (open_type_ == 0) {
    position = new PositionDim<1>(1, -1);
    border_ = factory.createCell(*position, '0');
  } else {
    position = new PositionDim<1>(1, -1);
    border_ = factory.createCell(*position, '1');
  }
}


Lattice1D_open::~Lattice1D_open() {
  delete border_;
}


Cell& Lattice1D_open::operator[](Position& position) const {
  int pos = position[0];
  if (pos < 0 || pos >= size_) {
    return *border_;
  } else {
    return *lattice_[pos];
  }
}

// Clase periodic --------------------------------------------------------------------------------

Cell& Lattice1D_periodic::operator[](Position& position) const {
  int pos = position[0];
  if (pos < 0) {
    pos = size_-1;
  } else if (pos >= size_) {
    pos = 0;
  }
  return *lattice_[pos];
}

// Resuelve un mensaje de advertencia que indica un problema potencial con el tipo de dato int usado en una
// comparación. std::vector::size() devuelve un tipo size_type, que es un tipo entero sin signo (unsigned). 
using MatrixOfCells = std::vector<std::vector<Cell*>>;

// Clase 2D --------------------------------------------------------------------------------

Lattice2D::Lattice2D(std::fstream& file, FactoryCell& factory) {
    // line 1: dimension (must be 2)
    // line 2: number of rows
    // line 3: number of columns
  int dimension;
  file >> dimension;
  if (dimension != 2) {
    throw std::invalid_argument("Dimension must be 2");
  }
  int rows;
  file >> rows;
  int columns;
  file >> columns;
  lattice_.resize(rows);
  for (int i = 0; i < rows; i++) {
    lattice_[i].resize(columns);
  }

  State state;
  std::string line;
  std::getline(file, line);
  for (int i = 0; i < rows; i++) {
    std::getline(file, line);
    for (int j = 0; j < columns; j++) {
      state = line[j];
      Position* position = new PositionDim<2>(2, i, j);
      lattice_[i][j] = factory.createCell(*position, state);
    }
  }
  rows_ = rows;
  columns_ = columns;
}

Lattice2D::Lattice2D(const int& rows, const int& columns, FactoryCell& factory) {
  lattice_.resize(rows);
  for (int i = 0; i < rows; i++) {
    lattice_[i].resize(columns);
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      Position* position = new PositionDim<2>(2, i, j);
      lattice_[i][j] = factory.createCell(*position, '0');
    }
  }
  rows_ = rows;
  columns_ = columns;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      std::cout << "Introudce el estado de la celda (" << i << ", " << j << "): ";
      unsigned char state;
      std::cin >> state;
      lattice_[i][j]->setState(state);
    }
  }
}

Lattice2D::~Lattice2D() {
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      delete lattice_[i][j];
    }
  }
}

void Lattice2D::nextGeneration() {
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      lattice_[i][j]->nextState(*this);
    }
  }
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      lattice_[i][j]->updateState();
    }
  }
}

std::size_t Lattice2D::Population() const {
  std::size_t population = 0;
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      if (lattice_[i][j]->getState() == '1') {
        population++;
      }
    }
  }
  return population;
}

std::ostream& Lattice2D::display(std::ostream& os) const {
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      os << *lattice_[i][j];
    }
    os << std::endl;
  }
  return os;
}

std::ofstream& Lattice2D::displayfile(std::ofstream& os) const {
  os << 2 << std::endl;
  os << rows_ << std::endl;
  os << columns_ << std::endl;
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      os << *lattice_[i][j];
    }
    os << std::endl;
  }
  return os;
}

// Clase reflective --------------------------------------------------------------------------------


Cell& Lattice2D_reflective::operator[](Position& position) const {
  std::vector<Cell*>::size_type x = position[0];
  std::vector<Cell*>::size_type y = position[1];

  if ( x < 0 || y < 0 || x > lattice_[0].size()-1 || y > lattice_.size()-1) {
    if (x < 0) {
      x = 0;
      if (y < 0) {
        y = 0;
      } else if (y > lattice_.size()-1) {
        y = lattice_.size()-1;
      }
    }
    if (x > lattice_[0].size()-1) {
      x = lattice_[0].size()-1;
      if (y < 0) {
        y = 0;
      } else if (y > lattice_.size()-1) {
        y = lattice_.size()-1;
      }
    }
    if (y < 0) {
      y = 0;
      if (x < 0) {
        x = 0;
      } else if (x > lattice_[0].size()-1) {
        x = lattice_[0].size()-1;
      }
    }
    if (y > lattice_.size()-1) {
      y = lattice_.size()-1;
      if (x < 0) {
        x = 0;
      } else if (x > lattice_[0].size()-1) {
        x = lattice_[0].size()-1;
      }
    }
  }
  return *lattice_[y][x];
}


struct parameters {
  int dimension;
  bool two_dim = false;
  int size_x;
  int size_y;
  int cell_type; // 0: Ace110, 1: Ace30, 2: Life23_3, 3: Life51_346
  int border; // 0: open, 1: periodic, 2: reflective, 3: no border
  bool open_type = false;
  std::fstream filename;
  bool initial_file = false;
};

int main(int argc, char *argv[]) {
  // Tipo de parametros
  std::vector<std::string> args(argv + 1, argv + argc);
  parameters options;
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-dim") {
      options.dimension = std::stoi(*++it);
      if (options.dimension == 2) {
        options.two_dim = true;
      }
    }
    else if (*it == "-cell") {
      if (*++it == "Ace110") {
        options.cell_type = 0;
      } else if (*it == "Ace30") {
        options.cell_type = 1;
      } else if (*it == "Life23_3") {
        options.cell_type = 2;
      } else if (*it == "Life51_346") {
        options.cell_type = 3;
      }
    }
    else if (*it == "-size") {
      options.size_x = std::stoi(*++it);
      if (options.two_dim) options.size_y = std::stoi(*++it);
    } else if (*it == "-border") {
        if (*++it == "open") {
          options.border = 0;
          if (*++it == "1") {
            options.open_type = true;
          }
        } else if (*it == "periodic") {
          options.border = 1;
        } else if (*it == "reflective") {
          options.border = 2;
        } else if (*it == "noborder") {
          options.border = 3;
        }
    } else if (*it == "-init") {
      options.filename = std::fstream(*++it);
      options.initial_file = true;
    }
    else {
      std::cerr << "Error: argumento no válido" << std::endl;
    }
  }

  std::cout << "Menu:" << std::endl << "'x' to exit.\n's' to save configuration.\n'n' to show next generation.\n";
  std::cout << "'L' to show next 5 generations.\n'c' to show population.\n";

  // Creacion del tipo de celula
  FactoryCell* factory;
  switch(options.cell_type) {
    case 0:
      factory = new FactoryCellACE110();
      break;
    case 1:
      factory = new FactoryCellACE30();
      break;
    case 2:
      factory = new FactoryCellLife23_3();
      break;
    case 3:
      factory = new FactoryCellLife51_346();
      break;
  }

  // Creacion del tipo de borde
  Lattice* lattice;
  switch(options.border) {
    case 0:
      if (options.initial_file) {
        lattice = new Lattice1D_open(options.filename, *factory, options.open_type);
      } else {
        lattice = new Lattice1D_open(options.size_x, *factory, options.open_type);
      }
      break;
    case 1:
      if (options.initial_file) {
        lattice = new Lattice1D_periodic(options.filename, *factory);
      } else {
        lattice = new Lattice1D_periodic(options.size_x, *factory);
      }
      break;
    case 2:
      if (options.initial_file) {
        lattice = new Lattice2D_reflective(options.filename, *factory);
      } else {
        lattice = new Lattice2D_reflective(options.size_x, options.size_y, *factory);
      }
      break;
    case 3:
      if (options.initial_file) {
        // lattice = new Lattice2D_NoBorder(options.filename, *factory);
        lattice = new Lattice2D_reflective(options.filename, *factory);
      } else {
        // lattice = new Lattice2D_NoBorder(options.size_x, options.size_y, *factory);
        lattice = new Lattice2D_reflective(options.size_x, options.size_y, *factory);
      }
      break;
  }
  
  // Menu
  std::cout << *lattice << std::endl;
  bool population = false;
  bool running = true;
  char stop;
  while(running) {
    std::cin >> stop;
    switch (stop) {
      case 'x':
        running = false;
        break;
      case 'n': // Calcula y muestra la siguiente generación
        lattice->nextGeneration();
        if (population) {
          std::cout << lattice->Population() << std::endl;
        } else {
            std::cout << *lattice << std::endl;
          }
        break;
      case 'L': // Calcula y muestra las siguientes 5 generaciones
        for (int i = 0; i < 5; i++) {
          lattice->nextGeneration();
          if (population) {
            std::cout << lattice->Population() << std::endl;
          } else {
              std::cout << *lattice << std::endl;
            }
        }
        break;
      case 'c': // Se muestra la población (número de células vivas) actual
        population = (population) ? false : true;
        break;
      case 's': // Guarda la configuración actual en un fichero
        std::string file_name;
        std::cin >> file_name;
        std::ofstream output_file{file_name};
        output_file << *lattice;
        output_file.close();
        break;
    }
  }

  return 0;
}