#include <math.h>

#ifndef EXT_VAR
#define EXT_VAR

#define MAX_MC_LOOPS 1000
#define MAX_METR_LOOPS 100 // change to size of the lattice (at the final version)?
#define MAX_TRANSIENT 5
// #define INITIAL_TEMPERATURE 2E10
// #define MIN_TEMPERATURE 1E5
// #define DELTA_T 0.1
// #define TC 2.5
#define N_LATTICE_TEST 5
#define KB 1.38064852E-23 // SI unsits
// #define J (double) TC/2 * KB*log(1+sqrt(2)
#define J 1
#define INITIAL_TEMPERATURE 100 * (2*J / (KB*log(1+sqrt(2))))
#define MIN_TEMPERATURE INITIAL_TEMPERATURE/1000
#define DELTA_T (INITIAL_TEMPERATURE - MIN_TEMPERATURE)/100
#define FILE_NAME "teste.dat"

#endif
