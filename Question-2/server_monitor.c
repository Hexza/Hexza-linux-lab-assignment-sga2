#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child process (PID: %d) started. Simulating unresponsive server...\n", getpid());
        sleep(30);
        printf("Child finished (this line should not print if killed).\n");
        exit(0);
    } else {
        printf("Parent process (PID: %d) monitoring child (PID: %d)...\n", getpid(), pid);
        sleep(5);

        int status;
        pid_t result = waitpid(pid, &status, WNOHANG);

        if (result == 0) {
            printf("Child is unresponsive after 5 seconds. Killing child PID %d...\n", pid);
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
            printf("Child process terminated and reaped. No zombie left.\n");
        } else {
            printf("Child exited normally.\n");
        }
    }

    return 0;
}

