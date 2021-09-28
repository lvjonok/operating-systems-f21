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

void round_robin(process** processes, int n, int quantum) {
  // queue might be longer than 10 processes...
  int* queue = malloc(sizeof(int) * 1000);
  int queue_len = 0;

  sort_processes(processes, &first_arrived_comparator, n);
  // print_processes(processes, n);

  int left_time[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  int completed_processes = 0;

  for (int i = 0; i < n; i++) {
    left_time[i] = processes[i]->burst_time;
  }

  int time = processes[0]->arrival_time;
  while (completed_processes < n) {
    // add all new processes which came while we were processing
    for (int i = 0; i < n; i++) {
      if (processes[i]->arrival_time <= time && left_time[i] != 0) {
        int exists = 0;
        for (int q = 0; q < queue_len; q++) {
          if (queue[q] == i) exists = 1;
        }

        if (!exists) queue[queue_len++] = i;
      }
    }

    // check that the queue is empty and we need to skip the time
    if (queue_len == 0) {
      time++;
      continue;
    }

    // printf("\n\nstart processing\n===================\n");

    int temp_len = queue_len;
    for (int i = 0; i < temp_len; i++) {
      // printf("starting with time %d\n", time);
      // pick the first element from the queue
      int process_idx = queue[0];
      // printf("processing %d\n", process_idx);
      queue_len--;

      // shift elements to the left
      for (int q = 0; q < queue_len; q++) {
        queue[q] = queue[q + 1];
      }

      // process time left is longer than the quantum
      if (quantum < left_time[process_idx]) {
        time += quantum;
        left_time[process_idx] -= quantum;
        // have to add it back to the queue
        // printf("add %d +%d to the queue\n", process_idx, quantum);

        // in russian this thing is called костыль
        // I had to add it because we might have some processes already coming
        // into the queue while we processed `process_idx`, and they should be
        // earlier in the queue add all new processes which came while we were
        // processing
        for (int i = 0; i < n; i++) {
          if (processes[i]->arrival_time <= time && left_time[i] != 0 &&
              i != process_idx) {
            int exists = 0;
            for (int q = 0; q < queue_len; q++) {
              if (queue[q] == i) exists = 1;
            }

            if (!exists) queue[queue_len++] = i;
          }
        }

        queue[queue_len++] = process_idx;
      } else {
        time += left_time[process_idx];

        // update metrics

        processes[process_idx]->completion_time = time;
        processes[process_idx]->turnaround_time =
            processes[process_idx]->completion_time -
            processes[process_idx]->arrival_time;

        processes[process_idx]->waiting_time =
            processes[process_idx]->turnaround_time -
            processes[process_idx]->burst_time;

        completed_processes++;
        // printf("completed %d +%d %d \n", process_idx, left_time[process_idx],
        //        time);

        left_time[process_idx] = 0;
      }
    }
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
  int quantum = 2;
  int maxn = 10;
  // for case when we need to input manually
  // fscanf(stdin, "%d", &n);

  process** array = malloc(sizeof(process*) * maxn);
  int n = parse_data_csv(array);
  // uncomment the next line to input from the terminal
  // parse_data(array, n);
  round_robin(array, n, quantum);
  printf("Average Turnaround Time = %f\n",
         get_average_turnaround_time(array, n));
  printf("Average Waiting time = %f\n", get_average_waiting_time(array, n));
}