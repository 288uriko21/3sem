#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <limits.h>
#include <stdlib.h>

int s;
struct sembuf sops;

int main()
{
    key_t key;

    char *my_name;
    my_name = (char *)malloc(PATH_MAX);
    my_name = realpath("./N4.c", my_name);
    printf("%d", getpid());

    key = ftok(my_name, 's');
    s = semget(key, 1, 0666 | IPC_CREAT);
    semctl(s, 0, SETVAL, (int)1);
    sops.sem_num = 0;
    sops.sem_flg = 0;

    while(1);

}




