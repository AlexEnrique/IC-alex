#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// random number generator file
#include "random_generator.h"

// structure of all observables
#include "observables.h"

unsigned int n;
double dE;
// functions used
#include "new_functions.h"

// Consants declared with #define used in the program
#include "extern_defs_var.h"


typedef struct latticePosition {
  unsigned int x;
  unsigned int y;
} latticePosition;

typedef struct SpinsLattice {
  latticePosition pos;
  unsigned int Nx;
  unsigned int Ny;
  unsigned int size;
  long int **spin;

  void (*memSpinsAlloc)();
  void (*initializeSpinsRandom)();
  void (*floatSpins)();
  void (*choseRandomPosition)();
  short (*flipSpin)();
} SpinsLattice;

// void memSpinsAlloc(SpinsLattice this);
// void initializeSpinsRandom(SpinsLattice this);
// void floatSpins(SpinsLattice this);
// void choseRandomPosition(spinFlipped this);
// short flipSpin(spinFlipped this);

void memSpinsAlloc(SpinsLattice this) {
  this.spin = malloc(this.Nx * sizeof(**this.spin));
  for (unsigned int x = 0; x < this.Nx; x++)
    this.spin[x] = malloc(this.Ny * sizeof(**this.spin));
}

void initializeSpinsRandom(SpinsLattice this) {
  unsigned int randomNo;

  for (unsigned int x = 0; x < this.Nx; x++) {
    for (unsigned int y = 0; y < this.Ny; y++) {
      // generates an unsigned integer in the interval [0:10)
      printf("x, y: %d, %d\n", x, y);
      randomNo = gsl_rng_uniform_int(rng, 10);
      this.spin[x][y] = ( (randomNo < 5) ? -1 : 1 );
    }
  }
}

void floatSpins(SpinsLattice this) {
  for (unsigned int i = 0; i < this.Nx; i++) {
    for (unsigned int j = 0; j < this.Ny; j++) {
      this.choseRandomPosition();
      this.flipSpin();
    }
  }
}

void choseRandomPosition(SpinsLattice this) {
  this.pos.x = gsl_rng_uniform_int(rng, this.Nx);
  this.pos.y = gsl_rng_uniform_int(rng, this.Ny);
}

double deltaE(latticePosition pos, long int **lattice) {
  short neigbSum = 0;
  /* periodic boundary conditions:                              *
   * ((pos.x+1 == n) % n) == 0 and ((pos.x-1 == -1) % n) == -1  */
  neigbSum += lattice[(pos.x - 1 + n) % n][pos.y];
  neigbSum += lattice[(pos.x + 1) % n][pos.y];
  neigbSum += lattice[pos.x][(pos.y - 1 + n) % n];
  neigbSum += lattice[pos.x][(pos.y + 1) % n];

  return ( (double)(2*J) * -lattice[pos.x][pos.y] * neigbSum );
}

short flipSpin(SpinsLattice this) {
  dE = deltaE(this.pos, this.spin);
}

SpinsLattice createLattice(int Nx, int Ny) {
  SpinsLattice _lattice;
  _lattice.Nx = Nx;
  _lattice.Ny = Ny;
  _lattice.size = Nx*Ny;
  _lattice.memSpinsAlloc = memSpinsAlloc;
  _lattice.initializeSpinsRandom = initializeSpinsRandom;
  _lattice.floatSpins = floatSpins;
  _lattice.choseRandomPosition = choseRandomPosition;
  _lattice.flipSpin = flipSpin;

  return _lattice;
}

int main () {
  SpinsLattice lattice = createLattice(7, 3);

  startRNG();
  lattice.memSpinsAlloc();
  lattice.initializeSpinsRandom();

  printf("\n\n");
  for (int y = 0; y < lattice.Ny; y++) {
    for (int x = 0; x < lattice.Nx; x++) {
      printf("%d ", lattice.spin[x][y]);
    }
    printf("\n");
  }

  for (int x = 0; x < lattice.Nx; x++)
    free(lattice.spin[x]);
  free(lattice.spin);


  stopRNG();
  return 0;
}
