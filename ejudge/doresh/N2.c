/*
Напишите функцию

void exchange(char *str);
Функция принимает Си-строку str. Строка содержит последовательность
 чисел в десятичной записи без ведущих нулей, разделенных символом +.

Функция должна модифицировать строку str, поменяв в ней местами
первое и последнее число.

Например, если при вызове функции строка str равна 10+23+456,
то в результате её выполнения строка str должна стать равной 456+23+10.

Числа содержат хотя бы одну цифру, но строка может быть пустой,
содержать одно, два или более чисел.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exchange(char *str)
{
    int ind = 1;

    while (str[ind] != '+' && str[ind] != '\0')
        ++ind;

    if (str[ind] == '\0')
        return;

    int ind2 = ind, len = 1, lench = 0;
    ++ind;
    while (str[ind] != '\0')
    {
        if (str[ind] >= '0' && str[ind] <= '9')
            ++lench;
        else
            lench = 0;
        ++len;
        ++ind;
    }
    len -= lench;

    char *str2 = (char *)malloc((len + lench + ind2 + 1) * (sizeof(char)));
    int indstr2 = 0;

    ind = ind2 + len;
    while (str[ind] != '\0')
    {
        str2[indstr2] = str[ind];
        ++indstr2;
        ++ind;
    }

    ind = 0;
    int ind22 = ind2;
    for (; ind < len; ++ind)
    {
        str2[indstr2] = str[ind22];
        ++indstr2;
        ++ind22;
    }

    ind = 0;
    for (; ind < ind2; ++ind)
    {
        str2[indstr2] = str[ind];
        ++indstr2;
    }

    for (int i = 0; i < len + lench + ind2; ++i)
        str[i] = str2[i];
    str[len + lench + ind2] = '\0';

    free(str2);
}

/*int main(void)
{
    char m[] = "1880+2";
    exchange(m);
    printf("%s", m);
    return 0;
}*/