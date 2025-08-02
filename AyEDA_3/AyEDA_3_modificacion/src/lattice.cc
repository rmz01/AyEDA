#include "../include/lattice.h"

/**
 * @brief Sobrecarga del operador de inserción para la clase Lattice. (Normal)
 * 
 * @param os El flujo de salida en el que se imprimirá el retículo.
 * @param lattice El retículo que se imprimirá en el flujo de salida.
 * @return El flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  lattice.display(os);
  return os;
}

/**
 * @brief Sobrecarga del operador de inserción para la clase Lattice. (Fichero)
 * 
 * @param os El flujo de archivo de salida en el que se imprimirá el retículo.
 * @param lattice El retículo que se imprimirá en el flujo de archivo de salida.
 * @return El flujo de archivo de salida modificado.
 */
std::ofstream& operator<<(std::ofstream& os, const Lattice& lattice) {
  lattice.displayfile(os);
  return os;
}