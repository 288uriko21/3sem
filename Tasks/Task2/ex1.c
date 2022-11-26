#include <stdio.h>

int main(void)
{
    double E, x, xi, xi_1;
    scanf("%lf", &E);

    while (scanf("%lf", &x) != -1)
    {
        if (x >= 0)
        {
            xi_1 = -1;
            xi = 1;
            while ((xi_1 == -1) || (xi - xi_1) >= E || (xi_1 - xi) >= E)
            {
                xi_1 = xi;
                xi = 0.5 * (xi_1 + (x / xi_1));
            }
            printf("\n%.10g \n", xi);
        }
    }

    return 0;
}