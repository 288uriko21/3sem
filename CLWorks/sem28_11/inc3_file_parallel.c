/* В файле записано целое число в текстовом виде. Создать 2 параллельных
   процесса, один из которых увеличивает число на 1, второй - на 2. Всего число
   должно увеличиться на 3. Синхронизацию обеспечить с помощью неименованных
   каналов */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int pipes[2];
    FILE *fp;
    int n;
    
    pipe(pipes);
    if (fork()==0) {
        close(pipes[0]);
        fp=fopen(argv[1], "r+");
        fscanf(fp,"%d",&n);
        n+=2;
        fseek(fp,0,SEEK_SET);
        fprintf(fp,"%d",n);
        fclose(fp);
        close(pipes[1]);
        return 0;
    }
    close(pipes[1]);
    read(pipes[0],NULL,1);
    close(pipes[0]);
    fp=fopen(argv[1], "r+");
    fscanf(fp,"%d",&n);
    n+=1;
    fseek(fp,0,SEEK_SET);
    fprintf(fp,"%d",n);
    fclose(fp);
    close(pipes[1]);
    return 0;
}
