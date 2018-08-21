#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "extern_defs_var.h"

int main (int argc) {
	double T, dT, minT;
	dT = DELTA_T;
	T = INITIAL_TEMPERATURE + dT;
	minT = MIN_TEMPERATURE;

	char *call = malloc(BUFF_SIZE * sizeof(*call));
	char *folderName = malloc(BUFF_SIZE * sizeof(*folderName));
	folderName = "FinalObservables";

  // git configurations
  system("git config --global credential.helper cache");
  system("git config --global credential.helper 'cache --timeout=36000000000000000000000000000000000'");

  // while ((T -= dT) > minT) {
	for (int j = 1; j < ceil(MAX_N/2); j++) {
    printf("=====================================================\n");
		printf("Calculating observables for j = %u...\n", j);

    snprintf(call, BUFF_SIZE, "./main.exe %u", j);
    system(call);

		printf("Done!\n\n");
  }

  printf("=====================================================\n");
	printf("Calling github...\n");

  snprintf(call, BUFF_SIZE, "git add %s/", folderName);
  system(call);
  snprintf(call, BUFF_SIZE, "git commit -m \"added %s\"", folderName);
  system(call);
  snprintf(call, BUFF_SIZE, "git push origin master");
  system(call);

	printf("Finished! \n");
	printf("Turning of...\n");

	// system("poweroff");
  return 0;
}
