#ifndef LATTICE_H
#define LATTICE_H
#include <iostream>
#include "position.h"

using State = unsigned char;

class Cell;

class Lattice {
 public:
  virtual ~Lattice() {} // Destructor virtual para permitir la eliminación segura a través de punteros de tipo base
  virtual Cell& operator[](Position&) const = 0;
  virtual void nextGeneration() = 0;
  virtual std::size_t Population() const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);
  friend std::ofstream& operator<<(std::ofstream& os, const Lattice& lattice);

 protected:
  virtual std::ostream& display(std::ostream& os) const = 0;
  virtual std::ofstream& displayfile(std::ofstream& os) const = 0;
};

#endif // LATTICE_H