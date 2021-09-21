#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int N = 8;  // maximum number of items in buffer
// I do not really use buffers in this program, I just emulate them using
// `count` variable. Each operation on variable `count` represents the access to
// the buffer from each thread
int count = 0;  // number of items in the buffer

// variables (emulating boolean) to wake up other thread
int consumer_should_sleep = 1;
int producer_should_sleep = 1;

// function executed in the consumer thread
void *consumer() {
  while (1) {
    if (count == 0) {
      // wait for values in the buffer from producer
      consumer_should_sleep = 1;
      while (consumer_should_sleep) {
      }
    } else {
      count--;
      // send wakeup message
      if (count == N - 1) {
        producer_should_sleep = 0;
      }
      // simple print just to understand when this program will fail
      printf("%d", count);
    }
  }
}

// function executed in the producer thread
void *producer() {
  while (1) {
    if (count == N) {
      // wait until consumer will take all values
      producer_should_sleep = 1;
      while (producer_should_sleep) {
      }
    } else {
      count++;
      // send wakeup message
      if (count == 1) {
        consumer_should_sleep = 0;
      }
      // simple print just to understand when this program will fail
      printf("%d", count);
    }
  }
}

/*
  In this example we have a race condition which may lead to deadlock
  Example:
    1. Consumer gets that `count` is zero and falls to sleep
    2. Just before it slept producer was resumed and consumer interrupted
    3. Produces makes one more item and updates `count`, and tries to wake up
      the consumer because the `count` was 0 before.
    4. As consumer was not yet sleeping, wakeup signal was lost and two
      processes will sleep forever just after producer will fill the buffer

  Explanations were somehow changed, but the idea was surely taken from slides
  and wikipedia: https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
*/
int main() {
  pthread_t consumer_thread_ptr;
  pthread_t producer_thread_ptr;

  pthread_create(&consumer_thread_ptr, NULL, consumer, NULL);
  pthread_create(&producer_thread_ptr, NULL, producer, NULL);

  pthread_join(&consumer_thread_ptr, 0);
  pthread_join(&producer_thread_ptr, 0);
}