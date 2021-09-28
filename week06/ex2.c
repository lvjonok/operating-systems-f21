#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int arrival_time;     // at
  int burst_time;       // bt
  int completion_time;  // ct
  int turnaround_time;  // tat
  int waiting_time;     // wt
} process;

process* parse_process() {
  process* cur_proc = malloc(sizeof(process));
  fscanf(stdin, "%d %d", &cur_proc->arrival_time, &cur_proc->burst_time);

  return cur_proc;
}

void parse_data(process** storage, int n) {
  for (int row = 0; row < n; row++) {
    storage[row] = parse_process();
  }
}

// Function parses csv file and returns the number of process we have read
int parse_data_csv(process** storage) {
  FILE* input_stream = fopen("input.csv", "r");
  // check that we for sure opened the file
  if (input_stream == NULL) exit(1);

  int process_idx = 0;
  process* cur_proc = malloc(sizeof(process));
  while (fscanf(input_stream, "%d, %d\n", &cur_proc->arrival_time,
                &cur_proc->burst_time) != EOF) {
    storage[process_idx++] = cur_proc;
    // allocate new memory piece
    cur_proc = malloc(sizeof(process));
  }
  return process_idx;
}

void print_processes(process** processes, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d\t:\t%d\t%d\n", i, processes[i]->arrival_time,
           processes[i]->burst_time);
  }
}

void swap_processes(process* process1, process* process2) {
  process temp = *process1;
  *process1 = *process2;
  *process2 = temp;
}

int first_arrived_comparator(process* process1, process* process2) {
  // the process with bigger arrival time should run later
  return process1->arrival_time > process2->arrival_time;
}

int shortest_job_next_comparator(process* process1, process* process2) {
  if (process1->arrival_time != process2->arrival_time) {
    return process1->arrival_time > process2->arrival_time;
  } else {
    return process1->burst_time > process2->burst_time;
  }
}

void sort_processes(process** processes, int (*comparator)(process*, process*),
                    int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (comparator(processes[i], processes[j])) {
        swap_processes(processes[i], processes[j]);
      }
    }
  }
}

void shortest_job_first(process** processes, int n) {
  sort_processes(processes, &shortest_job_next_comparator, n);
  print_processes(processes, n);
  // return;
  int completed[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  int time = processes[0]->arrival_time;
  for (int i = 0; i < n; i++) {
    // printf("start with time %d\n", time);
    int min_time_idx = -1;
    int min_time = -1;

    // search for the shortest job in the queue
    for (int j = 0; j < n; j++) {
      if (processes[j]->arrival_time > time) break;
      // select a process with minimum time + it must not be completed
      if ((min_time == -1 || min_time > processes[j]->burst_time) &&
          !completed[j]) {
        min_time = processes[j]->burst_time;
        min_time_idx = j;
      }
      // we have selected our process
    }

    // we had nothing in queue, so we skip some time for the first arrived
    // we can select the first arrived, because if two processes will have the
    // same arrival time, the one with the shortest job will be the first
    // according to the sorting I used
    if (min_time == -1) {
      for (int j = 0; j < n; j++) {
        if (!completed[j]) {
          min_time_idx = j;
          time = processes[j]->arrival_time;
          break;
        }
      }
    }

    // mark as completed
    completed[min_time_idx] = 1;

    // calculate completion time of processes we have selected
    processes[min_time_idx]->completion_time =
        time + processes[min_time_idx]->burst_time;

    processes[min_time_idx]->turnaround_time =
        processes[min_time_idx]->completion_time -
        processes[min_time_idx]->arrival_time;

    processes[min_time_idx]->waiting_time =
        processes[min_time_idx]->turnaround_time -
        processes[min_time_idx]->burst_time;

    time += processes[min_time_idx]->burst_time;
  }
  output_task(processes, n);
}

float get_average_turnaround_time(process** processes, int n) {
  float att = 0;
  for (int i = 0; i < n; i++) {
    att += processes[i]->turnaround_time;
  }
  return att / n;
}

float get_average_waiting_time(process** processes, int n) {
  float awt = 0;
  for (int i = 0; i < n; i++) {
    awt += processes[i]->waiting_time;
  }
  return awt / n;
}

void output_task(process** processes, int n) {
  printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 1; i <= n; i++) {
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i, processes[i - 1]->arrival_time,
           processes[i - 1]->burst_time, processes[i - 1]->completion_time,
           processes[i - 1]->turnaround_time, processes[i - 1]->waiting_time);
  }
}

int main() {
  int maxn = 10;
  // for case when we need to input manually
  // fscanf(stdin, "%d", &n);

  process** array = malloc(sizeof(process*) * maxn);
  int n = parse_data_csv(array);
  // uncomment the next line to input from the terminal
  // parse_data(array, n);
  shortest_job_first(array, n);
  printf("Average Turnaround Time = %f\n",
         get_average_turnaround_time(array, n));
  printf("Average Waiting time = %f\n", get_average_waiting_time(array, n));
}