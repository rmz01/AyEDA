#include "cell.h"
#include "lattice.h"

// Constructor
Cell::Cell() : position_(std::make_pair(0, 0)), state_('0'), nextState_('0') {}

Cell::Cell(const Position& pos, const State& st) : position_(pos), state_(st), nextState_('0') {}

State Cell::setState(State newState) {
  state_ = newState;
  return state_;
}

void Cell::updateState() { state_ = nextState_; }

int Cell::nextState(const Lattice& lattice) {
  int live_neighbors = 0;
  std::string border_type = lattice.getBorderType();

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) continue; // Skip the cell itself

      Position neighbor(position_.first + i, position_.second + j);
      State neighbor_state;

      if (border_type == "reflective") {
        if (neighbor.first < 0 || neighbor.first >= lattice.getRows() || neighbor.second < 0 || neighbor.second >= lattice.getCols()) {
          neighbor_state = state_;
        } else {
          neighbor_state = lattice.getCell(neighbor).getState();
        }
      } 
      if (border_type == "noborder") {
        if (neighbor.first < 0 || neighbor.first >= lattice.getRows() || neighbor.second < 0 || neighbor.second >= lattice.getCols()) {
          neighbor_state = '0'; // Consider out-of-bounds cells as dead
        } else {
          neighbor_state = lattice.getCell(neighbor).getState();
        }
      }

      live_neighbors += (neighbor_state == '1' ? 1 : 0);
    }
  }

// Modificacion de las reglas del juego pasando de la 23/3 a la 35/234
  if (state_ == '1' && (live_neighbors == 3 || live_neighbors == 5)) {
    nextState_ = '1';
  } else if (state_ == '0' && (live_neighbors == 2 || live_neighbors == 3 || live_neighbors == 4)) {
    nextState_ = '1';
  } else {
    nextState_ = '0';
  }
  return nextState_;
}


std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << (cell.getState() == '1' ? 'X' : '-');
  return os;
}