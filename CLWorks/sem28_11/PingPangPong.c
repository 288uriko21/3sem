#include<stdio.h> /* for printf */
#include<unistd.h> /* system calls fork, pipe etc. */
#include<signal.h> /* constant SIGINT */
#include<stdlib.h> /* function exit */

char * name;
//char Pang[]="Pang";
//char Ping[]="Ping";
//char Pong[]="Pong";
int ball;

void GameOver(int sig){
  printf("%s finished\n", name);
  exit(0);
}

void PlayVoley(int in, int out){
  for(;;){
     read(in,&ball,sizeof(ball));
     printf("%s: %d\n",name, ball);
     sleep(1);
     ball++;
     write(out,&ball,sizeof(ball));
  }
}

int main(){
  
/*         []
          /  \
         /    \
      Pang    Ping
                \
                 \
                 Pong
*/ 

  int ai[2]; /* Pang --> Ping */
  int io[2]; /* Ping --> Pong */
  int oa[2]; /* Pong --> Pang */

  pipe(ai); pipe(io); pipe(oa);
  signal(SIGINT, GameOver);
   
  if (fork()==0){
      
    name="Pang";
     
    close(ai[0]); close(oa[1]);
    close(io[0]); close(io[1]);
    write(ai[1],&ball,sizeof(ball)); /* start game */
     
    PlayVoley(oa[0],ai[1]);
  }
  
  if (fork()==0){
    if (fork()==0){
      
      name="Pong";
     
      close(oa[0]); close(io[1]);
      close(ai[0]); close(ai[1]);
     
      PlayVoley(io[0],oa[1]);
    }
      
    name="Ping";
     
    close(io[0]); close(ai[1]);
    close(oa[0]); close(oa[1]);
     
    PlayVoley(ai[0],io[1]);
  }

  /* father */
   
  signal(SIGINT, SIG_IGN);
  
  close(ai[0]); close(ai[1]); 
  close(io[0]); close(io[1]);
  close(io[0]); close(io[1]);

  wait(NULL); wait(NULL); wait(NULL);
  return 0;
}

