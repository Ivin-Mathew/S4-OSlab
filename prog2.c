#include <stdio.h>
#include <stdlib.h>
//Ivin Mathew 14-03-2024
//Execv() redirects to this program
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    int v = atoi(argv[1]);
    printf("\nExecuting program 2\n");
    printf("Sum=%d\n\n", v);

    return 0;
}
