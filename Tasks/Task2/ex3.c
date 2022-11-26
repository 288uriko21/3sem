#include <stdio.h>

long fibIt(int n) // iterative function
{
    int c, i = 2;
    long chp = 1/*previous fibonacci number*/, ch = 1;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    while (i != n)
    {
        c = ch;
        ch += chp;
        chp = c;
        ++i;
    }
    return ch;
};

long fibRec(int n) // recursive function
{
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return 1;
    return fibRec(n - 1) + fibRec(n - 2);
};

int main(void)
{
    int n;
    while (scanf("%d", &n) != -1)
    {
        printf("%ld\n", fibIt(n));
        printf("%ld\n", fibRec(n));
    };
    return 0;
} /*whith calculating large Fibonacci numbers,
 the recursive function works noticeably slower*/