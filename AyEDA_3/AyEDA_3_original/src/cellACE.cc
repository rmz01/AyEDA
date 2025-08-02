#include "../include/cellACE.h"
#include "../include/lattice1D.h"

// Clase ACE 110 --------------------------------------------------------------------------------

/**
 * @brief Actualiza el estado de la celda ACE110 al estado siguiente.
 */
void CellACE110::updateState() {
  state_ = nextState_;
}

/**
 * @brief Imprime una representación de la celda ACE110 en el flujo de salida proporcionado.
 * 
 * @param os El flujo de salida en el que se imprimirá la celda.
 */
void CellACE110::display(std::ostream& os) {
  if (state_ == '0') {
    os << "-";
  } else {
    os << "X";
  }
}

/**
 * @brief Calcula el estado siguiente de la celda ACE110 basándose en el estado actual del retículo.
 * 
 * @param reticulo El retículo que contiene el estado actual de todas las celdas.
 */
void CellACE110::nextState(const Lattice& reticulo) {
  const State C = state_;
  State next_state{0};

  int position = position_[0];

  Position* Left = new PositionDim<1>(1, position - 1);
  Position* Right = new PositionDim<1>(1, position + 1);

  State L = reticulo[*Left].getState();
  State R = reticulo[*Right].getState();

  next_state = (C + R + C * R + L * C * R) % 2;
  if (next_state == 0) {
    nextState_ = '0';
  } else {
    nextState_ = '1';
  }
}

// Clase ACE 30 --------------------------------------------------------------------------------

/**
 * @brief Actualiza el estado de la celda ACE30 al estado siguiente.
 */
void CellACE30::updateState() {
  state_ = nextState_;
}

/**
 * @brief Imprime una representación de la celda ACE30 en el flujo de salida proporcionado.
 * 
 * @param os El flujo de salida en el que se imprimirá la celda.
 */
void CellACE30::display(std::ostream& os) {
  if (state_ == '0') {
    os << "-";
  } else {
    os << "X";
  }
}

/**
 * @brief Calcula el estado siguiente de la celda ACE30 basándose en el estado actual del retículo.
 * 
 * @param reticulo El retículo que contiene el estado actual de todas las celdas.
 */
void CellACE30::nextState(const Lattice& reticulo) {
  const State C = state_;
  State next_state{0};

  int position = position_[0];

  Position* Left = new PositionDim<1>(1, position - 1);
  Position* Right = new PositionDim<1>(1, position + 1);

  State L = reticulo[*Left].getState();
  State R = reticulo[*Right].getState();

  next_state = (L + C + R + C * R) % 2;
  if (next_state == 0) {
    nextState_ = '0';
  } else {
    nextState_ = '1';
  }
}