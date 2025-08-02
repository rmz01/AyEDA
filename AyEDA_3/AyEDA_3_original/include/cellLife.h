#ifndef CELLLIFE_H
#define CELLLIFE_H
#include "cell.h"

// Clase Life base --------------------------------------------------------------------------------

class CellLife: public Cell {
 public:
  CellLife(Position& position, const State& state) : Cell(position, state) {}
};

// Clase Life 23_3 --------------------------------------------------------------------------------

class CellLife23_3: public CellLife {
 public:
  CellLife23_3(Position& position, const State& state) : CellLife(position, state) {}
  void nextState(const Lattice& reticulo);
  void updateState();
  void display(std::ostream& os);
};

// Clase Life 51_346 --------------------------------------------------------------------------------

class CellLife51_346: public CellLife {
 public:
  CellLife51_346(Position& position, const State& state) : CellLife(position, state) {}
  void nextState(const Lattice& reticulo);
  void updateState();
  void display(std::ostream& os);
};

#endif // CELLLIFE_H