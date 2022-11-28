/* alarm (n) */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void myAlarm(int n) {
    if (fork()==0) {
        int PID;
        PID=getppid();
        if (fork()==0) {
            sleep(n);
            kill(PID,SIGALRM);
            exit(0);
        }
        exit(0);
    }
    wait(0);
    return;
}

int main() {
    myAlarm(10);
    return 0;
}