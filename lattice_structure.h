#ifndef LATTICE_STRUCT
#define LATTICE_STRUCT

typedef struct LatticePosition {
  unsigned int x;
  unsigned int y;
} LatticePosition;

typedef struct SpinsLattice {
  LatticePosition pos;
  unsigned int Nx;
  unsigned int Ny;
  unsigned int size;
  long int **spin;

  // Functions pointers
  void (*memSpinsAlloc)();
  void (*initSpinsRandomly)();
  void (*floatSpins)();
  void (*choseRandomPosition)();
  void (*freeMemory)();
  void (*printLattice)();
  short (*flipSpin)();
} SpinsLattice;

#endif
