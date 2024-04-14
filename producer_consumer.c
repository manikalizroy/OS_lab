#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE]; // Shared buffer
int itemCount = 0; // Number of items in the buffer

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for buffer access
pthread_cond_t full = PTHREAD_COND_INITIALIZER; // Condition variable for buffer full
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; // Condition variable for buffer empty

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // Generate a random item
        pthread_mutex_lock(&mutex);
        while (itemCount == BUFFER_SIZE) {
            pthread_cond_wait(&full, &mutex); // Wait if buffer is full
        }
        buffer[itemCount++] = item; // Add item to buffer
        printf("Produced: %d\n", item);
        pthread_cond_signal(&empty); // Signal that buffer is not empty
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3); // Simulate production time
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (itemCount == 0) {
            pthread_cond_wait(&empty, &mutex); // Wait if buffer is empty
        }
        item = buffer[--itemCount]; // Remove item from buffer
        printf("Consumed: %d\n", item);
        pthread_cond_signal(&full); // Signal that buffer is not full
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3); // Simulate consumption time
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Wait for threads to finish (which will never happen in this case)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return 0;
}
