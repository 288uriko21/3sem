#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <limits.h>

int main(int argc, char **argv)
{
    int fd = open(argv[2], O_CREAT | O_RDWR | O_TRUNC);
    dup2(fd, 1);
    //char buf[PATH_MAX];
    //sprintf(buf, "/bin/%s");
    execlp(argv[1], argv[1], (char *)0);
    printf("Faild execl call\n");
    return 0;
}