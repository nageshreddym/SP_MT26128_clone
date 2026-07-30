#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t job1, job2;
    int status;

    printf("=====================================\n");
    printf(" Job Supervisor Started\n");
    printf(" Supervisor PID : %d\n", getpid());
    printf("=====================================\n");

    /* Launch Job 1 */
    job1 = fork();

    if (job1 < 0) {
        perror("Fork failed for Job 1");
        exit(EXIT_FAILURE);
    }

    if (job1 == 0) {
        printf("Job 1 started (PID = %d)\n", getpid());
        execlp("sleep", "sleep", "20", NULL);
        perror("Failed to execute Job 1");
        exit(EXIT_FAILURE);
    }

    /* Launch Job 2 */
    job2 = fork();

    if (job2 < 0) {
        perror("Fork failed for Job 2");
        exit(EXIT_FAILURE);
    }

    if (job2 == 0) {
        printf("Job 2 started (PID = %d)\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("Failed to execute Job 2");
        exit(EXIT_FAILURE);
    }

    /* Wait for Job 1 */
    waitpid(job1, &status, 0);
    printf("Job 1 (PID=%d) completed.\n", job1);

    /* Wait for Job 2 */
    waitpid(job2, &status, 0);
    printf("Job 2 (PID=%d) completed.\n", job2);

    printf("\n========== Execution Summary ==========\n");
    printf("Supervisor PID : %d\n", getpid());
    printf("Job 1 PID      : %d\n", job1);
    printf("Job 2 PID      : %d\n", job2);
    printf("Both jobs executed successfully.\n");
    printf("=======================================\n");

    return 0;
}