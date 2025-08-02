#include <iostream>
#include <cstdlib> // Para usar atoi
#include <unistd.h>

#include "lattice.h"


int main(int argc, char* argv[]) {
  std::string fileName;
  std::string borderType;
  int rows = 0, cols = 0;


  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-init" && i + 1 < argc) {
      fileName = argv[++i];
    } else if (arg == "-border" && i + 1 < argc) {
      borderType = argv[++i];
    } else if (arg == "-size" && i + 2 < argc) {
      rows = std::stoi(argv[++i]);
      cols = std::stoi(argv[++i]);
    } else {
      std::cerr << "Uso: " << argv[0] << " -init [fichero] -border [borderType] -size [M] [N]\n";
      return 1;
    }
  }

  if (borderType.empty()) {
    std::cerr << "Debe proporcionar -border\n";
    return 1;
  }

  // Inicializa el autómata celular con un retículo cargado desde un archivo
  if (!fileName.empty()) {
    Lattice lattice(fileName);
    lattice.setBorderType(borderType);
    // Simula la evolución del autómata celular
  std::cout << lattice; // Muestra el retículo
  char command;
  do {
    std::cout << "Comando: ";
    std::cin >> command;
    switch (command) {
      case 'x':
        return 0;
      case 'n':
        lattice.nextGeneration();
        std::cout << lattice << std::endl;
        break;
      case 'L':
        for (int i = 0; i < 5; ++i) {
          lattice.nextGeneration();
          std::cout << lattice << std::endl;
        }
        break;
      case 'c':
        std::cout << "Población: " << lattice.Population() << std::endl;
        break;
      case 's':  {
        std::string fileName;
        std::cout << "Nombre del archivo: ";
        std::cin >> fileName;
        lattice.saveToFile(fileName);
        break;
      }
        break;
    }
  } while (true);

    // Inicializa el autómata celular con un retículo de tamaño MxN
    } else if (rows > 0 && cols > 0) {
      Lattice lattice(rows, cols);
      lattice.setBorderType(borderType);
      int numCells;
      std::cout << "¿Cuántas células vivas desea inicializar? ";
      std::cin >> numCells;
      for (int i = 0; i < numCells; ++i) {
        int row, col;
        std::cout << "Introduzca las coordenadas de la célula viva " << i + 1 << " (fila columna): ";
        std::cin >> row >> col;
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
          lattice[Position(row, col)].setState('1');
        } else {
          std::cerr << "Las coordenadas están fuera de rango. Inténtalo de nuevo.\n";
          --i;
        }
      }
  // Simula la evolución del autómata celular
  std::cout << lattice; // Muestra el retículo
  char command;
  do {
    std::cout << "Comando: ";
    std::cin >> command;
    switch (command) {
      case 'x':
        return 0;
      case 'n':
        lattice.nextGeneration();
        std::cout << lattice << std::endl;
        break;
      case 'L':
        for (int i = 0; i < 5; ++i) {
          lattice.nextGeneration();
          std::cout << lattice << std::endl;
        }
        break;
      case 'c':
        std::cout << "Población: " << lattice.Population() << std::endl;
        break;
      case 's':  {
        std::string fileName;
        std::cout << "Nombre del archivo: ";
        std::cin >> fileName;
        lattice.saveToFile(fileName);
        break;
      }
        break;
    }
  } while (true);
  // Si no se proporciona un archivo o un tamaño, se muestra un mensaje de error
    } else {
      std::cerr << "Debe proporcionar -init o -size\n";
      return 1;
    }
  return 0;
}