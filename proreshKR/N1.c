// pr1 > f2 && {pr3|pr4}
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int child_pid, status;
    if ((child_pid = fork()) == 0)
    {
        int fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY);
        if (fd < 0)
            exit(1);
        dup2(fd, 1);
        close(fd);
        execlp(argv[1], argv[1], (char *)0);
        exit(1);
    }
    waitpid(child_pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
    {
        int pipefd[2];
        pipe(pipefd);
        if (fork() == 0)
        {
            close(pipefd[0]);
            dup2(pipefd[1], 1);
            close(pipefd[1]);
            execlp(argv[3], argv[3], (char *)0);
            exit(1);
        }
        if (fork() == 0)
        {
            close(pipefd[1]);
            dup2(pipefd[0], 0);
            close(pipefd[0]);
            execlp(argv[4], argv[4], (char *)0);
            exit(1);
        }
        close(pipefd[1]);
        close(pipefd[0]);
        wait(NULL);
        wait(NULL);
        exit(0);
    }
    else
        exit(1);
}
