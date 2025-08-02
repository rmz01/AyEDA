#include "../include/cell.h"

/**
 * @brief Sobrecarga del operador de inserción para la clase Cell.
 * 
 * @param os El flujo de salida en el que se imprimirá la celda.
 * @param cell La celda que se imprimirá en el flujo de salida.
 * @return El flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, Cell& cell) {
  cell.display(os);
  return os;
}