
/**
* Header file that defines points, data sets, and their constructors and
* destructors
*/
#include <stdlib.h>
#include "sds-master/sds.c"

typedef struct Point {
  double x;
  double y;
} Point;

typedef struct Data {
  Point** set;
  unsigned int size;
} Data;

Point* point_new(double x, double y);
Data* data_new(void);
void data_push(Data* data, double x, double y);
void data_pop(Data* data);
void data_free(Data* data);
Data* data_read(char* text);

Point* point_new(double x, double y) {
  Point* point = (Point*) calloc(1, sizeof(Point));
  point->x = x;
  point->y = y;
  return point;
}

Data* data_new(void) {
  // constructor for Data, returns a stack of size 1
  Data* data = (Data*) calloc(1, sizeof(Data));
  data->size = 0;
  return data;
}

void data_push(Data* data, double x, double y) {
  if (data->size == 0) {
    data->set = (Point**) calloc(1, sizeof(Point*));
    data->size += 1;
    data->set[0] = point_new(x,y);
  }
  else {
    data->set = (Point**) realloc(data->set, data->size + 1);
    data->size += 1;
    data->set[data->size-1] = point_new(x,y);
  }
}

void data_pop(Data* data) {
  if (data->size > 1) {
    free(data->set[data->size-1]);
    data->set[data->size-1] = NULL;
    data->size -= 1;
  }
  else { // free header of data. This means freeing the struct itself
    free(data);
    data = NULL;
  }
}

void data_free(Data* data) {
  // destructor for the Data stack
  while (data->size > 1) {
    data_pop(data);
  }
}
