typedef struct euc_2d {
  
  int city;
  float x, y;
  struct euc_2d *next;
  struct euc_2d *prev;

}EUC_2D;

typedef struct queue_2d{
	
	EUC_2D *start;
	EUC_2D *end;

}Queue_2D;

Queue_2D * create_queue () {
  return (Queue_2D *)malloc(sizeof(Queue_2D));
}

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

void impress_2d_queue(Queue_2D *q){

	EUC_2D *aux = q->start;

	while(aux != NULL){
		printf("city[%d]->[%f, %f] \n",aux->city, aux->x, aux->y);
		aux = aux->next;
	}

}

void aloc_2D (FILE *tsblib_file) {
  char str[128];
  char city[2], x[55], y[55];

  do {
    if(!strcmp(str, "NODE_COORD_SECTION")) {
      printf("Start to Aloc 2D Queue ... [%s] \n\n", str);
      break;
    }
  } while (fscanf(tsblib_file, "%s", str) != EOF);

  Queue_2D *q = create_queue ();

  while (fscanf(tsblib_file, "%s %s %s", city, x, y) != EOF) 
    insert_2D_queue (q, atoi(city), atof(x), atof(y));
  
  impress_2d_queue(q);
  printf("2D Queue Alocated -> Find path through Cities ... \n\n");

}