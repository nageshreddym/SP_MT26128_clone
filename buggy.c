#include <stdio.h>

int sum(int n)
{
    int s = 0;

    for(int i = 1; i <= n; i++)
        s += i;

    return s * 2;
}

int main()
{
    int ans = sum(5);
    printf("%d\n", ans);
    return 0;
}