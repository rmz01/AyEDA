#include "../include/DispersionFunction.h"
#include "../include/ExplorationFunction.h"
#include "../include/Hash.h"
#include "../include/Sequence.h"
#include "../include/NIF.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

struct parameters {
  int tablesize;
  int fd_code;  // 0: mod, 1: suma, 2: pseudoaleatorio
  int dispersion_technique; // 0: close, 1: open
  bool close_dispersion = false;
  int blocksize;
  int exploration_code; // 0: linear, 1: quadratic
};

parameters parse_args(int argc, char* argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  parameters options;
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-ts") {
      options.tablesize = std::stoi(*++it);
    }
    else if (*it == "-fd") {
      if (*++it == "mod") {
        options.fd_code = 0;
      } else if (*it == "suma") {
        options.fd_code = 1;
      } else if (*it == "pseudoaleatorio") {
        options.fd_code = 2;
      }
    }
    else if (*it == "-hash") {
      if (*++it == "close") {
        options.dispersion_technique = 0;
        options.close_dispersion = true;
      } else if (*it == "open") {
        options.dispersion_technique = 1;
      }
    }
    else if (*it == "-bs") {
      if (options.close_dispersion == false) {
        std::cerr << "Error: no se puede especificar el tamaño de bloque si la técnica de dispersión no es cerrada" << std::endl;
        exit(EXIT_SUCCESS);
      }
      options.blocksize = std::stoi(*++it);
    }
    else if (*it == "-fe") {
      if (*++it == "linear") {
        options.exploration_code = 0;
      } else if (*it == "quadratic") {
        options.exploration_code = 1;
      }
    }
    else {
      std::cerr << "Error: argumento no válido" << std::endl;
    }
  }
  return options;
}

int main(int argc, char *argv[]) {
    if (argc > 1 && std::string(argv[1]) == "-help") {
    std::cout << "Uso correcto del programa:\n";
    std::cout << "./programa -ts <tablesize>\n";
    std::cout << "-fd <0: mod, 1: suma, 2: pseudoaleatorio>\n";
    std::cout << "-hash <0: close, 1: open>\n";
    std::cout << "-bs <blocksize>\n"; 
    std::cout << "-fe <0: linear, 1: quadratic>\n";
    std::cout << "Ejemplo de ejecución:\n";
    std::cout << "./programa -ts 5 -fd mod -hash close -bs 3 -fe linear\n";
    return 0;
  }

  parameters options = parse_args(argc, argv);

  std::cout << "Menu de opciones:\n'i' para insertar clave.\n'r' para insertar clave aleatoria\n's' para buscar clave.\n'x' para salir.\n";

  DispersionFunction<NIF>* dispersion;
  switch(options.fd_code) {
    case 0:
      dispersion = new ModuleDispersion<NIF>(options.tablesize);
      break;
    case 1:
      dispersion = new SumDispersion<NIF>(options.tablesize);
      break;
    case 2:
      dispersion = new PseudoRandomDispersion<NIF>(options.tablesize);
      break;
    default:
      std::cerr << "Error: Funcion de dispersion desconocida." << std::endl;
      exit(EXIT_SUCCESS);
  }


  ExplorationFunction<NIF>* exploration;
  if (options.close_dispersion) {
    switch(options.exploration_code) {
      case 0:
        exploration = new LinearExploration<NIF>();
        break;
      case 1:
        exploration = new QuadraticExploration<NIF>();
        break;
        break;
      default:
        std::cerr << "Error: Funcion de exploracion desconocida." << std::endl;
        exit(EXIT_SUCCESS);
    }
  }

  Sequence<NIF>* hash_table;
  if (options.close_dispersion) {
    hash_table = new HashTable<NIF, StaticSequence<NIF>>(options.tablesize, *dispersion, *exploration, options.blocksize);
  } else {
    hash_table = new HashTable<NIF, DynamicSequence<NIF>>(options.tablesize, *dispersion);
  }


  bool running = true;
  char stop;
  long clave;
  while(running) {
    hash_table->Print();
    std::cin >> stop;
    switch(stop) {
      case 'i':
        std::cin >> clave;
        if (hash_table->Insert(clave)) {
          std::cout << "Clave insertada." << std::endl;
        } else {
          std::cout << "Clave no insertada." << std::endl;
        }
        break;
      case 'r': // insert random
          hash_table->Insert(NIF());
        break;
      case 's':
        std::cin >> clave;
        if (hash_table->Search(NIF(clave))) {
          std::cout << "Clave encontrada." << std::endl;
        } else {
          std::cout << "Clave no encontrada." << std::endl;
        }
        break;
      case 'x':
        running = false;
        break;
    }
  }

  return 0;
}