#include <math.h>

#ifndef EXT_VAR
#define EXT_VAR

#define MAX_MC_LOOPS 10000
#define MAX_METR_LOOPS 100 // change to size of the lattice (at the final version)?
#define MAX_TRANSIENT 1000
#define INITIAL_TEMPERATURE 5.0
#define MIN_TEMPERATURE 0.5
#define DELTA_T 0.1
#define TC 2.5
#define N_LATTICE_TEST 5
#define KB 1.38064852E-23 // SI unsits
// #define J (double) TC/2 * KB*log(1+sqrt(2)
#define J 1
// #define INITIAL_TEMPERATURE 1e4 * (2*J / (KB*log(1+sqrt(2))))
// #define MIN_TEMPERATURE INITIAL_TEMPERATURE/1e8
// #define DELTA_T (INITIAL_TEMPERATURE - MIN_TEMPERATURE)/1e2
#define FILE_NAME "teste.dat"

#endif
