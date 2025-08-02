#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Lattice;

// Definición de tipos
using State = unsigned char;
using Position = int;

// Clase Célula
class Cell {
 public:
  // Constructores
  Cell();
  Cell(const Position& pos, const State& st = '0');
  
  // Getters
  State getState() const { return state_; }
  Position getPosition() const { return position_; }

  // Setters
  State setState(State newState);
  
	// Métodos
  void updateState();

  // Declaración métodos
  int nextState(const Lattice& lattice);

  // Sobrecarga del operador de inserción
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

 private:
  Position position_;
  State state_;
  State nextState_;
};

#endif // CELL_H
