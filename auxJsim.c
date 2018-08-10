#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "extern_defs_var.h"

int main (int argc) {
	char *call = malloc(BUFF_SIZE * sizeof(*call));
	char *folderName = malloc(BUFF_SIZE * sizeof(*folderName));
	folderName = "FinalObservables";

  // git configurations
  system("git config --global credential.helper cache");
  system("git config --global credential.helper 'cache --timeout=36000000000000000000000000'");

  for (unsigned int j = 1; j < MAX_N - 2; j++) {
    printf("=====================================================\n");
		printf("Finite Size Scalling for j = %u\n", j);
		printf("Calculating...\n");

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

	system("poweroff");
  return 0;
}
