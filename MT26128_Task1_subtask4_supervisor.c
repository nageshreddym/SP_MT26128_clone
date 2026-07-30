#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_JOBS 2

int main() {
    pid_t jobs[NUM_JOBS];
    int status;

    printf("=========================================\n");
    printf("   JOB SUPERVISOR (PID: %d)\n", getpid());
    printf("=========================================\n\n");

    // -----------------------------------------------------------------
    // 1. Launch Job 1: ls -l
    // -----------------------------------------------------------------
    jobs[0] = fork();
    if (jobs[0] < 0) {
        perror("fork failed for Job 1");
        exit(EXIT_FAILURE);
    }

    if (jobs[0] == 0) {
        printf("[Job 1 - PID %d] Executing: ls -l\n\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed for Job 1");
        exit(EXIT_FAILURE);
    }

    // -----------------------------------------------------------------
    // 2. Launch Job 2: sleep 60
    // -----------------------------------------------------------------
    jobs[1] = fork();
    if (jobs[1] < 0) {
        perror("fork failed for Job 2");
        exit(EXIT_FAILURE);
    }

    if (jobs[1] == 0) {
        printf("[Job 2 - PID %d] Executing: sleep 60\n", getpid());
        execlp("sleep", "sleep", "60", NULL);
        perror("execlp failed for Job 2");
        exit(EXIT_FAILURE);
    }

    // Give children time to run output
    sleep(2);

    printf("\n-----------------------------------------\n");
    printf("Job 1 (ls -l) PID    : %d\n", jobs[0]);
    printf("Job 2 (sleep 60) PID : %d\n", jobs[1]);
    printf("-----------------------------------------\n");

    // -----------------------------------------------------------------
    // 3. Prompt User for Termination Method
    // -----------------------------------------------------------------
    printf("\nChoose termination method for running jobs:\n");
    printf("1. Graceful (SIGTERM)\n");
    printf("2. Forceful (SIGKILL)\n");
    printf("Enter choice (1 or 2): ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nSending SIGTERM to active jobs...\n");
        kill(jobs[1], SIGTERM); // Send graceful signal to remaining background job
    } 
    else if (choice == 2) {
        printf("\nSending SIGKILL to active jobs...\n");
        kill(jobs[1], SIGKILL); // Send forceful signal to remaining background job
    } 
    else {
        printf("Invalid choice! Skipping signal sending.\n");
    }

    // -----------------------------------------------------------------
    // 4. Reap and Inspect Both Jobs
    // -----------------------------------------------------------------
    printf("\n=========================================\n");
    printf("         SUPERVISOR SUMMARY REPORT\n");
    printf("=========================================\n");

    for (int i = 0; i < NUM_JOBS; i++) {
        pid_t wpid = waitpid(jobs[i], &status, 0);

        if (WIFEXITED(status)) {
            printf("[Job %d - PID %d] Exited naturally with code: %d\n", 
                   i + 1, wpid, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            printf("[Job %d - PID %d] Terminated by signal %d (%s)\n", 
                   i + 1, wpid, sig, (sig == SIGKILL) ? "SIGKILL" : "SIGTERM");
        }
    }

    printf("\nAll jobs accounted for. Supervisor shutting down.\n");
    return 0;
}