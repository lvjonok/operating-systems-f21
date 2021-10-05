#include <stdio.h>
#include <stdlib.h>
int main() {
  int n;
  fscanf(stdin, "%d", &n);

  // allocate memory after we got the n
  int *array = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    array[i] = i;
  }

  for (int i = 0; i < n; i++) {
    printf("%d\n", array[i]);
  }

  // deallocate the memory
  free(array);
}