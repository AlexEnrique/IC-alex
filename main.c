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

// random number generator file
#include "random_generator.h"

// structure of all observables
#include "observables.h"

unsigned int n;
// functions used
#include "functions.h"

// Consants declared with #define used in the program
#include "extern_defs_var.h"

int main () {
  // Declaration of variables (and others structures)
  unsigned int size; // 'n' is the number of sites in each direction and size == Nx*Nx == n^2
  long int **lattice;
  double T, dT, minT, *E, *M, avgE, avgM;
  struct lattice_position pos;
  struct type_observables obsrv;

  // Initialization of variables (and others)
  n = N_LATTICE_TEST;
  size = pow(n,2);
  dT = DELTA_T;
  T = INITIAL_TEMPERATURE + dT; // dT é descontado no inicio do while abaixo
  minT = MIN_TEMPERATURE;

  E = malloc(MAX_MC_LOOPS * sizeof(*E));
  M = malloc(MAX_MC_LOOPS * sizeof(*M));

  lattice = malloc(n * sizeof(**lattice));
  for (unsigned int i = 0; i < n; i++) {
    lattice[i] = malloc(n * sizeof(**lattice));
  }

  // Create and initialize lattice with random spins variables
  startRNG();
  initialize(&lattice, n);

  // file to store the calculations
  FILE *filePtr = fopen(FILE_NAME, "w");

  showCriticalTemperature(0); // 0 == no, 1 == yes
  while ((T -= dT) > minT-dT) {
    beta = 1/(KB * T); //k == 1

    // Float the spins for disregarding transient states
    transientFloatSpins(&lattice, size);
    obsrv.energy = -totalEnergy(lattice);
    obsrv.magnetization = totalMagnetization(lattice);

    // Monte Carlo loop
    for (unsigned int i = 0; i < MAX_MC_LOOPS; i++) {
      // Metropolis (Fluctuations) loops
      for (unsigned int j = 0; j < size; j++) {
        raffleRandomPosition(&pos);
        if ( spinFlipped(pos, &lattice) )
          adjustObservables(&obsrv, lattice[pos.x][pos.y]);

      }

      // Store the new observables
      E[i] = obsrv.energy;
      M[i] = obsrv.magnetization;
    }

    avgE = sum(E, MAX_MC_LOOPS)/MAX_MC_LOOPS;
    avgE /= size; // avgE per site

    avgM = sum(M, MAX_MC_LOOPS)/MAX_MC_LOOPS;
    avgM /= size;

    // output data
    // printing T, <E>, |<M>|
    fprintf(filePtr, "%.1lf\t%.3lf\t%.3lf\n", T, avgE, fabs(avgM));
    printf("%.2lf\t%.3lf\t%.3lf\n", T, avgE, fabs(avgM)); // To se where the program is
  }

  // clossing/cleaning files, pointers, etc.
  for (unsigned int i = 0; i < n; i++) {
    free(lattice[i]);
  }
  free(lattice);
  free(E);
  free(M);
  fclose(filePtr);
  stopRNG();

  // plot data
  // system("gnuplot < scr.gnu --persist");

  printf("\a");
  return 0;
}
