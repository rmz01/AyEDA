#ifndef LATTICE_H
#define LATTICE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "cell.h"

// Clase Retículo
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

#endif // LATTICE_H