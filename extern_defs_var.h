#include <math.h>

#ifndef EXT_VAR
#define EXT_VAR

#define MAX_MC_LOOPS 10000
#define MAX_METR_LOOPS 100 // change to size of the lattice (at the final version)?
#define MAX_TRANSIENT 1000
#define N_LATTICE_TEST 2

// #define J (double) TC/2 * KB*log(1+sqrt(2)
// #define KB 1.38064852E-23 // SI unsits
#define J -1
#define KB 1
#define INITIAL_TEMPERATURE 5
#define MIN_TEMPERATURE 0.5
#define DELTA_T 0.05
#define TC 2.5
// #define INITIAL_TEMPERATURE 1e2 * (-2*J / (KB*log(1+sqrt(2))))
// #define MIN_TEMPERATURE 1e-7 * (-2*J / (KB*log(1+sqrt(2))))
// #define DELTA_T (INITIAL_TEMPERATURE - MIN_TEMPERATURE)/1e4

#define FILE_NAME "obsrv2.dat"
#define BUFF_SIZE 70

#endif
