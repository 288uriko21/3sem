#include "N4.c"

int main(void){
    semctl(s, 0, IPC_RMID, (int) 0);
    return 0;
}