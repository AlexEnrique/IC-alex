#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random_generator.h"
#include "type_observables.h"
#include "extern_defs_var.h"

#ifndef FUNCTIONS
#define FUNCTIONS

// move this global variable to an extern file or remove it
double dE, beta;
unsigned int n = N_LATTICE_TEST;

struct lattice_position {
  /* Using modular arithmetics, periodic boundary  *
   * conditions can be performed. This is why just *
   * using unsigned integer variables for x and y  */
  unsigned int x;
  unsigned int y;
};

// All functions ======================================================
// Functions of the 'random_generator' header
unsigned long int rdtsc();
void startRNG();
void stopRNG();

// Functions of this header ============================================
double deltaE(struct lattice_position pos, long int **lattice);
double sum(double *arr, unsigned int lenght);
short spinFlipped(struct lattice_position pos, long int ***lattice);
void raffleRandomPosition(struct lattice_position *pos);
void transientFloatSpins(long int ***lattice, unsigned int size);
void adjustObservables(struct type_observables *obsrv);
void initialize(long int ***lattice, unsigned int n);
void printLattice(long int **lattice, unsigned int n);
double totalEnergy(long int **lattice);
// ======================================================================

void initialize(long int ***lattice, unsigned int n) {
  // Equaly distributed random initialization
  unsigned int randomNo;

  for (unsigned int x = 0; x < n; x++) {
    for (unsigned int y = 0; y < n; y++) {
      // generates an unsigned integer in the interval [0:10)
      randomNo = gsl_rng_uniform_int(rng, 10);
      (*lattice)[x][y] = ((randomNo < 5) ? -1 : 1);
    }
  }

}

void transientFloatSpins(long int ***lattice, unsigned int size) {
  struct lattice_position pos;

  // change this 15 to something meaningful
  for (unsigned int i = 0; i < MAX_TRANSIENT; i++) {
    for (unsigned int j = 0; j < size; j++) {
      raffleRandomPosition(&pos);
      spinFlipped(pos, lattice);
    }
  }
}

void raffleRandomPosition(struct lattice_position *pos) {
  /* the range of 'x' and 'y' in lattice[x][y] is  *
   * from 0 (inclusive) to n (exclusive), like the *
   * gsl_rng_uniform_int() function above.         */
  pos->x = gsl_rng_uniform_int(rng, n);
  pos->y = gsl_rng_uniform_int(rng, n);
}

short spinFlipped(struct lattice_position pos, long int ***lattice) {
  if ((dE = deltaE(pos, *lattice)) < 0 || gsl_rng_uniform(rng) < exp(-beta*dE)) {
    (*lattice)[pos.x][pos.y] *= -1;
    return 1;
  }

  // else (if not flipped):
  return 0;
}

double deltaE(struct lattice_position pos, long int **lattice) {
  short neigbSum = 0;
  /* periodic boundary conditions:                              *
   * ((pos.x+1 == n) % n) == 0 and ((pos.x-1 == -1) % n) == n-1 */
  neigbSum += lattice[(pos.x-1)%n][pos.y];
  neigbSum += lattice[(pos.x+1)%n][pos.y];
  neigbSum += lattice[pos.x][(pos.y-1)%n];
  neigbSum += lattice[pos.x][(pos.y+1)%n];

  return ( (double)(-2*J) * (lattice[pos.x][pos.y]) * neigbSum );
}

double sum(double *arr, unsigned int lenght) {
  double S = 0;
  for (unsigned int i = 0; i < lenght; i++)
    S += arr[i];

  return S;
}

// typedef struct type_observables defined in "type_observables.h"
void adjustObservables(struct type_observables *obsrv) {
  obsrv->energy += dE;
}

double totalEnergy(long int **lattice) {
  // (B == 0): H = -J \sum_{i,j} s_i^j s_{i+1}^j + s_i^j s_i^{j+1}
  double H = 0;
  for (unsigned int i = 0; i < n; i++) { // Nx == Ny == n
    for (unsigned int j = 0; j < n; j++) {
      H += (-J) * lattice[i][j] * (lattice[(i+1)%n][j] + lattice[i][(j+1)%n]);
    }
  }

  return H;
}

void printLattice(long int **lattice, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      char c = (lattice[i][j] > 0) ? '+' : '-';
      printf("%c ", c);
    }
    printf("\n");
  }
  printf("\n");
}

#endif
