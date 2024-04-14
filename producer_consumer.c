#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int sem =1;
int no =1;
int state=0;

void  wait(int *sema){
    while(*sema <= 0);
        *sema--;
}
void signal(int * sema){
    sleep(1);
    *sema++;
}

void *producer(void * arg){
    int no =*((int *)arg);
    int st = no;
    while(1){
        wait(&sem);
          if(state==0){
            printf("producer produce  %d\n",no);
            no++;
            state = 1;
          }
        signal(&sem);
    }
    pthread_exit(NULL);
}

void *consumer(void * arg){
    int no =*((int *)arg);
    int st = no;
    while(1){
        wait(&sem);
          if(state==1){
            printf("consumer consumes %d\n",no);
            no++;
            state =0;
          }
        signal(&sem);
    }
    pthread_exit(NULL);
}


int main(){
    pthread_t id1,id2;
    pthread_create(&id1,NULL,(void*)producer,&no);
    pthread_create(&id2,NULL,(void*)consumer,&no);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    return 0;
}
