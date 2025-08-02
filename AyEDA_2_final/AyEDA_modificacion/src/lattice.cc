#include "lattice.h"
#include <fstream>
#include <iostream>

Lattice::Lattice(int rows, int cols) : rows_(rows), cols_(cols) {
  cells_.resize(rows, std::vector<Cell*>(cols, nullptr));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells_[i][j] = new Cell(std::make_pair(i, j));
    }
  }
}

Lattice::Lattice(const std::string& fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
    return;
  }
  file >> rows_ >> cols_;
  cells_.resize(rows_, std::vector<Cell*>(cols_, nullptr));
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      cells_[i][j] = new Cell(std::make_pair(i, j));
      char state;
      file >> state;
      if (state == '1') {
        cells_[i][j]->setState('1');
      } else {
        cells_[i][j]->setState('0');
      }
    }
  }
  file.close();
}

Lattice::~Lattice() {
  for (auto& row : cells_) {
    for (auto& cell : row) {
      delete cell;
    }
  }
}

const Cell& Lattice::getCell(const Position& pos) const {
  int x = pos.first;
  int y = pos.second;
  return *cells_[x][y];
}

void Lattice::nextGeneration() {
  // Calculate the next state for each cell
  for (auto& row : cells_) {
    for (auto& cell : row) {
      cell->nextState(*this);
    }
  }
  if (border_type_ == "noborder") {
  // Check if any border cell is alive
  bool topRowAlive = false, bottomRowAlive = false, leftColumnAlive = false, rightColumnAlive = false;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (cells_[i][j]->getState() == '1') {
        if (i == 0) topRowAlive = true;
        if (i == rows_ - 1) bottomRowAlive = true;
        if (j == 0) leftColumnAlive = true;
        if (j == cols_ - 1) rightColumnAlive = true;
      }
    }
  }

  // Add new row/column if necessary
  if (topRowAlive) {
    cells_.insert(cells_.begin(), std::vector<Cell*>(cols_, nullptr));
    for (int j = 0; j < cols_; ++j) {
      cells_[0][j] = new Cell(std::make_pair(0, j), '0');
    }
    ++rows_;
  }
  if (bottomRowAlive) {
    cells_.push_back(std::vector<Cell*>(cols_, nullptr));
    for (int j = 0; j < cols_; ++j) {
      cells_[rows_][j] = new Cell(std::make_pair(rows_, j), '0');
    }
    ++rows_;
  }
  if (leftColumnAlive) {
    for (auto& row : cells_) {
      row.insert(row.begin(), new Cell(std::make_pair(row[0]->getPosition().first, 0), '0'));
    }
    ++cols_;
  }
  if (rightColumnAlive) {
    for (auto& row : cells_) {
      row.push_back(new Cell(std::make_pair(row[0]->getPosition().first, cols_), '0'));
    }
    ++cols_;
  }
  }

  // Update the state of each cell
  for (auto& row : cells_) {
    for (auto& cell : row) {
      cell->updateState();
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (const auto& row : lattice.cells_) {
    for (const auto& cell : row) {
      os << *cell;
    }
    os << std::endl;
  }
  return os;
}

Cell& Lattice::operator[](const Position& pos) const {
  int row = pos.first;
  int col = pos.second;
  if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
    return *cells_[row][col];
  } else {
    throw std::out_of_range("Position out of range");
  }
}

std::size_t Lattice::Population() const {
  std::size_t population = 0;
  for (const auto& row : cells_) {
    for (const auto& cell : row) {
      if (cell->getState() == '1') {
        ++population;
      }
    }
  }
  return population;
}

void Lattice::saveToFile(const std::string& fileName) const {
  std::ofstream file(fileName);
  if (!file) {
    std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
    return;
  }
  file << rows_ << " " << cols_ << "\n";
  for (const auto& row : cells_) {
    for (const auto& cell : row) {
      file << (cell->getState() == '1' ? '1' : '0') << " ";
    }
    file << "\n";
  }
  file.close();
}