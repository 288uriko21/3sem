#include <stdio.h>

int main(void)
{
    int a, b, n;
    scanf("%d%d%d", &a, &b, &n);
    
    printf("%*c", n, ' ');
    for (int i = a; i < b; ++i)
        printf("%*d", n+1, i);

    printf("\n");

    for (int i = a; i < b; ++i)
    {
        printf("%*d", n, i);

        for (int j = a; j < b; ++j)
            printf("%*lld", n+1, (long long)i*j);

        printf("\n");
    }
    return 0;
}