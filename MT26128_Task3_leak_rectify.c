#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 5;

    // 1. Dynamic memory allocation
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // 2. Access valid indices (0 to 4)
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
    }

    // 3. Print the last valid element (arr[4])
    printf("Last element: %d\n", arr[size - 1]);

    // 4. Free allocated memory to prevent memory leaks
    free(arr);
    arr = NULL;

    return 0;
}