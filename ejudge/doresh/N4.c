#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    /* int a[10] = {45671, 432, -4, 34, 4, 6, 0, 54, 55, 39};
     int b[12]; */
    int f = open(argv[1], O_RDWR);
    /*write(f, a, 10 * sizeof(int));
    lseek(f, 0, SEEK_SET);
    read(f, a, 10 * sizeof(int));
    for (int i = 0; i <= 9; ++i)
        printf("%d ", *(a + i));
    printf("\n"); */
    // fflush;
    // close(f);
    // f = open(argv[1], O_RDWR);
    lseek(f, 0, SEEK_SET);

    int c, r;
    long offs = 0, ofsz = 0;
    r = read(f, &c, sizeof(int));
    if (r == 0)
        exit(0);
    int m = c;
    while (r != 0)
    {
        if (c >= m)
        {
            m = c;
            ofsz = offs;
        };
        offs += sizeof(int);
        // printf("!%d!", c);
        r = read(f, &c, sizeof(int));
    };

    offs = 0;
    lseek(f, 0, SEEK_SET);
    r = read(f, &c, sizeof(int));
    while (offs != ofsz + sizeof(int))
    {
        lseek(f, offs, SEEK_SET);
        write(f, &c, sizeof(int));
        r = read(f, &c, sizeof(int));
        offs += sizeof(int);
    };
    lseek(f, offs, SEEK_SET);
    write(f, &m, sizeof(int));
    offs += sizeof(int);

    /*if (r != 0)
    {
        lseek(f, offs, SEEK_SET);
        int c2;
        int r2 = read(f, &c2, sizeof(int));
        if (r2 != 0)
        {
        }
    }*/
    int c2;
    while (r != 0)
    {
        lseek(f, offs, SEEK_SET);
        read(f, &c2, sizeof(int));
        lseek(f, offs, SEEK_SET);
        write(f, &c, sizeof(int));
        r = read(f, &c, sizeof(int));
        if (r == 0)
        {
            write(f, &c2, sizeof(int));
        }
        offs += sizeof(int);
        c = c2;
    }

    // lseek(f, 0, SEEK_SET);
    // write(f, &m, sizeof(int));

    /* lseek(f, 0, SEEK_SET);
     read(f, b, 12 * sizeof(int));
     for (int i = 0; i <= 11; ++i)
         printf("%d ", *(b + i));*/
    close(f);
    return 0;
}