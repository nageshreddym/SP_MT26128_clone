#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *arr = malloc(5 * sizeof(int));
    for(int i = 0; i <= 5; i++)
        arr[i] = i * 10;
    printf("%d\n", arr[5]);
    return 0;
}