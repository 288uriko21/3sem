// { cmd1 || cmd2 } && cmd3
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int status, child_pid;
    if ((child_pid = fork()) == 0)
    {
        execlp(argv[1], argv[1], (char *)0);
        exit(1);
    }
    else
    {
        waitpid(child_pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        {
            if ((child_pid = fork()) == 0)
            {
                execlp(argv[2], argv[2], (char *)0);
                exit(1);
            }
            waitpid(child_pid, &status, 0);
        }

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            if ((child_pid = fork()) == 0)
            {
                execlp(argv[3], argv[3], (char *)0);
                exit(1);
            }
            waitpid(child_pid, &status, 0);
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            exit(0);
        else
            exit(1);
    }
    return 0;
}