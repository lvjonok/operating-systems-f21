#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *on_thread_created(int thread_idx) {
  printf("Hello from bad coffee shop number: %d!\n", thread_idx);
}

const int N = 10;  // defines the number of threads created

main() {
  pthread_t *thread_id_container = malloc(sizeof(pthread_t) * N);

  for (int i = 0; i < N; i++) {
    printf("Someone opened coffee shop number: %d\n", i);
    // the magic of this task is here
    // the difference with the previous task is that we intentionally waited for
    // the end of execution by calling pthread_join
    // It stopped the execution of our main function and patiently waited for
    // each thread to end
    pthread_create(&thread_id_container[i], NULL, on_thread_created, i);
    pthread_join(thread_id_container[i], 0);
    printf("Giancarlo closed bad coffee shop with idx: %d\n", i);
  }
}