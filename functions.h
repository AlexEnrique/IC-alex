/*
  Functions to implement:
    transientFloatSpins(&lattice)
    totalEnergy(&lattice)
    raffleRandomPosition(&pos)
      - store the pos's already flipped?
    spinFlipped(pos, &lattice)
    adjustObservables(E, ...)
    sum(E)

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random_generator.h"

struct lattice_position {
  /* Using modular arithmetics, periodic boundary  *
   * conditions can be performed. This is why just *
   * using unsigned integer variables for x and y  */
  unsigned int x;
  unsigned int y;
}

// All functions
// Functions of the 'random_generator' header
unsigned long int rdtsc();
void startRNG();
void stopRNG();

// Functions of this header
short spinFlipped(lattice_position pos, short ***lattice);
void initialize(short ***lattice, unsigned int n);
void transientFloatSpins(short ***lattice, size);
void raffleRandomPosition(lattice_position *pos);
void spinFlipped(lattice_position pos, short ***lattice);

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

void transientFloatSpins(short ***lattice, size) {
  lattice_position pos;
  for (unsigned int i = 0; i < SMTHG; i++) {
    for (unsigned int j = 0; j < size; j++) {
      raffleRandomPosition(&pos);
      spinFlipped(pos, &lattice);
    }
  }
}

void raffleRandomPosition(lattice_position *pos) {
  /* the range of 'x' and 'y' in lattice[x][y] is  *
   * from 0 (inclusive) to n (exclusive), like the *
   * gsl_rng_uniform_int() function above.         */
  (*pos).x = gsl_rng_uniform_int(rng, n);
  (*pos).y = gsl_rng_uniform_int(rng, n);
}

void spinFlipped(lattice_position pos, short ***lattice) {

}
