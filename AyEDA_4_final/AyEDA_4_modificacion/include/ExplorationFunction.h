#ifndef EXPLORATIONFUNCTION_H
#define EXPLORATIONFUNCTION_H

#include <iostream>
#include "DispersionFunction.h"

template <class Key>
class ExplorationFunction {
  public:
  virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
    LinearExploration() {}
    unsigned operator()(const Key& k, unsigned i) const override {
        std::cout << "Exploracion lineal" << std::endl;
        return i;
        // En la exploración lineal, simplemente se devuelve i, lo que significa que se explorarán los índices de la tabla hash en orden secuencial (es decir, 0, 1, 2, 3, ...).
    }
};

template <class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
 public:
    QuadraticExploration() {}
    unsigned operator()(const Key& k, unsigned i) const override {
        std::cout << "Exploracion cuadratica" << std::endl;
        return (i * i);
        //  En la exploración cuadrática, se devuelve i * i, lo que significa que se explorarán los índices de la tabla hash en un orden cuadrático (es decir, 0, 1, 4, 9, 16, ...).
    }
};


#endif