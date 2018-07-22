typedef struct array {
  // type = type of the array
  unsigned int length;
  ... = malloc(lenght * sizeof(type));
}

array allocArray(unsigned int lenght, char *type) {
  if (strcmp(type, "double")) {

  }
}

double *E = allocArray(lenght, double);
short **lattice = allocArray(n, short);
for (unsigned int i = 0; i < n; i++) {
  lattice[i] = allocArray(n, short);
}

// I want this:
// E[i] // E.i
// E.length
// Is there a way?
