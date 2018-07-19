/* Main code file
 * Comments will be added after...
 * Created by: Alex Enrique Crispim
 * Date: ...
 * Adaptaded from: ...
 * e-mail: ecsp.alex@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

// Move this defs to a separated file after
#define MAX_MC_LOOPS 10000
#define MAX_METR_LOOPS 10000 // change to size of the lattice (at the final version)?
#define INITIAL_TEMPERATURE 5.0
#define DELTA_T 0.1
#define MIN_TEMPERATURE 0.5
#define N_LATTICE_TEST 3

struct lattice_position {
  /* Using modular arithmetics, periodic boundary  *
   * conditions can be performed. This is why just *
   * using unsigned integer variables for x and y  */
  unsigned int x;
  unsigned int y;
}

int main () {
  // Declaration of variables (and others structures)
  unsigned int n, size; // número de sítios em cada dimensão
  short **lattice;
  double T, dT, minT, tempE, *E, avgE;
  lattice_position pos;

  // Initialization of variables (and others)
  n = N_LATTICE_TEST;
  size = pow(n,2);
  T = INITIAL_TEMPERATURE;
  dT = DELTA_T;
  minT = MIN_TEMPERATURE;

  E = malloc(MAX_MC_LOOPS * sizeof(*E));

  lattice = malloc(n * sizeof(**lattice));
  for (unsigned int i = 0; i < n; i++) {
    lattice[i] = malloc(n * sizeof(**lattice));
  }

  // Create and initialize lattice with random spins variables
  initialize(&lattice, n);

  // file to store the calculations
  FILE *filePtr = fopen(FILE_NAME, "w");


  while (T > (minT - dT)) {
    // Float the spins for disregarding transient states
    transientFloatSpins(&lattice);

    // Observables tests for the program
    // M = totalMagnetization(&lattice);
    tempE = totalEnergy(&lattice);

    // Monte Carlo loop
    for (unsigned int i = 0; i < MAX_MC_LOOPS; i++) {
      // Metropolis (Fluctuation) loops
      for (unsigned int j = 0; j < MAX_METR_LOOPS; j++) {
        raffleRandomPosition(&pos);
        if (spinFlipped(pos, &lattice)) {
          adjustObservables(&tempE);
          // E += 2 * deltaE(lattice, pos);
        }
      }
      // Store the new observables
      E[i] = tempE;

    }
    avgE = sum(E)/MAX_MC_LOOPS;
    avgE /= size;

    // output data
    fprintf(filePtr, "%lf\t%lf\n", T, avgE);
    // Print T, <M> (per spin), <M^2> (per spin),
    // susceptibility (X) per spin, <E>, <E^2>, C (heat cap.)
  }

  fclose(filePtr);
  return 0;
}
