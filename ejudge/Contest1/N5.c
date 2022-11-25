#include <stdio.h>
#include <stdlib.h>

int EndOfFiles(int n, int *Eind)
{
    for (int i = 0; i < n; ++i)
        if (*(Eind + i))
            return 1;
    return 0;
};

int main(int argc, char **argv)
{
    FILE **fls;
    long long *numbers, M;
    int *Eind, I, e = 0, flag;
    fls = (FILE **)malloc((argc - 1) * (sizeof(FILE *)));
    numbers = (long long *)malloc((argc - 1) * (sizeof(long long)));
    Eind = (int *)malloc((argc - 1) * (sizeof(int)));

    for (int i = 0; i < argc - 1; ++i)
    {
        fls[i] = fopen(argv[i + 1], "r");
        *(Eind + i) = 1;
        if (!feof(fls[i]))
            e = fscanf(fls[i], "%lld", numbers + i);
        if (e == EOF)
            *(Eind + i) = 0;
    };

   while (EndOfFiles(argc - 1, Eind))
    {
        flag = 1;

        for (int i = 0; i < argc - 1; ++i)
        {
            if (flag && *(Eind + i))
            {
                M = *(numbers + i);
                I = i;
                flag = 0;
            };
            if (*(Eind + i) && (*(numbers + i) < M))
            {
                M = *(numbers + i);
                I = i;
            };
        };
        printf("%lld ", M);
        e = fscanf(fls[I], "%lld", numbers + I);
        if (e == EOF)
            *(Eind + I) = 0;
    }; 
    for (int i = 0; i < argc - 1; ++i)
        fclose(fls[i]);

    free(fls);
    free(numbers);
    free(Eind);
    printf("\n");
    return 0;
}