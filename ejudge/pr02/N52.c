#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

long long last = 0;
// char buf[1000];

/*int MyCount(long long n)
{
    long long i = 10;
    int sims = 1;
    while (n > i)
    {
        i *= 10;
        ++sims;
    }
    return sims;
}*/

void simple(int s)
{
    static int countInt = 0;
    countInt += 1;
    if (countInt == 4)
        exit(0);
    /* int colsims = MyCount(last);
     sprintf(buf, "%lld\n", last);
     write(1, (void *)buf, colsims + 1);*/
    printf("%lld\n", last);
    fflush(stdout);
    /*if (countInt != 3)
    {
        sprintf(buf, "%lld\n", last);
        write(1, (void *)buf, colsims + 1);
    }
    else
    {
        sprintf(buf, "%lld", last);
        write(1, (void *)buf, colsims);
    }*/
}

void term(int s)
{
    exit(0);
}

int main(int argc, char **argv)
{
    long long low, high;
    scanf("%lld%lld", &low, &high);
    if (low <= 1)
        low = 2;
    int pid = getpid();
    /* int colsims = MyCount(pid);
     sprintf(buf, "%d\n", pid);
     write(1, (void *)buf, colsims + 1);*/

    printf("%d\n", pid);
    fflush(stdout);

    ssignal(SIGINT, &simple);
    signal(SIGTERM, &term);

    int prime;
    if (low == 2)
    {
        last = 2;
        low = 3;
    }
    long long n, root, c = 0;
    if (low % 2 == 0)
        c = 1;

    for (n = low + c; n < high; n += 2)
    {
        prime = 1;
        root = (long long)(sqrt((double)n))+1;
        for (long long i = 3; i <= root; i += 2)
            if (n % i == 0)
            {
                prime = 0;
                break;
            }
        if (prime)
        {
            last = n;
            // printf("%lld\n", last);
        }
    }

    // write(1, "-1\n", 2);
    printf("-1\n");
    fflush(stdout);
    exit(0);
    return 0;
}
