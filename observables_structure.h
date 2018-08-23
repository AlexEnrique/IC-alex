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
  double Sxj;
  double SxiSxj;
  double Bell;

  // array for each loop
  double *E;
  double *M;
  double *SziArr;
  double *SzjArr;
  double *SziSzjArr;
  double *SxiArr;
  double *SxjArr;
  double *SxiSxjArr;
  double *Z1X2Arr;
  double *X1Z2Arr;

  // averaged value for observables
  double avgE;
  double avgM;
  double avgSzi;
  double avgSzj;
  double avgSziSzj;
  double avgSxi;
  double avgSxj;
  double avgSxiSxj;
  double avgZ1X2;
  double avgX1Z2;

  void (*adjust)();
  void (*average)();
  void (*freeMemory)();
} Observables;

#endif
