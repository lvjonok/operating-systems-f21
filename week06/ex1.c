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

void fcfs(process** processes, int n) {
  sort_processes(processes, &first_arrived_comparator, n);

  int time = 0;

  for (int idx = 0; idx < n; idx++) {
    process* cur_proc = processes[idx];

    // update time depending on current and cur_proc->arrival_time
    time = time > cur_proc->arrival_time ? time : cur_proc->arrival_time;

    // calculate completion time of cur_proc
    cur_proc->completion_time = time + cur_proc->burst_time;

    // update time as time of completion of current process
    time = cur_proc->completion_time;

    // turnaround time is the total amount of time spent by the process from
    // coming in the ready state for the first time to its completion
    cur_proc->turnaround_time =
        cur_proc->completion_time - cur_proc->arrival_time;

    // waiting time is the total time spent by the process in the ready state
    // waiting for the CPU
    cur_proc->waiting_time = cur_proc->turnaround_time - cur_proc->burst_time;
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
  fcfs(array, n);
  printf("Average Turnaround Time = %f\n",
         get_average_turnaround_time(array, n));
  printf("Average Waiting time = %f\n", get_average_waiting_time(array, n));
}