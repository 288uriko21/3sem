#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

#define NMAX 256
#define playTime 1

int main(int argc, char **argv)
{
    key_t key;
    int semid, shmid; //дескр. семафора и дескр. разделяемой памяти
    char *shmaddr;
    struct sembuf sops;

    key = ftok(argv[1], 'S');
    // printf("%s", mum_name);
    semid = semget(key, 1, 0666 | IPC_CREAT);
    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    shmaddr = shmat(shmid, NULL, 0);
    sops.sem_num = 0;
    sops.sem_flg = 0;

    int apples;
    int time = atoi(argv[3]);
    alarm(time);

    printf("child!");

    while (1)
    {
        sops.sem_op = -1;
        semop(semid, &sops, 1);

        memcpy((void *)(&apples), (void *)shmaddr, sizeof(int));
        if (apples <= 0)
        {
            sops.sem_op = 1;
            semop(semid, &sops, 1);
            //kill(getppid(), SIGALRM);
            sleep(2);
        }
        --apples;
        printf("Child%s gets an apple; %d apples left\n", argv[2], apples);
        memcpy((void *)shmaddr, (void *)(&apples), sizeof(int));

        sops.sem_op = 1;
        semop(semid, &sops, 1);

        if (apples <= 0)
            kill(getppid(), SIGALRM);

        sleep(playTime);
    }

    return 0;
}