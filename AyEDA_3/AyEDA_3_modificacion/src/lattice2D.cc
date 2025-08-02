#include "../include/lattice2D.h"
#include "../include/factorycell.h"
#include "../include/cell.h"
#include "../include/position.h"

// Resuelve un mensaje de advertencia que indica un problema potencial con el tipo de dato int usado en una
// comparación. std::vector::size() devuelve un tipo size_type, que es un tipo entero sin signo (unsigned). 
using MatrixOfCells = std::vector<std::vector<Cell*>>;

// Clase 2D --------------------------------------------------------------------------------

/**
 * @brief Constructor de la clase Lattice2D que lee el estado inicial del retículo de un archivo.
 * 
 * @param file El archivo del que se leerá el estado inicial del retículo.
 * @param factory La fábrica de celdas que se utilizará para crear las celdas del retículo.
 */
Lattice2D::Lattice2D(std::fstream& file, FactoryCell& factory) {
    // line 1: dimension que debe ser 2
    // line 2: number of rows
    // line 3: number of columns
  int dimension;
  file >> dimension;
  if (dimension != 2) {
    throw std::invalid_argument("Dimension debe ser 2");
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

/**
 * @brief Constructor de la clase Lattice2D.
 * 
 * @param rows El número de filas del retículo.
 * @param columns El número de columnas del retículo.
 * @param factory La fábrica de celdas que se utilizará para crear las celdas del retículo.
 */
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

/**
 * @brief Destructor de la clase Lattice2D.
 */
Lattice2D::~Lattice2D() {
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      delete lattice_[i][j];
    }
  }
}

/**
 * @brief Actualiza el retículo a la siguiente generación.
 */
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

/**
 * @brief Calcula la población del retículo, es decir, el número de celdas en estado '1'.
 * 
 * @return El número de celdas en estado '1'.
 */
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

/**
 * @brief Imprime una representación del retículo en el flujo de salida proporcionado.
 * 
 * @param os El flujo de salida en el que se imprimirá el retículo.
 * @return El flujo de salida modificado.
 */
std::ostream& Lattice2D::display(std::ostream& os) const {
  for (MatrixOfCells::size_type i = 0; i < lattice_.size(); i++) {
    for (MatrixOfCells::size_type j = 0; j < lattice_[i].size(); j++) {
      os << *lattice_[i][j];
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief Imprime una representación del retículo en el archivo de salida proporcionado.
 * 
 * @param os El archivo de salida en el que se imprimirá el retículo.
 * @return El archivo de salida modificado.
 */
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

/**
 * @brief Sobrecarga del operador de indexación para la clase Lattice2D_reflective.
 * 
 * @param position La posición de la celda que se quiere acceder.
 * @return La celda en la posición especificada.
 */
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

/* Clase NoBorder --------------------------------------------------------------------------------


Cell& Lattice2D_NoBorder::operator[](Position& position) const {
  int x = position[0];
  int y = position[1];

  if ( x < lattice_[0].negative_index()+1 || y < lattice_.negative_index()+1 ) {
    return *lattice_[0][0];
  }
  if ( x > (lattice_[0].size()+lattice_[0].negative_index()) && x >= 0) {
    return *lattice_[0][0];
  }
  if ( y > (lattice_.size()+lattice_.negative_index()) && y >= 0) {
    return *lattice_[0][0];
  }
  return *lattice_[y-(lattice_.negative_index()+1)][x+(-(lattice_[0].negative_index()+1))];
}


void Lattice2D_NoBorder::nextGeneration() {
  CheckBorder();

  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[0].size(); j++) {
      lattice_[i][j]->nextState(*this);
    }
  }

  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[0].size(); j++) {
      lattice_[i][j]->updateState();
    }
  }

  CheckBorder();
}


void Lattice2D_NoBorder::CheckBorder() {
  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[0].size(); j++) {
      if (i == 0 && lattice_[i][j]->getState() == '1') {
        IncrementSize('N');
      }
      if (i == lattice_.size()-1 && lattice_[i][j]->getState() == '1') {
        IncrementSize('S');
      }
      if (j == 0 && lattice_[i][j]->getState() == '1') {
        IncrementSize('W');
      }
      if (j == lattice_[0].size()-1 && lattice_[i][j]->getState() == '1') {
        IncrementSize('E');
      }
    }
  }
}


void Lattice2D_NoBorder::IncrementSize(char direction) {
  Position* new_position;
  std::vector<Cell*> new_row;
  switch (direction) {
    case 'E':
      for (int i{0}; i < lattice_.size(); ++i) {
        new_position = new PositionDim<2>(2, i+(lattice_.negative_index()+1), lattice_[i].size()-(-(lattice_[i].negative_index()+1)));
        lattice_[i].push_back(factory_->createCell(*new_position, '0'));
      }
      columns_++;
      break;
    case 'W':
      for (int i{0}; i < lattice_.size(); ++i) {
        new_position = new PositionDim<2>(2, i+(lattice_.negative_index()+1), lattice_[i].negative_index());
        lattice_[i].push_front(factory_->createCell(*new_position, '0'));
        lattice_[i].DecrementNegativeIndex();
      }
      columns_++;
      break;
    case 'N':
      new_row.resize(lattice_[0].size());
      new_row.SetNegativeIndex(lattice_[0].negative_index());
      for (int i{0}; i < lattice_[0].size(); ++i) {
        new_position = new PositionDim<2>(2, lattice_.negative_index(), i+(lattice_[0].negative_index()+1));
        new_row[i] = factory_->createCell(*new_position, '0');
      }
      lattice_.push_front(new_row);
      lattice_.DecrementNegativeIndex();
      rows_++;
      break;
    case 'S':
      new_row.resize(lattice_[0].size());
      new_row.SetNegativeIndex(lattice_[0].negative_index());
      for (int i{0}; i < lattice_[0].size(); ++i) {
        new_position = new PositionDim<2>(2, lattice_.size()-(-(lattice_.negative_index()+1)), i+(lattice_[0].negative_index()+1));
        new_row[i] = factory_->createCell(*new_position, '0');
      }
      lattice_.push_back(new_row);
      rows_++;
      break;
  }
}

*/