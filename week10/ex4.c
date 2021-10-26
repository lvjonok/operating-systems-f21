#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  int files_counter = 0;
  char** files_names = malloc(sizeof(char) * 256);
  int* inum_holder = malloc(sizeof(int) * 256);

  DIR* dir_pointer = opendir("tmp");
  struct dirent* dp;
  struct stat* st;
  while ((dp = readdir(dir_pointer)) != NULL) {
    // printf("%s\n", dp->d_name);
    stat(dp->d_name, st);
    // printf("%d\n", dp->d_ino);
    files_names[files_counter] = dp->d_name;
    inum_holder[files_counter] = dp->d_ino;
    files_counter++;
  }

  for (int i = 0; i < files_counter; i++) {
    int occurences = 0;
    for (int j = 0; j < files_counter; j++) {
      if (inum_holder[i] == inum_holder[j]) occurences++;
    }
    if (occurences >= 2) {
      printf("%s: ", files_names[i]);
      for (int j = 0; j < files_counter; j++) {
        if (inum_holder[i] == inum_holder[j] &&
            files_names[i] != files_names[j])
          printf("%s ", files_names[j]);
      }
      printf("\n");
    }
  }
}
