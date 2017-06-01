// EUC_2D data structure
typedef struct euc_2d {
  
  int city;
  float x, y;
  struct euc_2d *next;
  struct euc_2d *prev;

}EUC_2D;

// Queue data structure for EUC_2D type;
typedef struct queue_2d{
	
	EUC_2D *start;
	EUC_2D *end;

}Queue_2D;

// create and return a pointer type Queue_2D
Queue_2D * create_queue () {
  return (Queue_2D *)malloc(sizeof(Queue_2D));
}

// Insert end queue function
void insert_2D_queue(Queue_2D *q, int city, float x, float y){

	EUC_2D *newBlock;
	newBlock = (EUC_2D *)malloc(sizeof(EUC_2D));
  newBlock->city = city;
  newBlock->x = x;
  newBlock->y = y;
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
void impress_2d_queue(Queue_2D *q){

	EUC_2D *aux = q->start;

	while(aux != NULL){
		printf("city[%d]->[%f, %f] \n",aux->city, aux->x, aux->y);
		aux = aux->next;
	}

}

/*
  alloc_2D 
  Receive a pointer to file already open and put the he on 
  right position(after NODE_COORD_SECTION) to read the data of filestream 
*/
void alloc_2D (FILE *tsblib_file) {
  char str[128], city[2], x[55], y[55]; //strings that fscanf will copy the info of filestram 
  /*
    do while => because FILE *tsblib_file recived can be right in the next line, so
   in this case we find first NODE_COORD_SECTION and break the loop
  */
  do {  
    if(!strcmp(str, "NODE_COORD_SECTION")) { // compare
      printf("Start to Alloc 2D Queue ... [%s] \n\n", str);
      break; // exit loop;
    }
  } while (fscanf(tsblib_file, "%s", str) != EOF);

  Queue_2D *q = create_queue(); // create new queue

  /*
    read and create a queue with filestream data;
  */
  while (fscanf(tsblib_file, "%s %s %s", city, x, y) != EOF) 
    insert_2D_queue (q, atoi(city), atof(x), atof(y)); // atof beacuse some data info are real numbers
  
  impress_2d_queue(q); // impress queue; 
  printf("2D Queue Allocated -> Finding better path through Cities ... \n\n");

}