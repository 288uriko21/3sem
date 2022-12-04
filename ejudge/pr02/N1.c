#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
       return -1;
    unsigned short int startFadrTab = (unsigned short int)strtol(argv[2], NULL, 16);
    unsigned short int virtadr;
    unsigned short int Vpage_num;
    unsigned short int sdvig_po_str;
    unsigned short int Fpage_num;
    unsigned short int outp_num;

    /*printf("%d", virtadr);
    printf("%d", startFadrTab);*/
    //scanf("%x", &virtadr);
   // printf("%d", virtadr);
    while (scanf("%hx", &virtadr) == 1)
    {
        Vpage_num = virtadr / 512;
        sdvig_po_str = virtadr % 512;

        lseek(fd, startFadrTab + Vpage_num * 2, SEEK_SET);
        read(fd, (void *)(&Fpage_num), sizeof(unsigned short int));
        Fpage_num += sdvig_po_str;

        lseek(fd, Fpage_num, SEEK_SET);
        read(fd, (void *)(&outp_num), sizeof(unsigned short int));
        printf("%hu\n", outp_num);
    }
    close(fd);
    return 0;
}