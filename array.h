typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initarray(Array *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertarray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freearray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
