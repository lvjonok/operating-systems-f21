#include <stdio.h>

void bubble_sort(int *array, int length) {
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (array[i] > array[j]) {
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
      }
    }
  }
}

int main() {
  int arr[] = {1, 2, 3, 7, 5, -5};

  bubble_sort(arr, sizeof(arr) / sizeof(int));

  for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}