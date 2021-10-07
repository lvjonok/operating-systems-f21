#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  for (int s = 0; s < 10; s++) {
    // I saw the difference in si so fields only starting from 1000 MB

    // change of so and si fields indicate swap process

    // so si fields are changing when we do not have enough memory and need to
    // swap with the hard drive
    char *arr = (char *)malloc(10 * 1024 * 1024);
    memset(arr, 0, 10 * 1024 * 1024);

    sleep(1);
  }
}