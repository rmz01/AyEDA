#include "cell.h"
#include "lattice.h"

// Constructor
Cell::Cell() : position_(0), state_('0'), nextState_('0') {}

Cell::Cell(const Position& pos, const State& st) : position_(pos), state_(st), nextState_('0') {}

State Cell::setState(State newState) {
  state_ = newState;
  return state_;
}

// Métodos
void Cell::updateState() { state_ = nextState_; }

// Método nextState
int Cell::nextState(const Lattice& lattice) {
  State left_neighbor_state, right_neighbor_state;
  std::string border_type = lattice.getBorderType();
  State border_value = lattice.getBorderValue();
  State central_state = lattice.getCell(position_).getState();

  if (border_type == "open") {
    if (position_ == 0) {
      left_neighbor_state = border_value;
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    } else if (position_ == lattice.getSize() - 1) {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = border_value;
    } else {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    }
  } else if (border_type == "periodic") {
    if (position_ == 0) {
      left_neighbor_state = lattice.getCell(lattice.getSize() - 1).getState();
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    } else if (position_ == lattice.getSize() - 1) {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = lattice.getCell(0).getState();
    } else {
      left_neighbor_state = lattice.getCell(position_ - 1).getState();
      right_neighbor_state = lattice.getCell(position_ + 1).getState();
    }
  }

  // Implementa la lógica de evolución con la regla
  /*
  if (left_neighbor_state == '1' && central_state == '1' && right_neighbor_state == '1') {
    nextState_ = '0';
  } else if (left_neighbor_state == '1' && central_state == '1' && right_neighbor_state == '0') {
    nextState_ = '1';
  } else if (left_neighbor_state == '1' && central_state == '0' && right_neighbor_state == '1') {
    nextState_ = '1';
  } else if (left_neighbor_state == '1' && central_state == '0' && right_neighbor_state == '0') {
    nextState_ = '0';
  } else if (left_neighbor_state == '0' && central_state == '1' && right_neighbor_state == '1') {
    nextState_ = '1';
  } else if (left_neighbor_state == '0' && central_state == '1' && right_neighbor_state == '0') {
    nextState_ = '1';
  } else if (left_neighbor_state == '0' && central_state == '0' && right_neighbor_state == '1') {
    nextState_ = '1';
  } else if (left_neighbor_state == '0' && central_state == '0' && right_neighbor_state == '0') {
    nextState_ = '0';
  }
  */

  // Implementa la lógica de evolución con la formula
  int left = left_neighbor_state - '0';
  int center = central_state - '0';
  int right = right_neighbor_state - '0';

  nextState_ = (center + right + center * right + left * center * right) % 2 + '0';  

  return nextState_;
}

// Sobrecarga del operador de inserción
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << (cell.getState() == '1' ? 'X' : 'Y');
  return os;
}