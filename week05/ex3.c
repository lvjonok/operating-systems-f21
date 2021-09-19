#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int N = 8;      // maximum number of items in buffer
int count = 0;  // number of items in the buffer

// variables (emulating boolean) to wake up other thread
int consumer_should_sleep = 1;
int producer_should_sleep = 1;

// function executed in the consumer thread
void *consumer() {
  while (1) {
    if (count == 0) {
      consumer_should_sleep = 1;
      while (consumer_should_sleep) {
      }
    } else {
      count--;
      if (count == 0) {
        producer_should_sleep = 0;
      }
      printf("%d", count);
    }
  }
}

// function executed in the producer thread
void *producer() {
  while (1) {
    if (count == N) {
      producer_should_sleep = 1;
      while (producer_should_sleep) {
      }
    } else {
      count++;
      if (count == 1) {
        consumer_should_sleep = 0;
      }
      printf("%d", count);
    }
  }
}

int main() {
  pthread_t consumer_thread_ptr;
  pthread_t producer_thread_ptr;

  pthread_create(&consumer_thread_ptr, NULL, consumer, NULL);
  pthread_create(&producer_thread_ptr, NULL, producer, NULL);

  pthread_join(&consumer_thread_ptr, 0);
  pthread_join(&producer_thread_ptr, 0);
}