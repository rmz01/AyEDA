#include "../include/lattice1D.h"
#include "../include/position.h"
#include "../include/factorycell.h"

// CLase 1D --------------------------------------------------------------------------------

/**
 * @brief Constructor de la clase Lattice1D.
 * 
 * @param size El tamaño del retículo.
 * @param factory La fábrica de celdas que se utilizará para crear las celdas del retículo.
 */
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

/**
 * @brief Constructor de la clase Lattice1D que lee el estado inicial del retículo de un archivo.
 * 
 * @param file El archivo del que se leerá el estado inicial del retículo.
 * @param factory La fábrica de celdas que se utilizará para crear las celdas del retículo.
 */
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

/**
 * @brief Destructor de la clase Lattice1D.
 */
Lattice1D::~Lattice1D() {
  std::cout << "Destructor" << std::endl;
  for (int i = 0; i < size_; i++) {
    delete lattice_[i];
  }
}

/**
 * @brief Actualiza el retículo a la siguiente generación.
 */
void Lattice1D::nextGeneration() {
  for (int i = 0; i < size_; i++) {
    lattice_[i]->nextState(*this);
  }
  for (int i = 0; i < size_; i++) {
    lattice_[i]->updateState();
  }
}

/**
 * @brief Calcula la población del retículo, es decir, el número de celdas en estado '1'.
 * 
 * @return El número de celdas en estado '1'.
 */
std::size_t Lattice1D::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < size_; i++) {
    if (lattice_[i]->getState() == '1') {
      population++;
    }
  }
  return population;
}

/**
 * @brief Calcula la población del retículo, es decir, el número de celdas en estado '1'.
 * 
 * @return El número de celdas en estado '1'.
 */
std::ostream& Lattice1D::display(std::ostream& os) const {
  for (int i = 0; i < size_; i++) {
    os << *lattice_[i];
  }
  os << std::endl;
  return os;
}

/**
 * @brief Imprime una representación del retículo en el archivo de salida proporcionado.
 * 
 * @param os El archivo de salida en el que se imprimirá el retículo.
 * @return El archivo de salida modificado.
 */
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

/**
 * @brief Constructor de la clase Lattice1D_open.
 * 
 * @param size El tamaño del retículo.
 * @param factory La fábrica de celdas que se utilizará para crear las celdas del retículo.
 * @param open_type El tipo de borde abierto.
 */
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

/**
 * @brief Constructor de la clase Lattice1D_open que lee el estado inicial del retículo de un archivo.
 * 
 * @param file El archivo del que se leerá el estado inicial del retículo.
 * @param factory La fábrica de celdas que se utilizará para crear las celdas del retículo.
 * @param open_type El tipo de borde abierto.
 */
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

/**
 * @brief Destructor de la clase Lattice1D_open.
 */
Lattice1D_open::~Lattice1D_open() {
  delete border_;
}

/**
 * @brief Sobrecarga del operador de indexación para la clase Lattice1D_open.
 * 
 * @param position La posición de la celda que se quiere acceder.
 * @return La celda en la posición especificada.
 */
Cell& Lattice1D_open::operator[](Position& position) const {
  int pos = position[0];
  if (pos < 0 || pos >= size_) {
    return *border_;
  } else {
    return *lattice_[pos];
  }
}

// Clase periodic --------------------------------------------------------------------------------

/**
 * @brief Sobrecarga del operador de indexación para la clase Lattice1D_periodic.
 * 
 * @param position La posición de la celda que se quiere acceder.
 * @return La celda en la posición especificada.
 */
Cell& Lattice1D_periodic::operator[](Position& position) const {
  int pos = position[0];
  if (pos < 0) {
    pos = size_-1;
  } else if (pos >= size_) {
    pos = 0;
  }
  return *lattice_[pos];
}