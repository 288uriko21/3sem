// ( cmd1 < file1 && cmd2 ) | cmd3 >> file2
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{

    int pipefd[2];
    int pids[2];
    pipe(pipefd);

    if ((pids[0] = fork()) == 0) // subshell
    {
        int status;
        int child_pid;
        close(pipefd[0]);

        dup2(pipefd[1], 1);
        close(pipefd[1]);

        if ((child_pid = fork()) == 0)
        {
            int fd = open(argv[4], O_RDONLY);
           /* if (fd < 0)
                _exit(1);*/
            dup2(fd, 0);
            close(fd);
            execlp(argv[1], argv[1], (char *)0);
            exit(1);
        }
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status) && (WEXITSTATUS(status) == 0))
        {
            if ((child_pid = fork()) == 0)
            {
                execlp(argv[2], argv[2], (char *)0);
                exit(1);
            }
           /* waitpid(child_pid, &status, 0);
            if (WIFEXITED(status) && (WEXITSTATUS(status) == 0))
                exit(0);
            exit(1);*/
        }
        wait(NULL);
        exit(0);
    }

    int stats;
    close(pipefd[1]);
    if ((pids[1] = fork()) == 0)
    {
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        int fd = open(argv[5], O_APPEND | O_CREAT | O_WRONLY);
        /*if (fd < 0)
            _exit(1);*/
        dup2(fd, 1);
        close(fd);
        execlp(argv[3], argv[3], (char *)0);
        exit(1);
    }
    close(pipefd[0]);
    wait(NULL);
    wait(NULL);
    //waitpid(pids[1], &stats, 0);
   /* if (!(WIFEXITED(stats) && (WEXITSTATUS(stats) == 0)))
        _exit(1);*/
    /*for (int i = 0; i < 2; ++i)
    {
        waitpid(pids[i], &stats, 0);
        if (!(WIFEXITED(stats) && (WEXITSTATUS(stats) == 0)))
            _exit(1);
    }*/
    exit(0);
    return 0;
}