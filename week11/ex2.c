#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


int main() {
	DIR* root_dir = opendir("/");
	struct dirent* dp;
	while ((dp = readdir(root_dir)) != NULL) {
		printf("-> %s\n", dp->d_name);
	}
}
