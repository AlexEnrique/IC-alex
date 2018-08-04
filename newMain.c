#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// random number generator file
#include "random_generator.h"

// structure of all observables
// #include "observables.h"

// those variables are used in the function header
double dE;
double beta; // beta == 1/(kT)
// functions used
#include "new_functions.h"

// Consants declared with #define used in the program
#include "extern_defs_var.h"

#include "lattice_structure.h"
#include "observables_structure.h"

int main () {
  unsigned int n = N_LATTICE_TEST;
  double T, dT, minT;
  SpinsLattice lattice = createLattice(n, n);
  Observables observables = createObservables();

  // Initialization of variables
  T = INITIAL_TEMPERATURE;
  dT = DELTA_T;
  minT = MIN_TEMPERATURE;

  // Initialization of structures
  startRNG(); // Starts the random number generator
  lattice.memSpinsAlloc(&lattice);
  lattice.initSpinsRandomly(&lattice);
  // lattice.printLattice(lattice);

  // File to output the data calculated
  FILE *filePtr = fopen(FILE_NAME, "w");

  showCriticalTemperature(0); // 0 == no, 1 == yes
  while ((T -=dT) > minT) {
    beta = 1/T; // k == 1

    // Float the spins for disregarding transient states
    lattice.floatSpins(&lattice);

    // Calculate the observables before the MC loop (for some temperature)
    observables.energy = totalEnergy(lattice);
    observables.magnetization = totalMagnetization(lattice);

    // Monte Carlo loop
    for (unsigned int i = 0; i < MAX_MC_LOOPS; i++) {
      // Metropolis loop
      for (unsigned int j = 0; j < lattice.size; j++) {
        lattice.choseRandomPosition(lattice);
        if ( lattice.flipSpin(&lattice) )
          observables.adjust(lattice, &observables);
          // printf("%lf\t%lf\n", observables.energy, observables.magnetization);
      } // end Metropolis loop

      // Store the new observables
      observables.E[i] = observables.energy;
      observables.M[i] = observables.magnetization;
    } // end monte carlo loop

    observables.average(lattice, &observables); // calcula avgE e avgM (e outros)

    // output data
    // printing T, <E>, |<M>|
    fprintf(filePtr, "%.1lf\t%.3lf\t%.3lf\n", T, observables.avgE, fabs(observables.avgM));
    printf("%.2lf\n", T); // this print is just to see in which Temperature is the program
  } // end while

  // the following commands desalocates the memory used
  stopRNG(); // stops random number generator
  lattice.freeMemory(&lattice);
  observables.freeMemory(&observables);
  fclose(filePtr);
  printf("\a");

  return 0;
}
