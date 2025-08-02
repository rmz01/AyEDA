#include "lattice.h"

// utilizo size_t en vez de int porque comparar un número con signo con un número sin 
// signo puede llevar a resultados inesperados si el número con signo es negativo.

// Constructor
Lattice::Lattice(int size) {
  // El constructor del retículo crea las células en memoria dinámica.
  size_ = size;
  cells_.resize(size, Cell());
  for (int i = 0; i < getSize(); ++i) {
    cells_[i] = Cell(i);
  }
}

// Metodo para cargar la configuración inicial
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

// Implementa la lógica de evolución
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

// Sobrecarga del operador de inserción
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  // Implementa la sobrecarga del operador de inserción para mostrar el retículo
  for (int i = 0; i < lattice.getSize(); ++i) {
    os << lattice.cells_[i];
  }
  os << std::endl;
  return os;
}