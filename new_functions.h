#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "random_generator.h"
#include "extern_defs_var.h"
#include "lattice_structure.h"
#include "observables_structure.h"

#ifndef FUNCTIONS
#define FUNCTIONS
// Functions of this header========================================
SpinsLattice createLattice(int Nx, int Ny);
Observables createObservables();
double deltaE(SpinsLattice lattice);
double totalEnergy(SpinsLattice lattice);
double totalMagnetization(SpinsLattice lattice);
double sum(double *arr, unsigned int lenght);
short flipSpin(SpinsLattice *this);
void memSpinsAlloc(SpinsLattice *this);
void initSpinsRandomly(SpinsLattice *this);
void floatSpins(SpinsLattice *this);
void choseRandomPosition(SpinsLattice this);
void latticeFreeMemory(SpinsLattice *this);
void adjustObservables(SpinsLattice lattice, Observables *this);
void average(SpinsLattice lattice, Observables *this);
void observablesFreeMemory(Observables *this);
void showCriticalTemperature(const short op);
// ================================================================

// Lattice functions
void memSpinsAlloc(SpinsLattice *this) {
  this->spin = malloc(this->Nx * sizeof(**this->spin));
  for (unsigned int x = 0; x < this->Nx; x++) {
    this->spin[x] = malloc(this->Ny * sizeof(**this->spin));
  }
}

void initSpinsRandomly(SpinsLattice *this) {
  unsigned int randomNo;

  for (unsigned int x = 0; x < this->Nx; x++) {
    for (unsigned int y = 0; y < this->Ny; y++) {
      // generates an unsigned integer in the interval [0:10)
      randomNo = gsl_rng_uniform_int(rng, 10);
      this->spin[x][y] = ( (randomNo < 5) ? -1 : 1 );
    }
  }
}

void floatSpins(SpinsLattice *this) {
  for (unsigned int i = 0; i < MAX_TRANSIENT; i++) {
    for (unsigned int j = 0; j < this->size; j++) {
      this->choseRandomPosition(*this);
      flipSpin(this);
    }
  }
}

void choseRandomPosition(SpinsLattice this) {
  this.pos.x = gsl_rng_uniform_int(rng, this.Nx);
  this.pos.y = gsl_rng_uniform_int(rng, this.Ny);
}

void printLattice(SpinsLattice this) {
  for (unsigned int i = 0; i < this.Nx; i++) {
    for (unsigned int j = 0; j < this.Ny; j++) {
      char c = (this.spin[i][j] > 0) ? '+' : '-';
      printf("%c ", c);
    }
    printf("\n");
  }
  printf("\n");
}


void latticeFreeMemory(SpinsLattice *this) {
  for (unsigned int i = 0; i < this->Nx; i++) {
    free(this->spin[i]);
  }
  free(this->spin);
}

SpinsLattice createLattice(int Nx, int Ny) {
  SpinsLattice _lattice;
  _lattice.Nx = Nx;
  _lattice.Ny = Ny;
  _lattice.size = Nx*Ny;
  _lattice.memSpinsAlloc = memSpinsAlloc;
  _lattice.initSpinsRandomly = initSpinsRandomly;
  _lattice.floatSpins = floatSpins;
  _lattice.choseRandomPosition = choseRandomPosition;
  _lattice.flipSpin = flipSpin;
  _lattice.freeMemory = latticeFreeMemory;
  _lattice.printLattice = printLattice;

  return _lattice;
}
// END lattice functions


// Observables functions
void adjustObservables(SpinsLattice lattice, Observables *this) {
  this->energy += dE;
  this->magnetization += 2 * lattice.spin[lattice.pos.x][lattice.pos.y];
}

void average(SpinsLattice lattice, Observables *this) {
  this->avgE = sum(this->E, MAX_MC_LOOPS) / MAX_MC_LOOPS;
  this->avgE /= lattice.size;

  this->avgM = sum(this->M, MAX_MC_LOOPS) / MAX_MC_LOOPS;
  this->avgM /= lattice.size;
}

void observablesFreeMemory(Observables *this) {
  free(this->E);
  free(this->M);
  free(this->SziArr);
  free(this->SziSzjArr);
  free(this->SxiArr);
  free(this->SxiSxjArr);
}

Observables createObservables() {
  Observables _observables;

  _observables.E = malloc(MAX_MC_LOOPS * sizeof(*_observables.E));
  _observables.M = malloc(MAX_MC_LOOPS * sizeof(*_observables.M));
  _observables.SziArr = malloc(MAX_MC_LOOPS * sizeof(*_observables.SziArr));
  _observables.SziSzjArr = malloc(MAX_MC_LOOPS * sizeof(*_observables.SziSzjArr));
  _observables.SxiArr = malloc(MAX_MC_LOOPS * sizeof(*_observables.SxiArr));
  _observables.SxiSxjArr = malloc(MAX_MC_LOOPS * sizeof(*_observables.SxiSxjArr));

  // functions
  _observables.adjust = adjustObservables;
  _observables.average = average;
  _observables.freeMemory = observablesFreeMemory;

  return _observables;
}
// END observables functions

double deltaE(SpinsLattice lattice) {
  short neigbSum = 0;
  /* periodic boundary conditions:                              *
   * ((pos.x+1 == n) % n) == 0 and ((pos.x-1 == -1) % n) == -1  *
   * and (pos.x - 1 + Nx) % Nx == Nx - 1                        */
  long int x = lattice.pos.x;
  long int y = lattice.pos.y;
  unsigned int Nx = lattice.Nx;
  unsigned int Ny = lattice.Ny;

  neigbSum += lattice.spin[(x - 1 + Nx) % Nx][y];
  neigbSum += lattice.spin[(x + 1) % Nx][y];
  neigbSum += lattice.spin[x][(y - 1 + Ny) % Ny];
  neigbSum += lattice.spin[x][(y + 1) % Ny];

  return ( (double)(2*J) * (-lattice.spin[x][y]) * neigbSum );
}

short flipSpin(SpinsLattice *this) {
  dE = deltaE(*this); // Declared after in the main.c file
  if (dE < 0 || gsl_rng_uniform(rng) < exp(-beta*dE)) {
    this->spin[this->pos.x][this->pos.y] *= -1;
    return 1; // 1 == yes, spin flipped
  }

  // else, if the spin doesn't flip
  return 0;
}

double totalEnergy(SpinsLattice lattice) {
  // (B == 0): H = -J \sum_{i,j} s_i^j s_{i+1}^j + s_i^j s_i^{j+1}
  unsigned int Nx = lattice.Nx;
  unsigned int Ny = lattice.Ny;
  double H = 0;

  for (unsigned int i = 0; i < Nx; i++) { // Nx == Ny == n
    for (unsigned int j = 0; j < Ny; j++) {
      H += (-J) * lattice.spin[i][j] * (lattice.spin[(i+1) % Nx][j] + lattice.spin[i][(j+1) % Ny]);
    }
  }

  return -H; // -H since J < 0
}

double totalMagnetization(SpinsLattice lattice) {
  double m = 0;
  for (unsigned int i = 0; i < lattice.Nx; i++)
    for (unsigned int j = 0; j < lattice.Ny; j++)
      m += lattice.spin[i][j];

  return m;
}

double sum(double *arr, unsigned int lenght) {
  double S = 0;
  for (unsigned int i = 0; i < lenght; i++) {
    S += *(arr + i);
  }

  return S;
}

void showCriticalTemperature(const short op) {
  if (op)
    printf("Critical Temperature: %.2e\n", (2*J / (KB*log(1+sqrt(2)))));
}

#endif
