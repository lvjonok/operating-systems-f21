#include <stdio.h>
#include <string.h>

void *realloc(void *ptr, size_t size) {
  // just to be sure, that the new realloc is being called
  printf("executing new realloc\n");

  // case: ptr is NULL
  if (!ptr) {
    return malloc(size);
  }

  // case: size is zero, ptr is not NULL
  if (!size) {
    free(ptr);

    // return a new minimum sized object
    return NULL;
  }

  // allocate new space
  void *new_ptr;
  new_ptr = malloc(size);

  memcpy(new_ptr, ptr, size);
  free(ptr);
  return new_ptr;
}

int main() {
  int *ar = malloc(5 * sizeof(int));
  for (int i = 0; i < 5; i++) {
    ar[i] = i;
    printf("%d\n", ar[i]);
  }

  ar = (int *)realloc(ar, 2);

  for (int i = 0; i < 2; i++) {
    ar[i] = i;
    printf("%d\n", ar[i]);
  }
}