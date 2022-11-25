#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s1
{
    char f1;
    long long f2;
    char f3;
};

struct s2
{
    char f1;
    char f3;
    long long f2;
};

size_t compactify(void *ptr, size_t size)
{
    if (size == 0)
        return 0;

    int N = size / sizeof(struct s1);
    int razm = sizeof(struct s1);
    struct s2 elem;
    struct s2 * m2 = (struct s2 *)(malloc(N * sizeof(struct s2)));
    for (int i = 0; i < N; ++i)
    {
        elem.f1 = ((struct s1 *)(ptr + i*razm))->f1;
        elem.f2 = ((struct s1 *)(ptr + i*razm))->f2;
        elem.f3 = ((struct s1 *)(ptr + i*razm))->f3;
        m2[i] = elem;
    }
    razm = sizeof(struct s2);
    for (int i = 0; i < N; ++i)
    {
        memcpy(ptr+i*razm, (void*)(m2+i), razm);
    }
    free(m2);
    return N * sizeof(struct s2);
}

/*int main()
{
    struct s1 mas[4];
    mas[0].f2 = 0;
    mas[1].f2 = 1;
    mas[2].f2 = 2;
    mas[3].f2 = 3;
    printf("%ld\n", compactify((void*)mas, 4*sizeof(struct s1)));
    printf("%lld %lld %lld ", ((struct s2*)mas)[0].f2, ((struct s2*)mas)[1].f2, ((struct s2*)mas)[2].f2);

    printf("%ld %ld %ld", sizeof(struct s1), sizeof(struct s2), sizeof(void));
}*/