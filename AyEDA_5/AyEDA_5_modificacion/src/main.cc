#include "../include/Sequence.h"
#include "../include/Methods.h"
#include "../include/Sort.h"
#include "../include/NIF.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

struct parameters {
  int size;
  int sort_method;
  std::string init_method;
  std::string file_name;
  bool trace = false;
};

parameters parse_args(int argc, char* argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);
  parameters options;
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    if (*it == "-size") {
      options.size = std::stoi(*++it);
    } else if (*it == "-ord") {
      options.sort_method = std::stoi(*++it);
    } else if (*it == "-init") {
      options.init_method = *++it;
      if (options.init_method == "file") {
        options.file_name = *++it;
      }
    } else if (*it == "-trace") {
      options.trace = (*++it == "y");
    }
  }
  return options;
}


int main(int argc, char *argv[]) {
  parameters options = parse_args(argc, argv);

  StaticSequence<NIF>* sequence_to_order;
  if (options.init_method == "manual") {
    sequence_to_order = new StaticSequence<NIF>(options.size, options.init_method); // Manual
  } else if (options.init_method == "random") {
    sequence_to_order = new StaticSequence<NIF>(options.size, options.init_method); // Random
  } else if (options.init_method == "file") {
    sequence_to_order = new StaticSequence<NIF>(options.size, options.file_name); // File
  }

  SortMethod<NIF>* sort_method;
  if (options.sort_method == 0) {
    sort_method = new SelectionSortMethod<NIF>(*sequence_to_order, options.size, options.trace);
  } else if (options.sort_method == 1) {
    sort_method = new QuickSortMethod<NIF>(*sequence_to_order, options.size, options.trace);
  } else if (options.sort_method == 2) {
    sort_method = new HeapSortMethod<NIF>(*sequence_to_order, options.size, options.trace);
  } else if (options.sort_method == 3) {
    sort_method = new ShellSortMethod<NIF>(*sequence_to_order, options.size, options.trace);
  } else if (options.sort_method == 4) {
    sort_method = new RadixSortMethod<NIF>(*sequence_to_order, options.size, options.trace);
  }

  sort_method->Print();
  sort_method->Sort();
  sort_method->Print();

  return 0;
}