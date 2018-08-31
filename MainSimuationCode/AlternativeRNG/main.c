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
unsigned int jPos = 1;
// functions used
#include "functions.h"

// Consants declared with #define used in the program
#include "definitions.h"

#include "lattice_structure.h"
#include "observables_structure.h"

int main (int argc, char *argv[]) {
  unsigned int n = MAX_N;
  double T, dT, minT;
	char *filename = malloc(BUFF_SIZE * sizeof(*filename));
	char *dir = malloc(BUFF_SIZE * sizeof(*dir));
	char *command = malloc(BUFF_SIZE * sizeof(*command));

	// T = atof(*(argv + 1));
  // int j = atoi(*(argv + 1));

  startRNG(); // Starts the random number generator
  SpinsLattice lattice = createLattice(n, n);
  Observables observables = createObservables();

  // Initialization of variables
  dT = DELTA_T;
  T = INITIAL_TEMPERATURE + dT; // dT é descontado no inicio do 'while' abaixo
  minT = MIN_TEMPERATURE;

  // Initialization of structures
  lattice.memSpinsAlloc(&lattice);
  lattice.initSpinsInline(&lattice);
  // lattice.initSpinsRandomly(&lattice);

  // File to output the data calculated
  #define OBSRV_FOLDER "ObservablesData"
  snprintf(dir, BUFF_SIZE, "%s", OBSRV_FOLDER);
  snprintf(command, BUFF_SIZE, "if [ ! -d \"%s\" ]; then mkdir %s; fi", dir, dir);
  system(command);

  snprintf(dir, BUFF_SIZE, "%s/j=i+1", OBSRV_FOLDER);

  snprintf(command, BUFF_SIZE, "if [ ! -d \"%s\" ]; then mkdir %s; fi", dir, dir);
  system(command);

  snprintf(filename, BUFF_SIZE, "%s/simulation.dat", dir);
  FILE *filePtr = fopen(filename, "w");

  // Formating output file
  fprintf(filePtr, "#  T(K)  <E>    <|M|>     Szi    C(Sz)    Sxi    C(Sx)   Z1X2    X1Z2    Bell\n");
  fprintf(filePtr, "#  ---  ------  -----    -----   -----   -----   -----   -----  ------   -----\n");

	printf("-- Boltzmann constant = 1 --\n\n");
  showCriticalTemperature(0); // 0 == no, 1 == yes
  // for (int j = 1; j < n; j++) {
  while ((T -= dT) > minT) {
    beta = 1/T; // k == 1
		printf("Temperature set to %.3lf\n", T);

    // Float the spins for disregarding transient states
		printf("Process of thermalization...\n");
    lattice.floatSpins(&lattice);

    printf("Calculating observables...\n");

    // Calculate the observables before the MC loop (for some temperature)
    observables.energy = totalEnergy(lattice);
    observables.magnetization = totalMagnetization(lattice);

    observables.Szi = totalSzi(lattice);
    observables.Szj = totalSzj(lattice);
    observables.SziSzj = totalSziSzj(lattice);

    observables.Sxi = totalSxi(lattice);
    observables.Sxj = totalSxj(lattice);

    // Monte Carlo loop
    for (unsigned int i = 0; i < MAX_MC_LOOPS; i++) {
      // Metropolis loop
      for (unsigned int j = 0; j < lattice.size; j++) {
        lattice.choseRandomPosition(&lattice);
        if ( lattice.flipSpin(&lattice) )
          observables.adjust(lattice, &observables);
      } // end Metropolis loop


      // Store the new values
      observables.E[i] = observables.energy;
      observables.M[i] = fabs(observables.magnetization);

      observables.SziArr[i] = observables.Szi;
      observables.SzjArr[i] = observables.Szj;
      observables.SziSzjArr[i] = observables.SziSzj;

      observables.SxiArr[i] = observables.Sxi;
      observables.SxjArr[i] = observables.Sxj;
      observables.SxiSxjArr[i] = observables.Sxi * observables.Sxj;

      observables.Z1X2Arr[i] = observables.Szi * observables.Sxj;
      observables.X1Z2Arr[i] = observables.Sxi * observables.Szj;
    } // end monte carlo loop

    observables.average(lattice, &observables); // calcula avgE e avgM (e outros)
    observables.Bell = -sqrt(2) * observables.avgZ1X2 + observables.avgSxiSxj;

    // output data
    // formating output file
    fprintf(filePtr, "  %.2lf  ", T);
    if (observables.avgE >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.avgE);
    fprintf(filePtr, " %.3lf  ", observables.avgM);
    if (observables.avgSzi >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.avgSzi);
    if (observables.avgSziSzj - observables.avgSzi * observables.avgSzj >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.avgSziSzj - observables.avgSzi * observables.avgSzj);
    if (observables.avgSxi >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.avgSxi);
    if (observables.avgSxiSxj - observables.avgSxi * observables.avgSxj >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.avgSxiSxj - observables.avgSxi * observables.avgSxj);
    if (observables.avgZ1X2 >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.avgZ1X2);
    if (observables.avgX1Z2 >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.avgX1Z2);
    if (observables.Bell >= 0)
      fprintf(filePtr, " ");
    fprintf(filePtr, "%.3lf  ", observables.Bell);
    fprintf(filePtr, "\n");

		printf("Done for T=%.3lf!\n\n", T);
  } // end while

  // the following commands desalocates the memory used
  stopRNG(); // stops random number generator
  lattice.freeMemory(&lattice);
  observables.freeMemory(&observables);
  fclose(filePtr);
  // printf("\a");

  return 0;
}
