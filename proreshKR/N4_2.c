#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int s;
struct sembuf sops;

#define up(s)        \
    sops.sem_op = 1; \
    semop(s, &sops, 1);
#define down(s)       \
    sops.sem_op = -1; \
    semop(s, &sops, 1);

int main(void)
{
    char *my_name;
    my_name = (char *)malloc(PATH_MAX);
    my_name = realpath("./N4.c", my_name);

    key_t key = ftok(my_name, 's');
    s = semget(key, 1, 0666);
    while (1)
    {
        down(s);
        printf("%d\n", getpid());
        fflush(stdout);
        printf("p2");
        fflush(stdout);
        up(s);
    }
    return 0;
}