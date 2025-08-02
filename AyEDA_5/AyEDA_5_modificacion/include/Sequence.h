#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

template <class Key>
class Sequence {
  public:
  virtual bool Search(const Key& k) const = 0;
  virtual bool Insert(const Key& k) = 0;
  virtual void Print() const = 0;
  virtual Key& operator[](const int& index)  = 0;
};

/**
 * @brief Clase que implementa una secuencia de elementos de tamaño fijo
 */
template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence(int size, std::string init_method) {
    long clave;
    if (init_method == "manual") { // Inicializa la secuencia manualmente
      size_ = size;
      data_ = new Key[size_];
      Key* key_to_enter;
      for (unsigned i = 0; i < size_; i++) {
        std::cin >> clave;
        key_to_enter = new Key(clave);
        data_[i] = *key_to_enter;
      }
    } else if (init_method == "random") { // Inicializa la secuencia con números aleatorios
      size_ = size;
      data_ = new Key[size_];
      Key* clave_aleatoria;
      srand(time(NULL)); // generar semilla aleatoria
      for (unsigned i = 0; i < size_; i++) {
        clave = rand();
        clave_aleatoria = new Key(clave);
        data_[i] = *clave_aleatoria;
      }
    } else {
      std::cerr << "Error invalid mode." << std::endl; 
    } 
  }

  StaticSequence(int size, std::fstream& filename) {
    size_ = size;
    data_ = new Key[size_];
    long clave;
    Key* key_to_enter;
    for (unsigned i = 0; i < size_; i++) {
      filename >> clave;
      key_to_enter = new Key(clave);
      data_[i] = *key_to_enter;
    }
  }

  ~StaticSequence() { delete[] data_; }  

  unsigned size() const {
    return size_;
  }

  bool Search(const Key& k) const override {
    for (unsigned i = 0; i < size_; i++) {
      if (data_[i] == k) {
        return true;
      }
    }
    return false;
  }

  bool Insert(const Key& k) override {
    if (IsFull()) {
      return false;
    }
    for (unsigned i = 0; i < size_; i++) {
      if (data_[i] == k) {
        return false;
      }
    }
    for (unsigned i = 0; i < size_; i++) {
      if (long(data_[i]) == 0) {
        data_[i] = k;
        return true;
      }
    }
    return false;
  }

  void Initialize(int size) {
    long value = 0;
    size_ = size;
    data_ = new Key[size_];
    for (unsigned i = 0; i < size_; i++) {
      data_[i] = value;
    }
  }

  void Print() const {
    for (unsigned i = 0; i < size_; i++) {
      std::cout << data_[i] << " ";
    }
    std::cout << std::endl;
  }

  bool IsFull() const {
    for (unsigned i = 0; i < size_; i++) {
      if (long(data_[i]) == 0) {
        return false;
      }
    }
  return true;
  }

  Key& operator[](const int& index)  override {
    return data_[index];
  }

 private:
  unsigned size_;
  Key* data_;
};

#endif