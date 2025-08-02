#ifndef CELL_H
#define CELL_H
#include <iostream>
#include "position.h"

using State = unsigned char;

class Lattice;

class Cell {
 public:
  virtual ~Cell() {} // Destructor virtual para permitir la eliminación segura a través de punteros de tipo base
  Cell(Position& position, const State& state) : position_(position), state_(state) {}
  State getState() const { return state_; }
  void setState(State state) { state_ = state; }
  virtual void nextState(const Lattice& reticulo) = 0;
  virtual void updateState() { state_ = nextState_; }
  friend std::ostream& operator<<(std::ostream& os, Cell& cell);

 protected:
  Position& position_;
  virtual void display(std::ostream&) = 0;
  State state_;
  State nextState_;
};

#endif // CELL_H