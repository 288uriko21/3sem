#include <stdio.h>
int main(void)
{
    long long S = 0;
    char c;
    while ((!feof(stdin)))
    {
        c = getchar();
        if (c >= '0' && c <= '9')
            S += c - '0';
        if (c >= 'A' && c <= 'F')
            S += c - 'A' + 10;
        if (c >= 'a' && c <= 'f')
            S += c - 'a' + 10;
    }
    printf("%lld\n", S);
    return 0;
}