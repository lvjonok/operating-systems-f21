#include <stdio.h>
#include <stdlib.h>

#define FILENAME ("input_ok.txt")

struct row {
  int len;
  int* values;
};

int sum(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

struct row* rows_op(struct row* row1, struct row* row2,
                    int (*operation)(int, int)) {
  struct row* new_row = malloc(sizeof(struct row));
  new_row->len = row1->len;
  new_row->values = malloc(sizeof(int) * row1->len);

  for (int i = 0; i < new_row->len; i++) {
    new_row->values[i] = operation(row1->values[i], row2->values[i]);
  }

  return new_row;
}

struct matrix {
  int h;
  struct row** rows;  // we use represent matrix directly as consequtive rows
};

void print_row(struct row* r) {
  for (int i = 0; i < r->len; i++) {
    printf("%d ", r->values[i]);
  }
  printf("\n");
}

void print_matrix(struct matrix* m) {
  for (int i = 0; i < m->h; i++) print_row(m->rows[i]);
}

struct row* parse_row(char* buffer) {
  struct row* new_row = malloc(sizeof(struct row));
  new_row->len = 0;
  new_row->values = malloc(sizeof(int) * 1);

  while (1) {
    char* end;
    int number = strtol(buffer, &end, 10);
    if (buffer == end) break;
    new_row->values[new_row->len] = number;
    buffer = end;
    new_row->len++;
    if (new_row->len > sizeof(new_row->values) / sizeof(int)) {
      new_row->values = realloc(new_row->values, new_row->len * 2);
    }
  }

  return new_row;
}

struct matrix* create_matrix() {
  struct matrix* my_matrix = malloc(sizeof(struct matrix));
  my_matrix->h = 0;
  my_matrix->rows = (struct row**)malloc(sizeof(struct row*));
  return my_matrix;
}

void add_row(struct matrix* old_matrix, struct row* new_row) {
  old_matrix->rows = realloc(old_matrix->rows, old_matrix->h + 100);
  old_matrix->rows[old_matrix->h] = new_row;
  old_matrix->h++;
}

struct matrix* parse_input() {
  FILE* file = fopen(FILENAME, "r");
  int lines_amount = 0;
  char buffer[256];

  struct matrix* raw_data = create_matrix();

  while (!feof(file)) {
    fscanf(file, "%4095[^\n]\n", buffer);
    lines_amount++;
    struct row* my_row = parse_row(buffer);
    add_row(raw_data, my_row);
  }
  fclose(file);

  return raw_data;
}

// function returns 1 if row1 is element-wise less of equal than row2
int compare_rows(struct row* row1, struct row* row2) {
  for (int i = 0; i < row1->len; i++) {
    if (row1->values[i] > row2->values[i]) return 0;
  }
  return 1;
}

int main() {
  struct matrix* raw_matrix = parse_input();

  struct row* existing_resources = raw_matrix->rows[0];
  struct row* allocated_resources = raw_matrix->rows[1];

  // copy from the raw matrix
  struct matrix* current_allocation = create_matrix();
  struct matrix* request_matrix = create_matrix();
  for (int i = 2; i < raw_matrix->h; i++) {
    add_row(i < raw_matrix->h / 2 + 1 ? current_allocation : request_matrix,
            raw_matrix->rows[i]);
  }

  int N = current_allocation->h;
  int* terminated = calloc(0, sizeof(int) * N);
  int terminated_amount = 0;

  // actual implementation of banker's algorithm
  while (terminated_amount != N) {
    int found_one_process_to_complete = 0;
    for (int i = 0; i < N; i++) {
      if (!terminated[i] &&
          compare_rows(request_matrix->rows[i], allocated_resources)) {
        terminated[i] = 1;
        terminated_amount++;
        allocated_resources =
            rows_op(allocated_resources, current_allocation->rows[i], sum);
        found_one_process_to_complete = 1;
        break;
      }
    }

    if (!found_one_process_to_complete) {
      printf("Deadlock occured\n");
      for (int i = 0; i < N; i++) {
        if (!terminated[i]) {
          printf("Process causing this is %d\n", i);
          printf(
              "Cute little puppy doing cute things: "
              "https://www.youtube.com/watch?v=j5a0jTc9S10\n");
          return 0;
        }
      }
    }
  }
  printf("No deadlocks\n");
  printf(
      "Cute little puppy doing cute things: "
      "https://www.youtube.com/watch?v=j5a0jTc9S10\n");
}