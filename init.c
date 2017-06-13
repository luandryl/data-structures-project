#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 2d_interface
#include "2D_interface.c"
#include "3D_interface.c"


int main (int argc, char *argv[]) {
  
  Queue_2D *data = NULL;

  // pointer to file
  FILE *open_file = fopen(argv[1], "r");
  char str[128];

  //error handle with open file
  if (open_file == NULL) {
    fprintf(stderr, "Can't open input file [%s]\n",argv[1]);
    exit(1);
  }

  printf("Read file: [%s] \n", argv[1]);

  // Walking through file header to discover what interface to be called
  while (fscanf(open_file, "%s", str) != EOF) {

    if(!strcmp(str, "EUC_2D")) { 
      data = alloc_2D(open_file);
      break; // pass the file pointer to 2D_interface
    } else if (!strcmp(str, "EUC_3D")) {
      alloc_3D(open_file);
    } 
  }

  fclose(open_file); // close file
  if (data != NULL) {
    printf("Queue Allocated ... Starting to solve %d ", data->size);
    
    cost_matrix_2d(data);

  }


  return 0;
}