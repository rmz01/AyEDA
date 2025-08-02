#include <iostream>
#include <cstdlib> // Para usar atoi

#include "lattice.h"

int main(int argc, char* argv[]) {
  int size = 0;
  std::string borderType = "open";
  State borderValue = '0';
  std::string fileName = "";
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-size") {
      size = std::atoi(argv[i + 1]);
    } else if (std::string(argv[i]) == "-border") {
      borderType = argv[i + 1];
      borderValue = argv[i + 2][0];
    } else if (std::string(argv[i]) == "-init") {
      fileName = argv[i + 1];
    }
  }
  if (size <= 0 || (borderType != "open" && borderType != "periodic")) {
    std::cerr << "Error: Argumentos incorrectos." << std::endl;
    return 1;
  }
  Lattice lattice(size);
  lattice.loadInitialConfiguration(fileName, borderType, borderValue);
  // Simula la evolución del autómata celular
  char stopChar;
  do {
    std::cout << lattice; // Muestra el retículo
    lattice.nextGeneration(); // Evoluciona a la siguiente generación
    std::cout << "Presiona 'q' para detener la simulación, o cualquier otra tecla para continuar: ";
    std::cin >> stopChar;
  } while (stopChar != 'q');
  return 0;
}