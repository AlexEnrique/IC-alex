#include <math.h>

#ifndef EXT_VAR
#define EXT_VAR

#define MAX_MC_LOOPS 1000
#define MAX_METR_LOOPS 1000 // change to size of the lattice (at the final version)?
#define INITIAL_TEMPERATURE 15.0
#define DELTA_T 0.01
#define TC 2.5
#define MIN_TEMPERATURE 0.1
#define N_LATTICE_TEST 5
#define KB 1.38064852E-23 // SI unsits
#define J (double) TC/2 * KB*log(1+sqrt(2))
// #define J 1
#define FILE_NAME "teste.dat"

#endif
