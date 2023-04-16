#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHILDREN 10000
#define CHILD_SLEEP_TIME 30

int main() {
    pid_t pid;
    int child_count = 0;
    while (1) {
        pid = fork();
        if (pid < 0) {
            printf("Unable to create child process\n");
            break;
        } else if (pid == 0) {
            printf("Child %d created\n", getpid());
            sleep(1);
            printf("Child %d's parent is %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
        } else {
            child_count++;
            if (child_count == MAX_CHILDREN) {
                break;
            }
            usleep(200000);
        }
    }

    int status;
    pid_t child_pid;
    while ((child_pid = wait(&status)) > 0) {}

    return 0;
}

