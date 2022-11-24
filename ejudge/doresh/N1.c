#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print(int a, int b, int c)
{
    long long res = ((long long)c) * ((long long)b);
    if (res == (long long)a)
    {
        printf("%d %d\n", b, c);
        exit(0);
    }
}

int main(void)
{
    int a, b, c, d;

    scanf("%d %d %d %d", &a, &b, &c, &d);
    print(a, b, c);
    print(a, b, d);
    print(a, c, d);

    return 0;
}
