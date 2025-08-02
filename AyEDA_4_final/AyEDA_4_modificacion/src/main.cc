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
#include <random> // modificacion
#include <chrono> // modificacion


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
    std::cout << "-fe <0: linear, 1: quadratic\n";
    std::cout << "Ejemplo de ejecución:\n";
    std::cout << "./programa -ts 5 -fd 1 -hash open -bs 5 -fe 1\n";
    return 0;
  }

    const unsigned tableSize = 50;
    ModuleDispersion<long> modDispersion(tableSize);
    SumDispersion<long> sumDispersion(tableSize);
    PseudoRandomDispersion<long> pseudoRandomDispersion(tableSize);

    std::vector<long> randomNumbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (int n = 0; n < 1000; ++n) {
        randomNumbers.push_back(dis(gen));
    }

    std::vector<DispersionFunction<long>*> dispersionFunctions = {&modDispersion, &sumDispersion, &pseudoRandomDispersion};
    std::vector<std::string> functionNames = {"ModuleDispersion", "SumDispersion", "PseudoRandomDispersion"};

    for (int i = 0; i < dispersionFunctions.size(); ++i) {
        std::vector<int> hits(tableSize, 0);
        for (long number : randomNumbers) {
            hits[(*dispersionFunctions[i])(number)]++;
        }
        std::cout << functionNames[i] << " hits: ";
        for (int hit : hits) {
            std::cout << hit << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}