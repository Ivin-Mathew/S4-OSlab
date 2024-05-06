#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//Ivin Mathew 14-03-2024 Fucntioning of execv()
int main() {
    char *args[] = {"./prog2", "10", NULL};
    printf("Inside program 1 pid=%d\n\n", getpid());
    execv(args[0], args);
    perror("execv");
    return 1;
}
