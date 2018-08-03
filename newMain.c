typedef struct latticePosition {
  unsigned int x;
  unsigned int y;
} latticePosition;

typedef struct SpinsLattice {
  latticePosition pos;
  unsigned int Nx;
  unsigned int Ny;
  unsigned int size;
  short **spin;

  void (*memSpinsAlloc)();
  void (*initializeSpinsRandom)();
  void (*floatSpins)();
} SpinsLattice;

void memSpinsAlloc() {
  printf("teste struct\n");
}

SpinsLattice createLattice(int Nx, int Ny) {
  SpinsLattice lat;
  lat.Nx = Nx;
  lat.Ny = Ny;
  lat.size = Nx*Ny;
  lat.memSpinsAlloc = memSpinsAlloc;
  // lat.initializeSpinsRandom = initializeSpinsRandom;

  return lat;
}

int main () {
  SpinsLattice lat = createLattice(2, 2);
  lat.memSpinsAlloc();
  return 0;
}
