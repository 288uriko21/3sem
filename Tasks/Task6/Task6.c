#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define NMAX 256
char *shmaddr;
struct sembuf sops;
int semid, shmid; //дескр. семафора и дескр. разделяемой памяти

void put_apple(int s)
{
    int col = rand()%15+1;
    sops.sem_op = -1;
    semop(semid, &sops, 1);

    printf("Mum puts %d apples\n", col);
    memcpy((void *)shmaddr, (void *)(&col), sizeof(int));

    sops.sem_op = 1;
    semop(semid, &sops, 1);
}

void end()
{
    exit(0);
}

int main(int argc, char **argv)
{
    key_t key;
    int numchild = atoi(argv[1]);
    char *mum_name;
    mum_name = (char *)malloc(PATH_MAX);
    mum_name = realpath("./Task6.c", mum_name);
    key = ftok(mum_name, 'S');
    // printf("%s", mum_name);
    semid = semget(key, 1, 0666 | IPC_CREAT);
    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    shmaddr = shmat(shmid, NULL, 0);
    semctl(semid, 0, SETVAL, (int)1);
    sops.sem_num = 0;
    sops.sem_flg = 0;
    int col = rand()%15+1;
    char numch[2] = "0";

    printf("Mum puts %d apples\n", col);
    memcpy((void *)shmaddr, (void *)(&col), sizeof(int));
    signal(SIGALRM, put_apple);
    signal(SIGCHLD, end);

    for (int i = 0; i < numchild; ++i)
    {
        if (fork() == 0)
        {
            numch[0] += (i+1);
            //printf("%s\n", numch);
            execlp("./child", "./child", mum_name, numch, argv[2], (char *)0);
            printf("Faild exec\n");
            exit(1);
        }
    }
    while (1)
        ;

    wait(NULL);
    wait(NULL);

    return 0;
}