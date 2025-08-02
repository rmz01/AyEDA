#ifndef METHODS_H
#define METHODS_H

#include "Sequence.h"

/**
 * @brief Clase base para los métodos de ordenación
*/
template <class Key>
class SortMethod {
 public:
  //En el constructor de las clases derivadas, llamo a este constructor de la clase base utilizando la sintaxis : SortMethod<Key>(sequence, size, trace).
  SortMethod(StaticSequence<Key>& sequence, const int& size, bool& trace) 
    : sequence_(sequence), size_(size), trace_(trace){}

  virtual void Sort() = 0;

  void Print() const {
    sequence_.Print();
  }

 protected:
  StaticSequence<Key> sequence_;
  int size_;
  bool trace_;
};

/**
 * @brief Clase que implementa el método de ordenación por selección
*/
template <class Key>
class SelectionSortMethod : public SortMethod<Key> {
 public:
  SelectionSortMethod(StaticSequence<Key>& sequence, const int& size, bool& trace) 
    : SortMethod<Key>(sequence, size, trace) {}
  
  void Sort() override {
    selectionSort(SortMethod<Key>::sequence_, SortMethod<Key>::size_, SortMethod<Key>::trace_);
  }
};

/**
 * @brief Clase que implementa el método de ordenación quicksort
*/
template <class Key>
class QuickSortMethod : public SortMethod<Key> {
 public:
  QuickSortMethod(StaticSequence<Key>& sequence, const int& size, bool& trace) 
    : SortMethod<Key>(sequence, size, trace) {}

  void Sort() override {
    quickSort(SortMethod<Key>::sequence_, SortMethod<Key>::size_, SortMethod<Key>::trace_);
  }
};

/**
 * @brief Clase que implementa el método de ordenación heapsort
*/
template <class Key>
class HeapSortMethod : public SortMethod<Key> {
 public:
  HeapSortMethod(StaticSequence<Key>& sequence, const int& size, bool& trace) 
    : SortMethod<Key>(sequence, size, trace) {}

  void Sort() override {
    heapSort(SortMethod<Key>::sequence_, SortMethod<Key>::size_, SortMethod<Key>::trace_);
  }
};

/**
 * @brief Clase que implementa el método de ordenación shellsort
*/
template <class Key>
class ShellSortMethod : public SortMethod<Key> {
 public:
  ShellSortMethod(StaticSequence<Key>& sequence, const int& size, bool& trace) 
    : SortMethod<Key>(sequence, size, trace) {}

  void Sort() override {
    shellSort(SortMethod<Key>::sequence_, SortMethod<Key>::size_, SortMethod<Key>::trace_);
  }
};

/**
 * @brief Clase que implementa el método de ordenación RadixSort
*/
template <class Key>
class RadixSortMethod : public SortMethod<Key> {
 public:
  RadixSortMethod(StaticSequence<Key>& sequence, const int& size, bool& trace) 
    : SortMethod<Key>(sequence, size, trace) {}

  void Sort() override {
    radixsort(SortMethod<Key>::sequence_, SortMethod<Key>::size_, SortMethod<Key>::trace_);
  }
};

#endif