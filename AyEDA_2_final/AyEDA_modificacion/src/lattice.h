#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <string>

#include "cell.h"

// Clase Retículo
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

#endif // LATTICE_H