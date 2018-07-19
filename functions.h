/*
  Functions to implement:
    initialize(&lattice)
    floatSpins(&lattice)
    totalEnergy(&lattice)
    raffleRandomPosition(&pos)
    spinFlipped(pos, &lattice)
    adjustObservables(E, ...)
    sum(E)

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

// Provides a (random) seed for the rng in initialize function
unsigned long int rdtsc() {
   unsigned int lo, hi;
   __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
   return ((unsigned long int)hi << 32) | lo;
}

void initialize(short ***lattice, unsigned int n) {
  // Equaly distributed random initialization

  /* "gsl_rng *r" creates an instance (r) of random number *
   * of the type gsl_rng_ranlux389. It's an implementation *
   * of the algorithm developed by Luscher, but modified   *
   * to generate number with a lower correlation than the  *
   * original algorithm.                                   */

  unsigned long int seed = rdtsc();
  unsigned int randomNo;
  gsl_rng *r = gsl_rng_alloc(gsl_rng_ranlux389);
  gsl_rng_set(r, seed);

  for (unsigned int x = 0; x < n; x++) {
    for (unsigned int y = 0; y < n; y++) {
      // generates an unsigned integer in the interval [0:10)
      randomNo = gsl_rng_uniform_int(r, 10);
      (*lattice)[x][y] = ((randomNo < 6) ? -1 : 1);
    }
  }

  gsl_rng_free(r);
}
