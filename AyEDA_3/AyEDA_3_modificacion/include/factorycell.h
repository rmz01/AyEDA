#ifndef FACTORYCELL_H
#define FACTORYCELL_H
#include "cell.h"
#include "cellACE.h"
#include "cellLife.h"

// libreria para sacar el numero aleatorio
#include <stdlib.h>

// Clase FactoryCell base --------------------------------------------------------------------------------

class FactoryCell {
 public:
  FactoryCell() {}
  virtual Cell* createCell(Position& position, const State& state) = 0;
};

// Clase FactoryCell ACE110 --------------------------------------------------------------------------------

class FactoryCellACE110: public FactoryCell {
 public:
  FactoryCellACE110() {}
  Cell* createCell(Position& position, const State& state) {
    return new CellACE110(position, state);
  }
};

// Clase FactoryCell ACE30 --------------------------------------------------------------------------------

class FactoryCellACE30: public FactoryCell {
 public:
  Cell* createCell(Position& position, const State& state) {
    return new CellACE30(position, state);
  }
};

// Clase FactoryCell ACEM5 (modificacion) --------------------------------------------------------------------------------

class FactoryCellACEM5: public FactoryCell {
 public:
  Cell* createCell(Position& position, const State& state) {
    // Sacamos un numero aleatorio para que escoja la factoría aleatoria entre las 3 implementadas del ACE.
    int random = rand() % 3;
    if (random == 0) {
      return new CellACE110(position, state);
    } else if (random == 1) {
      return new CellACE30(position, state);
    } else {
      return new CellACEM5(position, state);
    }
  }
};

// Clase FactoryCell Life23_3 --------------------------------------------------------------------------------

class FactoryCellLife23_3: public FactoryCell {
 public:
  Cell* createCell(Position& position, const State& state) {
    return new CellLife23_3(position, state);
  }
};

// Clase FactoryCell Life51_346 --------------------------------------------------------------------------------

class FactoryCellLife51_346: public FactoryCell {
 public:
  Cell* createCell(Position& position, const State& state) {
    return new CellLife51_346(position, state);
  }
};

#endif