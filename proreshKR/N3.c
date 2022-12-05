#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char buf[5];
    int ping[2],
        pong[2];
    pipe(ping);
    pipe(pong);

    int fd = open("f1", O_RDONLY);
    printf("%d\n", fd);
    int chld_pid;
    if ((chld_pid = fork()) == 0)
    {
        int fd1 = open("f1", O_RDONLY);
        int f1 = open("f3", O_WRONLY | O_CREAT);
        char block[5];
        for (;;)
        {
            sleep(1);
            read(ping[0], buf, 5);
            //printf("%s\n", buf);
            if (read(fd, (void *)block, 5) <= 0)
                exit(0);
            write(f1, (void *)block, sizeof(block));
            write(pong[1], "Pong", 5);
        }
    }
    int f = open("f2", O_WRONLY | O_CREAT);
    char block[5];
    
    while (1)
    {
        sleep(1);
        if (read(fd, (void *)block, 5) <= 0)
        {
            kill(chld_pid, SIGKILL);
            exit(0);
        }
        write(f, (void *)block, 5);
        write(ping[1], "Ping", 5);
        read(pong[0], buf, 5);
        //printf("%s\n", buf);
    }
}

