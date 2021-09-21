#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *on_thread_created(int thread_idx) {
  printf("Hello from bad coffee shop number: %d!\n", thread_idx);
}

const int N = 10;  // defines the number of threads created

main() {
  // just a container for pointer to threads
  pthread_t *thread_id_container = malloc(sizeof(pthread_t) * N);

  // just sequently create new thread and do not care about anything else
  for (int i = 0; i < N; i++) {
    printf("Someone opened coffee shop number: %d\n", i);
    pthread_create(&thread_id_container[i], NULL, on_thread_created, i);
  }

  // just sequently close threads one by one
  // actually, that explains why the first thread was closed earlier than we got
  // message from the last.
  // It happens because we just created the last thread and as it is
  // non-blocking to our main function later, there were enough time to join the
  // first thread
  for (int i = 0; i < N; i++) {
    pthread_join(thread_id_container[i], 0);
    printf("Giancarlo closed bad coffee shop with idx: %d\n", i);
  }
}