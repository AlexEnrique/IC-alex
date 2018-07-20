/*
  Functions to implement:
    totalEnergy(&lattice)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random_generator.h"
#include "type_observables.h"

struct lattice_position {
  /* Using modular arithmetics, periodic boundary  *
   * conditions can be performed. This is why just *
   * using unsigned integer variables for x and y  */
  unsigned int x;
  unsigned int y;
}

// All functions ===============================================
// Functions of the 'random_generator' header
unsigned long int rdtsc();
void startRNG();
void stopRNG();

// Functions of this header =====================================
double totalEnergy(short **lattice)
double deltaE(lattice_position pos, short **lattice);
double sum(double *arr, unsigned int lenght);
short spinFlipped(lattice_position pos, short ***lattice);
void raffleRandomPosition(lattice_position *pos, unsigned int n);
void transientFloatSpins(short ***lattice, unsigned int size);
void adjustObservables(type_observables &obsrv, lattice_position posFlip, short **lattice);
void spinFlipped(lattice_position pos, short ***lattice);
void initialize(short ***lattice, unsigned int n);
// ===============================================================

void initialize(short ***lattice, unsigned int n) {
  // Equaly distributed random initialization
  unsigned int randomNo;

  for (unsigned int x = 0; x < n; x++) {
    for (unsigned int y = 0; y < n; y++) {
      // generates an unsigned integer in the interval [0:10)
      randomNo = gsl_rng_uniform_int(rng, 10);
      (*lattice)[x][y] = ((randomNo < 6) ? -1 : 1);
    }
  }

}

void transientFloatSpins(short ***lattice, unsigned int size) {
  lattice_position pos;

  // change this SMTHG to something meaningful
  for (unsigned int i = 0; i < SMTHG; i++) {
    for (unsigned int j = 0; j < size; j++) {
      raffleRandomPosition(&pos);
      spinFlipped(pos, &lattice);
    }
  }
}

void raffleRandomPosition(lattice_position *pos, unsigned int n) {
  /* the range of 'x' and 'y' in lattice[x][y] is  *
   * from 0 (inclusive) to n (exclusive), like the *
   * gsl_rng_uniform_int() function above.         */
  pos->x = gsl_rng_uniform_int(rng, n);
  pos->y = gsl_rng_uniform_int(rng, n);
}

short spinFlipped(lattice_position pos, short ***lattice) {
  if (deltaE(pos, *lattice) > 0) {
    (*lattice)[pos.x][pos.y] *= -1;
    return 1;
  }

  // else (if not flipped):
  return 0;
}

double deltaE(lattice_position pos, short **lattice) {
  short neigbSum = 0;
  /* periodic boundary conditions:                              *
   * ((pos.x+1 == n) % n) == 0 and ((pos.x-1 == -1) % n) == n-1 */
  neigbSum += lattice[(pos.x-1)%n][pos.y];
  neigbSum += lattice[(pos.x+1)%n][pos.y];
  neigbSum += lattice[pos.x][(pos.y-1)%n];
  neigbSum += lattice[pos.x][(pos.y+1)%n];

  // J = 1 (def.)
  return ( (-2) * (lattice[pos.x][pos.y]) * neigbSum );
}

double sum(double *arr, unsigned int lenght) {
  double S = 0;

  for (unsigned int i = 0; i < lenght; i++) {
    S += arr[i];
  }

  return S;
}

// typedef struct type_observables defined in "type_observables.h"
void adjustObservables(type_observables &obsrv, lattice_position posFlip, short **lattice) {
  obsrv->energy += deltaE(posFlip, lattice);
}

double totalEnergy(short **lattice) {
  
}
