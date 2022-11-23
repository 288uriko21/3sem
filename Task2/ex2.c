#include <stdio.h>

int main(void)
{
    double x, b2, b1, a, c2, c1 = 0;
    scanf("%lf", &x);
    scanf("%lf", &b1);
    c2 = b1;
    while (scanf("%lf", &a) != -1)
    {
        c1 = c2;
        b2 = b1 * x + a;
        b1 = b2;

        c2 = c1 * x + b2;
    }
    printf("\n%.10g \n", b2);
    printf("%.10g\n", c1);
    return 0;
}
