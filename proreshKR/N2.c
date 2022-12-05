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

int child_pids[4];
int semid;
int msgid;

void sig(int s)
{
    kill(child_pids[0], SIGKILL);
    kill(child_pids[1], SIGKILL);
    kill(child_pids[2], SIGKILL);
    kill(child_pids[3], SIGKILL);
    msgctl(msgid, IPC_RMID, NULL);
    _exit(0);
}

int main(int argc, char **argv)
{
    char *dad_name;
    dad_name = (char *)malloc(PATH_MAX);
    dad_name = realpath("./N2.c", dad_name);
    

    key_t key = ftok(dad_name, 's');

    msgid = msgget(key, 0666 | IPC_CREAT);

    signal(SIGINT, &sig);
    if ((child_pids[0] = fork()) == 0){
        execlp("./N2_2", "./N2_2", dad_name, "1", (char*) 0);
        printf("ExecFail");
    }
    sleep(2);

    if ((child_pids[1] = fork()) == 0)
        execlp("./N2_2", "./N2_2", dad_name, "2", (char*) 0);

    if ((child_pids[2] = fork()) == 0)
        execlp("./N2_2", "./N2_2", dad_name, "3", (char*) 0);

    if ((child_pids[3] = fork()) == 0)
        execlp("./N2_2", "./N2_2", dad_name, "4", (char*) 0);


    while(1);
    return 0;
}
