#ifndef DISPERSIONFUNCTION_H
#define DISPERSIONFUNCTION_H

#include <iostream>

template <class Key>
class DispersionFunction {
 public:
  virtual unsigned operator()(const Key& k) const = 0;
};

template <class Key>
class ModuleDispersion : public DispersionFunction<Key> {
 public:
  ModuleDispersion(unsigned tablesize) : tableSize_{tablesize} {}
  unsigned operator()(const Key& clave) const {
    std::cout << "ModuleDispersion: " << long(clave) % tableSize_ << std::endl; // Hago uso de la conversión a long de la clase Nif esta conversión solo funcionará si el tipo Key puede ser convertido a long.
    return long(clave) % tableSize_;
    // Por ejemplo, si la clave es 1234 y el tamaño de la tabla hash es 10, el operador () tomaría el módulo de la clave con el tamaño de la tabla hash (1234 % 10 = 4). Por lo tanto, el índice de la tabla hash para la clave 1234 sería 4.
  }
 private:
  unsigned tableSize_;
};

template <class Key>
class SumDispersion : public DispersionFunction<Key> {
 public:
  SumDispersion(unsigned tablesize) : tableSize_{tablesize} {}
  unsigned operator()(const Key& param_key) const {
    long clave = param_key;
    unsigned sum = 0;
    while (clave > 0) {
      sum += clave % 10;
      clave /= 10;
    }
    std::cout << "SumaDispersion: " << sum % tableSize_ << std::endl;
    return sum % tableSize_;
    // Por ejemplo, si la clave es 1234 y el tamaño de la tabla hash es 10, el operador () sumaría los dígitos (1 + 2 + 3 + 4 = 10) y luego tomaría el módulo de esta suma con el tamaño de la tabla hash (10 % 10 = 0). Por lo tanto, el índice de la tabla hash para la clave 1234 sería 0
  }

 private:
  unsigned tableSize_;
};

template <class Key>
class PseudoRandomDispersion : public DispersionFunction<Key> {
 public:
  PseudoRandomDispersion(unsigned tablesize) : tableSize_{tablesize} {}
  unsigned operator()(const Key& clave) const {
    srand(long(clave));
    return rand() % tableSize_;
    // Por ejemplo, si la clave es 1234 y el tamaño de la tabla hash es 10, el operador () inicializaría la semilla del generador de números pseudoaleatorios con 1234, generaría un número pseudoaleatorio y luego tomaría el módulo de este número con el tamaño de la tabla hash. El resultado sería un número entre 0 y 9, que sería el índice de la tabla hash para la clave 1234.
  }

 private:
  unsigned tableSize_;
};

#endif