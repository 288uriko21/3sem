#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

// pr1 | pr2 > f.res

int main(int argc, char **argv)
{
    int p[2];
    pipe(p);

    if (fork() == 0)
    {
        dup2(p[1], 1);
        close(p[1]);
        close(p[0]);
        execlp(argv[1], argv[1], (char *)0);
        exit(1);
    }
    else
    {
        close(p[1]);
        if (fork() == 0)
        {
            int fd = creat(argv[3], 0777); // c правами доступа
            dup2(fd, 1);
            close(fd);
            dup2(p[0], 0);
            close(p[0]);
            execlp(argv[2], argv[2], (char *)0);
            exit(1);
        }
        else
        {
            close(p[0]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}

// date cat  файл, который не жалко
