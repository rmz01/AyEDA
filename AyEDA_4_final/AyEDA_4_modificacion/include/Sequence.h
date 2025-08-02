#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>

template <class Key>
class Sequence {
  public:
  virtual bool Search(const Key& k) const = 0;
  virtual bool Insert(const Key& k) = 0;
  virtual void Print() const = 0;
};

// Secuencia dinámica -----------------------------------------------------------------------------------------------------

template <class Key>
class DynamicSequence : public Sequence<Key> {
 public:
  DynamicSequence() { data_.clear(); }

  ~DynamicSequence() {}

  bool Search(const Key& k) const override {
    for (Key element : data_) {
      if (element == k) {
        return true;
      }
    }
    return false;
  }

  bool Insert(const Key& k) override {
    data_.push_back(k);
    return true;
  }

  void Print() const {
    for (Key element : data_) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }

  private:
  std::vector<Key> data_;
};


// Secuencia estatica --------------------------------------------------------------------------------------------------

template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence() : size_(0), data_(nullptr) {}

  ~StaticSequence() { delete[] data_; }  

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

 private:
  unsigned size_;
  Key* data_;
};

#endif