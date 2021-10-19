#include <stdio.h>
#include <stdlib.h>

#define INCREMENT_STIPA(stipa) (((stipa) >> 1) | 0b10000000)
#define DECREMENT_STIPA(stipa) (((stipa) >> 1) | 0b00000000)

#define MAKE_LESS_STIPA(stipa) ((stipa) >> 1)
#define MAKE_STIPA_GREAT_AGAIN(stipa) (stipa | 0b1000000000000000)

typedef unsigned short age;

int* parse_input(int* input_len) {
  FILE* input_file = fopen("input.txt", "r");

  // contains amount of values we can put inside input_array
  int buffer_size = 1;

  int* input_array = (int*)malloc(sizeof(int));
  // actual amount of elements
  int input_array_len = 0;

  int current_number;
  while (fscanf(input_file, "%d ", &current_number) != -1) {
    input_array[input_array_len++] = current_number;

    if (input_array_len == buffer_size) {
      buffer_size *= 2;
      input_array = realloc(input_array, buffer_size * sizeof(int));
    }
  }

  input_array = realloc(input_array, input_array_len * sizeof(int));
  *input_len = input_array_len;
  return input_array;
}

char* format_char(age val) {
  char* out = (char*)malloc(sizeof(char) * 8);
  int idx = 0;
  while (val) {
    out[idx++] = val % 2 ? '1' : '0';
    val /= 2;
  }
  out[idx] = '\0';
  char* combined = (char*)malloc(idx * sizeof(char));
  for (int i = 0; i < idx; i++) {
    combined[i] = out[idx - i - 1];
  }
  return combined;
}

// function checks whether we have our page and returns its idx, -1 otherwise
int contains(int* memory, int memory_len, int page) {
  for (int i = 0; i < memory_len; i++) {
    if (memory[i] == page) return i;
  }

  return -1;
}

int get_oldest(age* ages, int memory_len) {
  int pensiya = 0xff;
  int idx = -1;
  for (int i = 0; i < memory_len; i++) {
    // printf("CHECK %d %d\n", pensiya, ages[i]);
    if (idx == -1 || pensiya > ages[i]) {
      pensiya = ages[i];
      idx = i;
    }
  }
  // printf("I FOUND THE OLDEST %d\n", idx);
  return idx;
}

int add(int* memory, age* ages, int memory_len, int new_page) {
  int place = contains(memory, memory_len, new_page);

  for (int i = 0; i < memory_len; i++) {
    ages[i] = MAKE_LESS_STIPA(ages[i]);
  }

  // we already have this page in the list
  // printf("%d was %d\n", new_page, place);
  if (place != -1) {
    ages[place] = MAKE_STIPA_GREAT_AGAIN(ages[place]);
    return 1;
  } else {
    // we have to remove the oldest page or add to the empty place

    // try to find the empty slot for the page
    int added = 0;
    for (int i = 0; i < memory_len; i++) {
      if (memory[i] == 0) {
        memory[i] = new_page;
        ages[i] = MAKE_STIPA_GREAT_AGAIN(0);
        added = 1;
        break;
      }
    }

    if (added == 1) {
      return 0;
    }

    // we have to remove the oldest page
    int to_remove = get_oldest(ages, memory_len);
    memory[to_remove] = new_page;
    ages[to_remove] = MAKE_STIPA_GREAT_AGAIN(0);

    return 0;
  }
}

void debug_memory(int* memory, age* ages, int memory_len) {
  printf("\nSTATE\n");
  for (int i = 0; i < memory_len; i++) {
    printf("Page %d - %d\t%d\n", i, memory[i], ages[i]);
  }
}

int main() {
  // printf("%s\n", format_char(6));
  int page_frames = 10;
  fscanf(stdin, "%d", &page_frames);

  int* queue = calloc(page_frames, sizeof(int));
  age* chasiki_tikayt = calloc(page_frames, sizeof(age));

  int input_len = 0;
  int* input = parse_input(&input_len);

  int hits = 0;

  debug_memory(queue, chasiki_tikayt, page_frames);
  for (int i = 0; i < input_len; i++) {
    hits += add(queue, chasiki_tikayt, page_frames, input[i]);
    debug_memory(queue, chasiki_tikayt, page_frames);

    // int res = add(queue, page_frames, &queue_len, input[i]);
    // print_queue(queue, queue_len);
  }

  printf("hits: %d\tmisses: %d\tratio: %f\n", hits, input_len - hits,
         (float)(hits) / (float)(input_len - hits));

  // int* pages_references = parse_input();
}