#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
    {
        if (fork() == 0)
        {
            if (i != N)
                printf("%d ", i);
            else
                printf("%d\n", i);
            return 0;
        }
        wait(NULL);
    }
    return 0;
}