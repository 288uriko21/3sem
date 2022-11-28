/* sleep (n) */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void mySleep(int n) {
    static int handler=0;
    void (*previous)(int);  // указтаель на предыдущий  обработчик
    if (handler) {
        handler=0;
        return;
    }
    handler=1;
    fprintf(stderr,"Slipping\n");
    previous=signal(SIGALRM, mySleep);
    alarm(n);
    pause();
    signal(SIGALRM, previous);
}

int main() {
    mySleep(1);
    mySleep(2);
    return 0;
}
