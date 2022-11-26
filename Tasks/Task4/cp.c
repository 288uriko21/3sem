#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define N 1024
#define MAX_PATHNAME_LEN 1024
int main(int argc, char **argv)
{
    char buf[N];
    int fd1, fd2, n;
    struct stat s, s1;

    lstat(argv[1], &s);
    lstat(argv[2], &s1);

    if (s1.st_dev != s.st_dev || s1.st_ino != s.st_ino)
    {

        if ((fd1 = open(argv[1], O_RDONLY)) == -1)
        {
            printf("Can't open file\n");
            return -1;
        }
        if (S_ISREG(s.st_mode))
        {
            if (S_ISREG(s1.st_mode))
                fd2 = creat(argv[2], s.st_mode);
            else
            {
                char pathFile[MAX_PATHNAME_LEN];
                sprintf(pathFile, "%s/%s", argv[2], argv[1]);
                fd2 = creat(pathFile, s.st_mode);
            }
            if (fd2 == -1)
            {
                printf("Can't create file\n");
                return -1;
            }
            while ((n = read(fd1, buf, N)) > 0)
                write(fd2, buf, n);
        }
        else
        {
            printf("%s is a directory\n", argv[1]);
        }
    }
    else
    {
        printf("cp: '%s' and ", argv[1]);
        printf("'%s' is the same file\n", argv[2]);
    }
    return 0;
}