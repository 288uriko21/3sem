// p21 && p22

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv)
{
    int ch_pid;
    int proc_status;
    if (ch_pid = fork() == 0)
    {
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    wait(&proc_status);
    if (WIFEXITED(proc_status) && WEXITSTATUS(proc_status) == 0)
        if (ch_pid = fork() == 0)
        {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
    wait(NULL);
}