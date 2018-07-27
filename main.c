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
// #include "extern_func_declarations.h"
#include "random_generator.h"
#include "type_observables.h"
#include "functions.h"

// Move those defs to a separated file after
#define MAX_MC_LOOPS 10000
#define MAX_METR_LOOPS 10000 // change to size of the lattice (at the final version)?
#define INITIAL_TEMPERATURE 5.0
#define DELTA_T 0.1
#define MIN_TEMPERATURE 0.5
#define N_LATTICE_TEST 3
#define FILE_NAME "teste.dat"

// struct lattice_position {
//   /* Using modular arithmetics, periodic boundary  *
//    * conditions can be performed. This is why just *
//    * using unsigned integer variables for x and y  */
//   unsigned int x;
//   unsigned int y;
// };

// All functions ============================================================
// Functions of the 'random_generator' header
// unsigned long int rdtsc();
// void startRNG();
// void stopRNG();
// // Functions of the "function.h" header =====================================
// double deltaE(struct lattice_position pos, short **lattice);
// double sum(double *arr, unsigned int lenght);
// short spinFlipped(struct lattice_position pos, short ***lattice);
// void raffleRandomPosition(struct lattice_position *pos);
// void transientFloatSpins(short ***lattice, unsigned int size);
// void adjustObservables(struct type_observables *obsrv, struct lattice_position posFlip, short **lattice);
// void initialize(short ***lattice, unsigned int n);
// double totalEnergy(short **lattice);
// ===========================================================================

int main () {
  // Declaration of variables (and others structures)
  unsigned int n, size; // número de sítios em cada dimensão
  short **lattice;
  double T, dT, minT, *E, avgE;
  struct lattice_position {double x; double y;} pos;
  struct type_observables obsrv;

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
  startRNG();
  initialize(&lattice, n);

  // file to store the calculations
  FILE *filePtr = fopen(FILE_NAME, "w");

  while (T > minT) {
    // Float the spins for disregarding transient states
    transientFloatSpins(&lattice, size);

    // Observables tests for the program
    obsrv.energy = totalEnergy(lattice);

    // Monte Carlo loop
    for (unsigned int i = 0; i < MAX_MC_LOOPS; i++) {
      // Metropolis (Fluctuations) loops
      for (unsigned int j = 0; j < MAX_METR_LOOPS; j++) {
        raffleRandomPosition(&pos);
        if (spinFlipped(pos, &lattice)) {
          adjustObservables(&obsrv, pos, lattice);
          // To add others observables after
        }
      }
      // Store the new observables
      E[i] = obsrv.energy;

    }
    avgE = sum(E, MAX_MC_LOOPS)/MAX_MC_LOOPS;
    avgE /= size; // avgE per site

    // output data
    // print T, <E>
    // fprintf(filePtr, "%lf\t%lf\n", T, avgE);
    printf("%lf\t%lf\n", T, avgE); // To test
  }

  fclose(filePtr);
  stopRNG();

  return 0;
}
