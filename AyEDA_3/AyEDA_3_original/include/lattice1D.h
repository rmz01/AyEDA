#ifndef LATTICE1D_H
#define LATTICE1D_H
#include <fstream>
#include <iostream>
#include <vector>
#include "lattice.h"
#include "factorycell.h"

// Clase 1D --------------------------------------------------------------------------------

class Lattice1D: public Lattice {
 public:
  Lattice1D(std::fstream& file, FactoryCell& factory);
  Lattice1D(const int& size, FactoryCell& factory);
  virtual ~Lattice1D();
  void nextGeneration();
  std::size_t Population() const;
 protected:
  std::ostream& display(std::ostream& os) const;
  std::ofstream& displayfile(std::ofstream& os) const;
  std::vector<Cell*> lattice_;
  int size_;
};

// Clase open --------------------------------------------------------------------------------

class Lattice1D_open: public Lattice1D {
 public:
  Lattice1D_open(const int& size, FactoryCell& factory, bool open_type);
  Lattice1D_open(std::fstream& file, FactoryCell& factory, bool open_type);
  ~Lattice1D_open();
  Cell& operator[](Position& position) const;
  
 private:
  bool open_type_; // The extra border cells can be 0 or 1
  Cell* border_;
};

// Clase periodic --------------------------------------------------------------------------------

class Lattice1D_periodic: public Lattice1D {
 public:
  Lattice1D_periodic(const int& size, FactoryCell& factory) : Lattice1D(size, factory) {}
  Lattice1D_periodic(std::fstream& file, FactoryCell& factory) : Lattice1D(file, factory) {}
  Cell& operator[](Position& position) const;
};

#endif // LATTICE1D_H