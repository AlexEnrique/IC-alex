#ifndef OBSERVABLES_STRUCT
#define OBSERVABLES_STRUCT

typedef struct Observables {
  // temporary variables
  double energy;
  double magnetization;
  double Szi;
  double Szj;
  double SziSzj;
  double Sxi;
  double SxiSxj;

  // array for each loop
  double *E;
  double *M;
  double *SziArr;
  double *SzjArr;
  double *SziSzjArr;
  double *SxiArr;
  double *SxiSxjArr;

  // averaged value for observables
  double avgE;
  double avgM;
  double avgSzi;
  double avgSzj;
  double avgSziSzj;
  double avgSxi;
  double avgSxiSxj;

  void (*adjust)();
  void (*average)();
  void (*freeMemory)();
} Observables;

#endif
