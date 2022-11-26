#include <stdio.h>

double str2double(char str[])
{
    double N = 0, n;
    int i = 0, st, sign = 1;
    if (str[i] == '-')
    {
        ++i;
        sign = -1;
    }
    else if (str[i] == '+')
        ++i;
    for (; (str[i] != '.') && (str[i] != '\0') && (str[i] != 'E') && (str[i] != 'e'); ++i);
    --i;
    st = i;
    for (; i >= 0 && str[i] != '-' && str[i] != '+'; --i)
    {
        n = (str[i] - '0');
        for (int j = st; j > i; j--)
            n *= 10;
        N += n;
    }; /*form a number without a fractional part up to e*/

    i = st + 1;
    if (str[i] == '.')
    {
        ++i;
        int k = 1;
        while (str[i] >= '0' && str[i] <= '9')
        {
            n = str[i] - '0';
            for (int j = 0; j != k; ++j)
                n /= 10;
            N += n;
            ++k;
            ++i;
        }
    }; /*forming the fractional part*/

    if ((str[i] == 'e') || (str[i] == 'E'))
    {
        ++i;
        if (str[i] == '-')
        {
            n = str2double(str + i + 1);
            for (int j = 0; j < n; ++j)
                N /= 10;
        }
        else
        {
            if (str[i] == '+')
                i++;
            n = str2double(str + i);
            for (int j = 0; j < n; ++j)
                N *= 10;
        }
    };

    N *= sign;
    return N;
};

int main(void)
{
    char str[100];

    while (scanf("%s", str) != -1)
    {
        printf("%.10g\n", str2double(str));
    };

    return 0;
}