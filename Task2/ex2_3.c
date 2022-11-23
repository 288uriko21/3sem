#include <stdio.h>

int main(void)
{
    double x, b2i, b1i, a, c1, c2, b2, b1;
    int n, i = 0;
    scanf("%d", &n);
    scanf("%lf", &x);
    scanf("%lf", &b1i);
    ++n;
    b1 = b1i;
    b1i /= n;
    c2 = b1;
    while (scanf("%lf", &a) != -1)
    {
        c1 = c2;
        b2 = b1 * x + a;
        b1 = b2;

        c2 = c1 * x + b2;

        ++i;
        b2i = b1i * x + (a / (n - i));
        b1i = b2i;
    }

    b2i = b1i * x;

    printf("\n%.10g \n", b2);
    printf("%.10g \n", c1);
    printf("%.10g \n", b2i);
    return 0;
} 