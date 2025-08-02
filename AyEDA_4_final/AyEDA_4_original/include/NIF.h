
#ifndef NIF_H
#define NIF_H

#include <iostream>

class NIF {
  public:
  NIF();
  NIF(const long& nif);

  // Operador de comparación
  void operator=(int num);

  // Conversión implícita a long
  operator long() const;

  private:
  long nif_;
};


#endif