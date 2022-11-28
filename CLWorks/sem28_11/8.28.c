/* Руденко 8.28 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char buf[BUFSIZ+1];
    int pipes[2];
    int PID;
    int fd;
    char *fgetsRet=(char *)1;
    FILE *fp;
    
    if (argc!=3) {
        fprintf(stderr,
            "ERROR! There must be 2 arguments: SOURCE_FILE DESTINATION_FILE\n");
        return -1;
    }
    
    pipe(pipes);
    
    if ((PID=fork())==-1) {
        fprintf(stderr, "ERROR! FORK failed\n");
        return -1;
    }
    else
        if (PID>0) {
            close (pipes[1]);
            if ((fd=open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666))==-1) {
                fprintf(stderr, "ERROR! %s opening failed\n",argv[2]);
                close (pipes[0]);
                return -1;
            }
            dup2 (pipes[0],0);
            close (pipes[0]);
            dup2 (fd,1);
            close (fd);
            if (execlp("sort","sort",NULL)==-1) {
                fprintf(stderr, "ERROR! SORT EXEC failed\n");
                return -1;
            }
        }
    
    close (pipes[0]);

    if ((fp=fopen(argv[1], "r"))==NULL) {
        fprintf(stderr, "ERROR! %s opening failed\n",argv[1]);
        close (pipes[1]);
        return -1;
    }
    
    while (fgetsRet) {
        buf[0]='\0';
        while (fgetsRet && !strchr(buf,'\n'))
            fgetsRet=fgets(buf,BUFSIZ+1,fp);
        buf[0]='\0';
        while (fgetsRet && !strchr(buf,'\n')) {
            fgetsRet=fgets(buf,BUFSIZ+1,fp);
            write(pipes[1], buf, (strchr(buf,'\0')-buf)*sizeof(char));
        }
    }
    
    close (pipes[1]);
    return 0;
}
