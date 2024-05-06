#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
//ivin Mathew 14-03-2024
//System calls for directories
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    char *dname = argv[1];
    DIR *dr = opendir(dname);
    if (dr == NULL) {
        perror("Error opening directory");
        return 1;
    }
    struct dirent *de;

    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }
    closedir(dr);
    return 0;
}

