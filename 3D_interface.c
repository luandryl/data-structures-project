// EUC_3D data structure
typedef struct euc_3d {
  
  int city;
  float x, y, z;
  struct euc_3d *next;
  struct euc_3d *prev;

}EUC_3D;

// Queue data structure for EUC_3D type;
typedef struct queue_3D{
	
	EUC_3D *start;
	EUC_3D *end;

}Queue_3D;

// create and return a pointer type Queue_3D
Queue_3D * create_queue3D () {
  return (Queue_3D *)malloc(sizeof(Queue_3D));
}

// Insert end queue function
void insert_3D_queue(Queue_3D *q, int city, float x, float y, float z){

	EUC_3D *newBlock;
	newBlock = (EUC_3D *)malloc(sizeof(EUC_3D));
  newBlock->city = city;
  newBlock->x = x;
  newBlock->y = y;
  newBlock->z = z;
	newBlock->next = NULL;
	
	if(q->start != NULL) {
		q->end->next = newBlock;
		newBlock->prev = q->end;
		q->end = newBlock;
	}
	else {
		q->start = newBlock;
		q->end = newBlock;		
	}
}

// impress queue
void impress_3D_queue(Queue_3D *q){

	EUC_3D *iterator = q->start;

	while(iterator != NULL){
		printf("city[%d]->[%f, %f, %f] \n",iterator->city, iterator->x, iterator->y, iterator->z);
		iterator = iterator->next;
	}

}

/*
  alloc_3D 
  Receive a pointer to file already open and put he on 
  right position(after NODE_COORD_SECTION) to read the data of filestream 
*/
void alloc_3D (FILE *tsblib_file) {
  char str[128], city[2], x[55], y[55], z[55]; //strings that fscanf will copy the data of filestram 
  /*
    do while => because FILE *tsblib_file recived can be right in the next line, so
    In this case we find first NODE COORD_SECTION and we break the loop without iteration
  */
  do {  
    if(!strcmp(str, "NODE_COORD_SECTION")) { // compare
      printf("Start to Alloc 3D Queue ... [%s] \n\n", str);
      break; // exit loop;
    }
  } while (fscanf(tsblib_file, "%s", str) != EOF);

  Queue_3D *q = create_queue3D(); // create new queue

  /*
    read and create a queue with filestream data;
  */
  while (fscanf(tsblib_file, "%s %s %s", city, x, y) != EOF) 
    insert_3D_queue (q, atoi(city), atof(x), atof(y), atof(z)); // atof beacuse some data info are real numbers
  
  impress_3D_queue(q); // impress queue; 
  printf("3D Queue Allocated -> Finding better path through Cities ... \n\n");

}