#include "../include/NIF.h"
#include <iostream>
#include <ctime>


NIF::NIF() {
  srand(time(NULL));
    nif_ = rand();
    while (nif_ % 100000000 != nif_) {
      nif_ /= 10;
    }
}


NIF::NIF(const long& nif) {
  long new_nif = nif;
  while (new_nif / 100000000 == 0) {
    new_nif *= 10;
  }

  while (new_nif % 100000000 != new_nif) {
    new_nif /= 10;
  }

  nif_ = new_nif;
}


void NIF::operator=(int num) {
  if (num / 100000000 != 0) {
    while (num / 100000000 == 0) {
      num *= 10;
    }
    while (num % 100000000 != num) {
      num /= 10;
  }
  }
  nif_ = num;
}


NIF::operator long() const {
  return nif_;
}