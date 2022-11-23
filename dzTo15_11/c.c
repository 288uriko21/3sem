// cmd < f

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd = open(argv[2], O_RDONLY);
    dup2(fd, 0);
    execlp(argv[1], argv[1], (char *)0);
    printf("Faild execl call\n");
    return 0;
}