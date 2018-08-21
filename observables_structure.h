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

  // array for each loop
  double *E;
  double *M;
  double *SziArr;
  double *SzjArr;
  double *SziSzjArr;
  double *SxiArr;
  double *SxjArr;
  double *SxiSxjArr;

  // averaged value for observables
  double avgE;
  double avgM;
  double avgSzi;
  double avgSzj;
  double avgSziSzj;
  double avgSxi;
  double avgSxiSxj;

  // New ones
  double Z1X2;
  double X1Z2;

  double *Z1X2Arr;
  double *X1Z2Arr;

  double avgZ1X2;
  double avgX1Z2;


  void (*adjust)();
  void (*average)();
  void (*freeMemory)();
} Observables;

#endif
