#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("Parent program\n");

    pid_t id = fork();

    if (id == 0) {
        printf("Inside child\n");
        printf("Current process=%d\n", getpid());
        printf("Parent process=%d\n", getppid());
    } else if (id > 0) {
        printf("Inside parent and waiting for child to complete\n");
        wait(NULL);
        printf("Inside parent after child completion\n");
        printf("Current process=%d\n", getpid());
        printf("Parent process=%d\n", getppid());
    } else {
        perror("fork");
        return 1;
    }

    printf("Last line\n");

    return 0;
}
