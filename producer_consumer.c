#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

pthread_mutex_t mutex;
sem_t empty, full, consumer_ready;

void wait(sem_t *sem) {
    sem_wait(sem);
}

void signal(sem_t *sem) {
    sem_post(sem);
}

void *producer(void *arg) {
    int item = 1;
    while (1) {
        // Produce item
        sleep(1); // Simulate some work to produce item
        
        // Wait for buffer slot to be empty
        wait(&empty);

        // Acquire mutex to access the buffer
        pthread_mutex_lock(&mutex);
        
        // Add item to buffer
        buffer[in] = item;
        printf("Producer produces: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        
        // Release mutex
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer is no longer empty
        signal(&full);
        
        // Wait for consumer to be ready
        wait(&consumer_ready);

        item++;
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    while (1) {
        // Wait for item in buffer
        wait(&full);
        
        // Acquire mutex to access the buffer
        pthread_mutex_lock(&mutex);
        
        // Consume item from buffer
        item = buffer[out];
        printf("Consumer consumes: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        
        // Release mutex
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer slot is empty
        signal(&empty);
        
        // Signal producer that consumer is ready for next item
        signal(&consumer_ready);
        
        sleep(2); // Simulate some work to consume item
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&consumer_ready, 0, 0);
    
    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&consumer_ready);
    
    return 0;
}



----------------------------------------------------------------------------------------------------------------------------

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
