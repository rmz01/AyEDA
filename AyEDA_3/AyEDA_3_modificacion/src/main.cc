#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../include/cell.h"
#include "../include/lattice.h"
#include "../include/factorycell.h"
#include "../include/position.h"
#include "../include/lattice1D.h"
#include "../include/lattice2D.h"

/**
 * @struct parameters
 * @brief Estructura para almacenar los parámetros de la simulación.
 */
struct parameters {
  int dimension;
  bool two_dim = false;
  int size_x;
  int size_y;
  int cell_type; // 0: Ace110, 1: Ace30, 2: Life23_3, 3: Life51_346 4: AceM5
  int border; // 0: open, 1: periodic, 2: reflective, 3: no border
  bool open_type = false;
  std::fstream filename;
  bool initial_file = false;
};

/**
 * @brief Función principal del programa.
 * 
 * Esta función lee los argumentos de la línea de comandos, crea la fábrica de celdas y el retículo adecuados según los argumentos,
 * y luego entra en un bucle en el que el usuario puede interactuar con la simulación.
 * 
 * @param argc El número de argumentos de la línea de comandos.
 * @param argv Los argumentos de la línea de comandos.
 * @return 0 si el programa se ejecutó con éxito, un número distinto de cero en caso contrario.
 */
int main(int argc, char *argv[]) {
  // Tipo de parametros
  std::vector<std::string> args(argv + 1, argv + argc);
  parameters options;
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-dim") {
      options.dimension = std::stoi(*++it);
      if (options.dimension == 2) {
        options.two_dim = true;
      }
    }
    else if (*it == "-cell") {
      if (*++it == "Ace110") {
        options.cell_type = 0;
      } else if (*it == "Ace30") {
        options.cell_type = 1;
      } else if (*it == "Life23_3") {
        options.cell_type = 2;
      } else if (*it == "Life51_346") {
        options.cell_type = 3;
      } else if (*it == "AceM5") {
        options.cell_type = 4;
      }
    }
    else if (*it == "-size") {
      options.size_x = std::stoi(*++it);
      if (options.two_dim) options.size_y = std::stoi(*++it);
    } else if (*it == "-border") {
        if (*++it == "open") {
          options.border = 0;
          if (*++it == "1") {
            options.open_type = true;
          }
        } else if (*it == "periodic") {
          options.border = 1;
        } else if (*it == "reflective") {
          options.border = 2;
        } else if (*it == "noborder") {
          options.border = 3;
        }
    } else if (*it == "-init") {
      options.filename = std::fstream(*++it);
      options.initial_file = true;
    }
    else {
      std::cerr << "Error: argumento no válido" << std::endl;
    }
  }

  std::cout << "Menu:" << std::endl << "'x' to exit.\n's' to save configuration.\n'n' to show next generation.\n";
  std::cout << "'L' to show next 5 generations.\n'c' to show population.\n";

  // Creacion del tipo de celula
  FactoryCell* factory;
  switch(options.cell_type) {
    case 0:
      factory = new FactoryCellACE110();
      break;
    case 1:
      factory = new FactoryCellACE30();
      break;
    case 2:
      factory = new FactoryCellLife23_3();
      break;
    case 3:
      factory = new FactoryCellLife51_346();
      break;
    case 4:
      factory = new FactoryCellACEM5();
    break;
  }

  // Creacion del tipo de borde
  Lattice* lattice;
  switch(options.border) {
    case 0:
      if (options.initial_file) {
        lattice = new Lattice1D_open(options.filename, *factory, options.open_type);
      } else {
        lattice = new Lattice1D_open(options.size_x, *factory, options.open_type);
      }
      break;
    case 1:
      if (options.initial_file) {
        lattice = new Lattice1D_periodic(options.filename, *factory);
      } else {
        lattice = new Lattice1D_periodic(options.size_x, *factory);
      }
      break;
    case 2:
      if (options.initial_file) {
        lattice = new Lattice2D_reflective(options.filename, *factory);
      } else {
        lattice = new Lattice2D_reflective(options.size_x, options.size_y, *factory);
      }
      break;
    case 3:
      if (options.initial_file) {
        // lattice = new Lattice2D_NoBorder(options.filename, *factory);
        lattice = new Lattice2D_reflective(options.filename, *factory);
      } else {
        // lattice = new Lattice2D_NoBorder(options.size_x, options.size_y, *factory);
        lattice = new Lattice2D_reflective(options.size_x, options.size_y, *factory);
      }
      break;
  }
  
  // Menu
  std::cout << *lattice << std::endl;
  bool population = false;
  bool running = true;
  char stop;
  while(running) {
    std::cin >> stop;
    switch (stop) {
      case 'x':
        running = false;
        break;
      case 'n': // Calcula y muestra la siguiente generación
        lattice->nextGeneration();
        if (population) {
          std::cout << lattice->Population() << std::endl;
        } else {
            std::cout << *lattice << std::endl;
          }
        break;
      case 'L': // Calcula y muestra las siguientes 5 generaciones
        for (int i = 0; i < 5; i++) {
          lattice->nextGeneration();
          if (population) {
            std::cout << lattice->Population() << std::endl;
          } else {
              std::cout << *lattice << std::endl;
            }
        }
        break;
      case 'c': // Se muestra la población (número de células vivas) actual
        population = (population) ? false : true;
        break;
      case 's': // Guarda la configuración actual en un fichero
        std::string file_name;
        std::cin >> file_name;
        std::ofstream output_file{file_name};
        output_file << *lattice;
        output_file.close();
        break;
    }
  }

  return 0;
}