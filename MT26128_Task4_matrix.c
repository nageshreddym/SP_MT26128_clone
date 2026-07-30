#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 500

int A[SIZE][SIZE];
int B[SIZE][SIZE];
int C[SIZE][SIZE];

typedef struct
{
    int start_row;
    int end_row;
} ThreadData;

void *multiply(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    for (int i = data->start_row; i < data->end_row; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <threads>\n", argv[0]);
        return 1;
    }

    int thread_count = atoi(argv[1]);

    if (thread_count != 1 && thread_count != 2 &&
        thread_count != 4 && thread_count != 8)
    {
        printf("Thread count must be 1, 2, 4 or 8\n");
        return 1;
    }

    pthread_t threads[8];
    ThreadData data[8];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    int rows_per_thread = SIZE / thread_count;

    for (int i = 0; i < thread_count; i++)
    {
        data[i].start_row = i * rows_per_thread;

        if (i == thread_count - 1)
            data[i].end_row = SIZE;
        else
            data[i].end_row = (i + 1) * rows_per_thread;

        pthread_create(&threads[i], NULL, multiply, &data[i]);
    }

    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix Multiplication Completed using %d thread(s).\n", thread_count);

    return 0;
}
