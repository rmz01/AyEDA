#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "DispersionFunction.h"
#include "ExplorationFunction.h"
#include "Sequence.h"

// Tabla hash para secuencia estática ---------------------------------------------------------------------------

template <class Key, class Container=StaticSequence<Key>>
class HashTable: public Sequence<Key> {
 public:
  HashTable(unsigned tablesize, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned blockSize) : fd_{fd}, fe_{fe} {
    tableSize_ = tablesize;
    blockSize_ = blockSize;
    table_ = new Container[tableSize_];
    for (unsigned i = 0; i < tableSize_; i++) {
      table_[i].Initialize(blockSize_);
    }
  }

  ~HashTable() {
    delete[] table_;
  }


  bool Search(const Key& k) const {
    unsigned position = fd_(k);
    unsigned intento{0};
    bool runnig{true};
    while (runnig) {
      if (intento >= tableSize_*3) return false;
      if (table_[position].Search(k)) {
        return true;
      }
      if (!table_[position].IsFull()) {
        runnig = false;
      }
      position =  (position + fe_(k, intento)) % tableSize_;
      intento++;
    }
    return false;
  }


  bool Insert(const Key& clave) {
    unsigned position = fd_(clave);
    unsigned intento{0};
    bool runnig{true};
    while (runnig) {
      if (intento >= tableSize_ * blockSize_ * 10) {
        std::cout << "Tiempo agotado" << std::endl;
        return false;
      }
      if (table_[position].Insert(clave)) {
        return true;
      }
      if (!table_[position].IsFull()) {
        std::cout << "Celda no llena" << std::endl;
        runnig = false;
      }
      position = (fd_(clave) + fe_(clave, intento)) % tableSize_;
      intento++;
    }
    return false;
  }


  void Print() const {
    for (unsigned i = 0; i < tableSize_; i++) {
      std::cout << "Position " << i << ": ";
      table_[i].Print();
      std::cout << std::endl;
    }
  }

 private:
  unsigned tableSize_;
  Container* table_;  
  DispersionFunction<Key>& fd_;
  ExplorationFunction<Key>& fe_;
  unsigned blockSize_;
};

// Tabla hash para secuencia dinámica ---------------------------------------------------------------------------

template <class Key>
class HashTable<Key, DynamicSequence<Key>>: public Sequence<Key> {
 public:
  HashTable(unsigned tablesize, DispersionFunction<Key>& fd) : fd_{fd} {
    tableSize_ = tablesize;
    table_ = new DynamicSequence<Key>[tableSize_];
  }

  ~HashTable() {
    delete[] table_;
  }

  bool Search(const Key& k) const {
    unsigned position = fd_(k);
    return table_[position].Search(k);
  }

  bool Insert(const Key& k) {
    unsigned position = fd_(k);
    return table_[position].Insert(k);
  }

  void Print() const {
    for (unsigned i = 0; i < tableSize_; i++) {
      std::cout << "Position " << i << ": ";
      table_[i].Print();
      std::cout << std::endl;
    }
  }

 private:
  unsigned tableSize_;
  DynamicSequence<Key>* table_;  
  DispersionFunction<Key>& fd_;
};

#endif  // HASHTABLE_H