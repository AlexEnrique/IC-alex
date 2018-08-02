#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random_generator.h"
#include "observables.h"
#include "extern_defs_var.h"

#ifndef FUNCTIONS
#define FUNCTIONS

// move this global variable to an extern file or remove it
double dE, beta;

struct lattice_position {
  /* Using modular arithmetics, periodic boundary  *
   * conditions can be performed. This is why I am *
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
double totalMagnetization(long int **lattice);
double totalEnergy(long int **lattice);
double sum(double *arr, unsigned int lenght);
short spinFlipped(struct lattice_position pos, long int ***lattice);
void raffleRandomPosition(struct lattice_position *pos);
void transientFloatSpins(long int ***lattice, unsigned int size);
void adjustObservables(struct type_observables *obsrv, int spin);
void initialize(long int ***lattice, unsigned int n);
void printLattice(long int **lattice, unsigned int n);
void showCriticalTemperature(const short op) ;
// ======================================================================

void initialize(long int ***lattice, unsigned int n) {
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

  // change this MAX_TRANSIENT to something meaningful
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
    (*lattice)[pos.x][pos.y] *= -1; // flip at pos.x, pos.y
    return 1;
  }

  // (if not flipped):
  return 0;
}

double deltaE(struct lattice_position pos, long int **lattice) {
  short neigbSum = 0;
  /* periodic boundary conditions:                              *
   * ((pos.x+1 == n) % n) == 0 and ((pos.x-1 == -1) % n) == -1  */
  neigbSum += lattice[(pos.x - 1 + n) % n][pos.y];
  neigbSum += lattice[(pos.x + 1) % n][pos.y];
  neigbSum += lattice[pos.x][(pos.y - 1 + n) % n];
  neigbSum += lattice[pos.x][(pos.y + 1) % n];

  return ( (double)(2*J) * -lattice[pos.x][pos.y] * neigbSum );
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

double totalMagnetization(long int **lattice) {
  double m = 0;
  for (unsigned int i = 0; i < n; i++)
    for (unsigned int j = 0; j < n; j++)
      m += lattice[i][j];

  return m;
}

// struct type_observables defined in "type_observables.h"
void adjustObservables(struct type_observables *obsrv, int spin) {
  obsrv->energy += dE;
  obsrv->magnetization += 2 * spin;
}

double sum(double *arr, unsigned int lenght) {
  double S = 0;
  for (unsigned int i = 0; i < lenght; i++) {
    S += *(arr + i);
  }

  return S;
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

void showCriticalTemperature(const short op) {
  if (op)
    printf("Critical Temperature: %.2e\n", (2*J / (KB*log(1+sqrt(2)))));
}

#endif
