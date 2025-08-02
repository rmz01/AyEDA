#ifndef LATTICE2D_H
#define LATTICE2D_H
#include <iostream>
#include <vector>
#include <fstream>
#include "lattice.h"
#include "factorycell.h"

// Clase 2D --------------------------------------------------------------------------------

class Lattice2D: public Lattice {
 public:
  Lattice2D(std::fstream& file, FactoryCell& factory);
  Lattice2D(const int& rows, const int& columns, FactoryCell& factory);
  virtual ~Lattice2D();
  virtual void nextGeneration();
  std::size_t Population() const;

 protected:
  std::ostream& display(std::ostream& os) const;
  std::ofstream& displayfile(std::ofstream& os) const;
  std::vector<std::vector<Cell*>> lattice_;
  int rows_;
  int columns_;
};

// Clase reflective --------------------------------------------------------------------------------

class Lattice2D_reflective: public Lattice2D {
 public:
  Lattice2D_reflective(std::fstream& file, FactoryCell& factory) : Lattice2D(file, factory) {}
  Lattice2D_reflective(const int& rows, const int& columns, FactoryCell& factory) : Lattice2D(rows, columns, factory) {}
  Cell& operator[](Position& position) const;
};

/* Clase NoBorder --------------------------------------------------------------------------------

class Lattice2D_NoBorder: public Lattice2D {
  public:
    Lattice2D_NoBorder(std::fstream& file, FactoryCell& factory) : Lattice2D(file, factory) { factory_ = &factory; }
    Lattice2D_NoBorder(const int& rows, const int& columns, FactoryCell& factory) : Lattice2D(rows, columns, factory) { factory_ = &factory; }
    Cell& operator[](Position& position) const;
    void nextGeneration();
    void CheckBorder();
    void IncrementSize(char direction);
  private:
    FactoryCell* factory_;
};
*/

#endif // LATTICE2D_H