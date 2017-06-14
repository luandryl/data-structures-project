#include <math.h>
#include <time.h>
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
  int size;

}Queue_2D;

// create and return a pointer type Queue_2D
Queue_2D * create_queue2D () {
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
    q->size++;
	}
	else {
    q->size = 0;
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
  Receive a pointer to file already open and put he on 
  right position(after NODE_COORD_SECTION) to read the data of filestream 
*/
Queue_2D * alloc_2D (FILE *tsblib_file) {
  char str[128], city[2], x[55], y[55]; //strings that fscanf will copy the data of filestram 
  /*
    do while => because FILE *tsblib_file recived can be right in the next line, so
    In this case we find first NODE COORD_SECTION and we break the loop without iteration
  */
  do {  
    if(!strcmp(str, "NODE_COORD_SECTION")) { // compare
      printf("Start to Alloc 2D Queue ... [%s] \n\n", str);
      break; // exit loop;
    }
  } while (fscanf(tsblib_file, "%s", str) != EOF);

  Queue_2D *queue = create_queue2D(); // create new queue

  /*
    read and create a queue with filestream data;
  */
  while (fscanf(tsblib_file, "%s %s %s", city, x, y) != EOF) 
    insert_2D_queue (queue, atoi(city), atof(x), atof(y)); // atof beacuse some data info are real numbers
  
  return queue;

}

EUC_2D * search_2d (EUC_2D *array, int city) {
  EUC_2D *iterator = array;

  while (iterator != NULL && iterator->city != city)
    iterator = iterator->next;
  
    return iterator;
}

float cost_calc_2d (EUC_2D *city1, EUC_2D *city2) {
  return sqrt(pow((city1->x - city2->x), 2) + pow((city1->y - city2->y), 2));
}

EUC_2D * find_near_2d (Queue_2D *data, int limit, char direction, EUC_2D *random_start) {
  
  EUC_2D *iterator = NULL;
  float dh = 0, d0 = 0; 
  EUC_2D *near = NULL;

  d0 = (random_start->next != NULL) ? cost_calc_2d(random_start, random_start->next): cost_calc_2d(random_start, random_start->prev);
  if (direction == 'f') {
    
    iterator = data->start;
    while (iterator != NULL && iterator->city < limit) {
      dh = cost_calc_2d(random_start, iterator);
      if (dh < d0)
        near = iterator;
      
      iterator = iterator->next;
    }

  } else {
    iterator = data->end;
    while (iterator != NULL && iterator->city > limit) {
      dh = cost_calc_2d(random_start, iterator);
      if (dh < d0)
        near = iterator;
      
      iterator = iterator->prev;
    }
  }

  return near;
}

void draw_path_2d(Queue_2D *data) {

  for (int i = 0; i < data->size; i++) {
    int r_s = (1+rand() % data->size-1);
    int up = r_s + data->size / 4;
    int down = fabsf(r_s - data->size / 4);
    
    EUC_2D *rand_start_node = search_2d(data->start, r_s);

    EUC_2D *h1 = find_near_2d(data, down, 'r', rand_start_node);

     printf("R_S:[%d] \t I [%d] \n", r_s, i);
    // printf("H1,c:[%d] \n", h1->city);
    // printf("SN,c:[%d] \n", rand_start_node->city);
    // printf("\n Sp[%d]  - \t In[%d] = [%d] \n\n\n", up, down, (up - down));
  }
  

}