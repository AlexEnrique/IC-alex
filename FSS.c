#include <stdio.h>
#include <stdlib.h>

// #define TEMPERATURE 7.000
// #define N_MIN 4
// #define N_MAX 70
#define BUFF_SIZE 100

/* *argv[] é utilizado para passar os argumentos de Temperatura, *
 * 'j' e 'n máximo' via linha de comando, nessa ordem            */
int main(int argc, char const *argv[]) {
  double T = atof(*(argv + 1));
  int j = atoi(*(argv + 2));
  int nMax = atoi(*(argv + 3));

  char *buff = malloc(BUFF_SIZE * sizeof(*buff));
  char *output = malloc(BUFF_SIZE * sizeof(*output));
  char *filename = malloc(BUFF_SIZE * sizeof(*filename));
  FILE *fRead = fopen("aux.tmp", "w");

  system("if [ ! -d \"FSS/done\" ]; then mkdir FSS/done; fi");

  // file name of fWrite
  if (j < 10)
    snprintf(filename, BUFF_SIZE, "FSS/done/FSS.T=%.3lf_j=0%d", T, j);
  else
    snprintf(filename, BUFF_SIZE, "FSS/done/FSS.T=%.3lf_j=%d", T, j);
  FILE *fWrite = fopen(filename, "w");

  if (j >= nMax) {
    printf("ERRO: valor de 'j' maior do que o máximo para 'n'\n");
    snprintf(output, BUFF_SIZE, "rm %s", filename);
    system(output);
    return 0;
  }

  for (int n = j+1; n < nMax + 1; n++) {
    snprintf(filename, BUFF_SIZE, "FSS/T=%.3lff/j=%df/n=%d.sim", T, j, nMax);
    snprintf(output, BUFF_SIZE, "if [ ! -f \"%s\" ]; then echo \"!! Dados para T = %.3lf, j = %d e n = %d inexistente !!\"; fi", filename, T, j, n);
    system(output);
    fRead = freopen(filename, "r", fRead);

    for (int i = 0; i < 4; i++) {
      fgets(buff, BUFF_SIZE, fRead);
    }

    snprintf(output, BUFF_SIZE, "%.4lf %s", (double)1/n, buff);
    fprintf(fWrite, output);
  }

  fclose(fWrite);
  fclose(fRead);
  system("rm aux.tmp");
  printf("Done!\n");

  return 0;
}
