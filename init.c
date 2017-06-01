#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "2D_interface.c"


int main (int argc, char *argv[]) {
  
  // pointer to file
  FILE *open_file = fopen(argv[1], argv[2]);
  char str[128];
  
  //error handle with open file
  if (open_file == NULL) {
    fprintf(stderr, "Can't open input file [%s]\n",argv[1]);
    exit(1);
  }

  printf("Read file: [%s] \n", argv[1]);

  while (fscanf(open_file, "%s", str) != EOF) {
    if(!strcmp(str, "EUC_2D")) {

      aloc_2D(open_file);
      
    } else if (!strcmp(str, "EUC_3D")) {
      break;
    } 
  }

  fclose(open_file);
  
  return 0;
}