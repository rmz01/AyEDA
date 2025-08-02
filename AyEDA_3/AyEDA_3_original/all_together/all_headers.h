#include <iostream>
#include <vector>
#include <fstream>
#include <stdarg.h>

using State = unsigned char;
typedef int Coor_t;


class Cell;
class Lattice;
class Position;
class FactoryCell;

class Cell {
public:
    virtual ~Cell() {}
    Cell(Position& position, const State& state) : position_(position), state_(state) {}
    State getState() const { return state_; }
    void setState(State state) { state_ = state; }
    virtual void nextState(const Lattice& reticulo) = 0;
    virtual void updateState() { state_ = nextState_; }
    friend std::ostream& operator<<(std::ostream& os, Cell& cell);

protected:
    virtual void display(std::ostream&) = 0;
    Position& position_;
    State state_;
    State nextState_;
};

// Clase ACE base --------------------------------------------------------------------------------

class CellACE: public Cell {
  public:
  CellACE(Position& position, const State& state) : Cell(position, state) {}
};

// Clase ACE 110 --------------------------------------------------------------------------------

class CellACE110: public CellACE {
  public:
    CellACE110(Position& position, const State& state) : CellACE(position, state) {}
    void nextState(const Lattice& reticulo);
    void updateState();
    void display(std::ostream& os);
};

// Clase ACE 30 --------------------------------------------------------------------------------

class CellACE30: public CellACE {
  public:
    CellACE30(Position& position, const State& state) : CellACE(position, state) {}
    void nextState(const Lattice& reticulo);
    void updateState();
    void display(std::ostream& os);
};


// Clase Life base --------------------------------------------------------------------------------

class CellLife: public Cell {
  public:
  CellLife(Position& position, const State& state) : Cell(position, state) {}
};

// Clase Life 23_3 --------------------------------------------------------------------------------

class CellLife23_3: public CellLife {
  public:
    CellLife23_3(Position& position, const State& state) : CellLife(position, state) {}
    void nextState(const Lattice& reticulo);
    void updateState();
    void display(std::ostream& os);
};

// Clase Life 51_346 --------------------------------------------------------------------------------

class CellLife51_346: public CellLife {
  public:
    CellLife51_346(Position& position, const State& state) : CellLife(position, state) {}
    void nextState(const Lattice& reticulo);
    void updateState();
    void display(std::ostream& os);
};


// Clase FactoryCell base --------------------------------------------------------------------------------

class FactoryCell {
  public:
  FactoryCell() {}
  virtual Cell* createCell(Position& position, const State& state) = 0;
};

// Clase FactoryCell ACE110 --------------------------------------------------------------------------------

class FactoryCellACE110: public FactoryCell {
  public:
  FactoryCellACE110() {}
  Cell* createCell(Position& position, const State& state) override {
    return new CellACE110(position, state);
  }
};

// Clase FactoryCell ACE30 --------------------------------------------------------------------------------

class FactoryCellACE30: public FactoryCell {
  public:
  Cell* createCell(Position& position, const State& state) override {
    return new CellACE30(position, state);
  }
};

// Clase FactoryCell Life23_3 --------------------------------------------------------------------------------

class FactoryCellLife23_3: public FactoryCell {
  public:
  Cell* createCell(Position& position, const State& state) override {
    return new CellLife23_3(position, state);
  }
};

// Clase FactoryCell Life51_346 --------------------------------------------------------------------------------

class FactoryCellLife51_346: public FactoryCell {
  public:
  Cell* createCell(Position& position, const State& state) override {
    return new CellLife51_346(position, state);
  }
};

class Lattice {
  public:
    virtual ~Lattice() {} // Destructor virtual para permitir la eliminación segura a través de punteros de tipo base
    virtual Cell& operator[](Position&) const = 0;
    virtual void nextGeneration() = 0;
    virtual std::size_t Population() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);
    friend std::ofstream& operator<<(std::ofstream& os, const Lattice& lattice);

  protected:
    virtual std::ostream& display(std::ostream& os) const = 0;
    virtual std::ofstream& displayfile(std::ofstream& os) const = 0;
};


// Clase 1D --------------------------------------------------------------------------------

class Lattice1D: public Lattice {
  public:
    Lattice1D(std::fstream& file, FactoryCell& factory);
    Lattice1D(const int& size, FactoryCell& factory);
    virtual ~Lattice1D();
    void nextGeneration();
    std::size_t Population() const;
  protected:
    std::ostream& display(std::ostream& os) const;
    std::ofstream& displayfile(std::ofstream& os) const;
    std::vector<Cell*> lattice_;
    int size_;
};

// Clase open --------------------------------------------------------------------------------

class Lattice1D_open: public Lattice1D {
  public:
    Lattice1D_open(const int& size, FactoryCell& factory, bool open_type);
    Lattice1D_open(std::fstream& file, FactoryCell& factory, bool open_type);
    ~Lattice1D_open();
    Cell& operator[](Position& position) const;
  
  private:
    bool open_type_; // 0: open, 1: periodic
    Cell* border_;
};

// Clase periodic --------------------------------------------------------------------------------

class Lattice1D_periodic: public Lattice1D {
  public:
    Lattice1D_periodic(const int& size, FactoryCell& factory) : Lattice1D(size, factory) {}
    Lattice1D_periodic(std::fstream& file, FactoryCell& factory) : Lattice1D(file, factory) {}
    Cell& operator[](Position& position) const;
};


// Clase 2D --------------------------------------------------------------------------------

class Lattice2D: public Lattice {
  public:
    Lattice2D(std::fstream& file, FactoryCell& factory);
    Lattice2D(const int& rows, const int& columns, FactoryCell& factory);
    virtual ~Lattice2D();
    virtual void nextGeneration();
    std::size_t Population() const;

  protected:
    std::ostream& display(std::ostream& os) const;
    std::ofstream& displayfile(std::ofstream& os) const;
    std::vector<std::vector<Cell*>> lattice_;
    int rows_;
    int columns_;
};

// Clase reflective --------------------------------------------------------------------------------

class Lattice2D_reflective: public Lattice2D {
  public:
    Lattice2D_reflective(std::fstream& file, FactoryCell& factory) : Lattice2D(file, factory) {}
    Lattice2D_reflective(const int& rows, const int& columns, FactoryCell& factory) : Lattice2D(rows, columns, factory) {}
    Cell& operator[](Position& position) const;
};

// Define aquí las clases CellACE, CellACE110, CellACE30, CellLife, CellLife23_3, CellLife51_346, FactoryCell, FactoryCellACE110, FactoryCellACE30, FactoryCellLife23_3, FactoryCellLife51_346, Lattice, Lattice1D, Lattice1D_open, Lattice1D_periodic, Lattice2D y Lattice2D_reflective

class Position {
public:
    virtual Coor_t operator[](unsigned int) const = 0;
};

template <int Dim=2, class Coordinate_t=int>
class PositionDim: public Position {
public:
    PositionDim(int sz, ...) {
        va_list vl;
        va_start(vl, sz);
        for(int d=0; d<Dim; d++) {
            Coordinates[d] = va_arg(vl, Coor_t);
        }
        va_end(vl);
    }
    Coor_t operator[](unsigned int i) const {
        try {
            return Coordinates[i];
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

private:
    Coor_t Coordinates[Dim];
};