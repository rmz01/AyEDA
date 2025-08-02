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
  // Modificacion -> Ahora las celulas vecinas son las que en lugar de considerar solo los vecinos 
  // inmediatos, ahora debemos considerar los vecinos a dos posiciones de distancia en ambos lados. 
  State left_neighbor_1_state, left_neighbor_2_state, right_neighbor_1_state, right_neighbor_2_state;
  std::string border_type = lattice.getBorderType();
  State border_value = lattice.getBorderValue();
  State central_state = lattice.getCell(position_).getState();

  if (border_type == "open") {
    if (position_ < 2) {
      left_neighbor_1_state = border_value;
      left_neighbor_2_state = border_value;
      right_neighbor_1_state = lattice.getCell(position_ + 2).getState();
      right_neighbor_2_state = lattice.getCell(position_ + 3).getState();
    } else if (position_ == 2) {
      left_neighbor_1_state = lattice.getCell(position_ - 2).getState();
      left_neighbor_2_state = border_value;
      right_neighbor_1_state = lattice.getCell(position_ + 2).getState();
      right_neighbor_2_state = lattice.getCell(position_ + 3).getState();
    }  else if (position_ == lattice.getSize() - 3) {
      left_neighbor_1_state = lattice.getCell(position_ - 2).getState();
      left_neighbor_2_state = lattice.getCell(position_ - 3).getState();
      right_neighbor_1_state = lattice.getCell(position_ + 2).getState();
      right_neighbor_2_state = border_value;
    } else if (position_ >= lattice.getSize() - 2) {
      left_neighbor_1_state = lattice.getCell(position_ - 2).getState();
      left_neighbor_2_state = lattice.getCell(position_ - 3).getState();
      right_neighbor_1_state = border_value;
      right_neighbor_2_state = border_value;
    }
    else {
      left_neighbor_1_state = lattice.getCell(position_ - 2).getState();
      left_neighbor_2_state = lattice.getCell(position_ - 3).getState();
      right_neighbor_1_state = lattice.getCell(position_ + 2).getState();
      right_neighbor_2_state = lattice.getCell(position_ + 3).getState();
    }
  } else if (border_type == "periodic") {
    if (position_ < 3) {
      left_neighbor_1_state = lattice.getCell((lattice.getSize() + position_ - 2) % lattice.getSize()).getState();
      left_neighbor_2_state = lattice.getCell((lattice.getSize() + position_ - 3) % lattice.getSize()).getState();
      right_neighbor_1_state = lattice.getCell((position_ + 2) % lattice.getSize()).getState();
      right_neighbor_2_state = lattice.getCell((position_ + 3) % lattice.getSize()).getState();
    } else if (position_ >= lattice.getSize() - 3) {
      left_neighbor_1_state = lattice.getCell((position_ - 2) % lattice.getSize()).getState();
      left_neighbor_2_state = lattice.getCell((position_ - 3) % lattice.getSize()).getState();
      right_neighbor_1_state = lattice.getCell((lattice.getSize() + position_ + 2) % lattice.getSize()).getState();
      right_neighbor_2_state = lattice.getCell((lattice.getSize() + position_ + 3) % lattice.getSize()).getState();
    } else {
      left_neighbor_1_state = lattice.getCell((position_ - 2) % lattice.getSize()).getState();
      left_neighbor_2_state = lattice.getCell((position_ - 3) % lattice.getSize()).getState();
      right_neighbor_1_state = lattice.getCell((position_ + 2) % lattice.getSize()).getState();
      right_neighbor_2_state = lattice.getCell((position_ + 3) % lattice.getSize()).getState();
    }
  }

  // MODIFICACION -> Ahora para saber el estado siguiente debemos contar el valor que mas se repita entre las 5 celulas
  int left_1 = left_neighbor_1_state - '0';
  int left_2 = left_neighbor_2_state - '0';
  int center = central_state - '0';
  int right_1 = right_neighbor_1_state - '0';
  int right_2 = right_neighbor_2_state - '0';

  int sum = left_1 + left_2 + center + right_1 + right_2;
  nextState_ = (sum >= 3) ? '1' : '0';  

  return nextState_;
}

// Sobrecarga del operador de inserción
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << (cell.getState() == '1' ? 'X' : ' ');
  return os;
}