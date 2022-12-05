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
#include <sys/msg.h>

int main(int argc, char** argv)
{
    int child_pid;
    if ((child_pid = fork()) == 0)
    {
        //printf("%s\n", argv[1]);
        struct sembuf sops;
        int semid;
        key_t key;
        int msgid;
        int Mypid = (int)strtol(argv[2], 0, 10);

        struct
        {
            long mtype;     // message type
            char data[100]; // message
        } message;


        key = ftok(argv[1], 's');
        msgid = msgget(key, 0666);

        if (Mypid == 1)
        {
            strcpy(message.data, "0");
            message.mtype = 1;

            printf("Son %d send  0\n", Mypid);
            msgsnd(msgid, (const void *)(&message), 100, 0);

        }

        while (1)
        {
            if (Mypid < 3)
                msgrcv(msgid, (void *)(&message), 100, 2, 0);
            else
                msgrcv(msgid, (void *)(&message), 100, 1, 0);
            printf("Son %d receved %s\n", Mypid, message.data);
            long int numb = strtol(message.data, 0, 10);
            numb += 1;
            printf("Son %d send %ld\n", Mypid, numb);
            sprintf(message.data, "%ld", numb);
            if (Mypid < 3)
                message.mtype = 1;
            else
                message.mtype = 2;
            msgsnd(msgid, (const void *)(&message), 100, 0);

            sleep(2);
        }
    }

    return 0;
}