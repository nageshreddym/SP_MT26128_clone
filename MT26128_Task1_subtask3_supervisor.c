#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t job1, job2;

    printf("Supervisor Started\n");
    printf("Supervisor PID: %d\n", getpid());

    job1 = fork();

    if (job1 == 0) {
        printf("Job1 started (PID=%d)\n", getpid());
        execlp("sleep", "sleep", "20", NULL);
        perror("execlp");
        exit(1);
    }

    job2 = fork();

    if (job2 == 0) {
        printf("Job2 started (PID=%d)\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    /* NO wait() or waitpid() */

    printf("\nSupervisor is NOT collecting child status.\n");
    printf("Sleeping for 60 seconds...\n");

    sleep(60);

    printf("Supervisor exiting.\n");

    return 0;
}