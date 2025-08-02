#ifndef CELLACE_H
#define CELLACE_H
#include "cell.h"

// Clase ACE base --------------------------------------------------------------------------------

class CellACE: public Cell {
  public:
  CellACE(Position& position, const State& state) : Cell(position, state) {}
};

// Clase ACE 110 --------------------------------------------------------------------------------

class CellACE110: public CellACE {
  public:
    CellACE110(Position& position, const State& state) : CellACE(position, state) {}
    void nextState(const Lattice& reticulo);
    void updateState();
    void display(std::ostream& os);
};

// Clase ACE 30 --------------------------------------------------------------------------------

class CellACE30: public CellACE {
  public:
    CellACE30(Position& position, const State& state) : CellACE(position, state) {}
    void nextState(const Lattice& reticulo);
    void updateState();
    void display(std::ostream& os);
};

// Clase ACEM5 (Modificacion) --------------------------------------------------------------------------------

class CellACEM5: public CellACE {
  public:
    CellACEM5(Position& position, const State& state) : CellACE(position, state) {}
    void nextState(const Lattice& reticulo);
    void updateState();
    void display(std::ostream& os);
};

#endif // CELLACE_H