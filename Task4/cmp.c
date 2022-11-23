#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    struct stat s2, s1;

    lstat(argv[1], &s1);
    lstat(argv[2], &s2);

    if (S_ISDIR(s1.st_mode))
    {
        printf("%s is a directory", argv[1]);
        return 0;
    }
    if (S_ISDIR(s2.st_mode))
    {
        printf("%s is a directory", argv[2]);
        return 0;
    }

    if (s2.st_dev != s1.st_dev || s2.st_ino != s1.st_ino)
    {
        int f1 = open(argv[1], O_RDONLY);
        int f2 = open(argv[2], O_RDONLY);
        char c1, c2, n1, n2;
        long long difB = 1, difL = 1;

        while ((n1 = read(f1, &c1, 1)) && (n2 = read(f2, &c2, 1)))
        {
            if (c1 != c2)
            {
                printf("%s differs from %s: line %lld char %lld\n", argv[1], argv[2], difL, difB);
                return 0;
            }
            if (c1 == '\n')
                ++difL;

            ++difB;
        }
        
        difB--;

        if (n1 == 0)
        {
            if (!(n2 = read(f2, &c2, 1)))
                return 0;
            printf("EOF in %s after byte %lld, line %lld\n", argv[1], difB, difL);
        }
        if (n2 == 0)
        {
            printf("EOF in %s after byte %lld, line %lld\n", argv[2], difB, difL);
        }
    }

    return 0;
}