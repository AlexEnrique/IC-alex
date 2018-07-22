#include <gsl/gsl_rng.h>

/* "gsl_rng *rng" creates an instance 'rng' of random number  *
 * of the type gsl_rng_ranlux389 (initialized in the          *
 * startRNG() function). It's an implementation of the        *
 * algorithm developed by Luscher, but modified to generate   *
 * number with a lower correlation than the original one      *
 * original algorithm.                                        */
const unsigned long int seed;
const gsl_rng *rng;

unsigned long int rdtsc();
void startRNG();
void stopRNG();

// Provides a (random) seed for the rng
unsigned long int rdtsc() {
   unsigned int lo, hi;
   __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
   return ((unsigned long int)hi << 32) | lo;
}

void startRNG() {
  seed = rdtsc();
  rng = gsl_rng_alloc(gsl_rng_ranlux389);
  gsl_rng_set(rng, seed);
}

void stopRNG() {
  gsl_rng_free(r);
}
