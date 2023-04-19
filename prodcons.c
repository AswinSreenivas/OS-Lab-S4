#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE]; // shared buffer
int fill = 0; // index to fill buffer
int use = 0; // index to use buffer

sem_t empty; // semaphore to track empty buffer slots
sem_t full; // semaphore to track full buffer slots
pthread_mutex_t mutex; // mutex lock for buffer access

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % BUFFER_SIZE;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % BUFFER_SIZE;
    return tmp;
}

void *producer(void *arg) {
    int i, item;
    for (i = 0; i < BUFFER_SIZE; i++) {
        item = i; // create item
        sem_wait(&empty); // wait for empty slot
        pthread_mutex_lock(&mutex); // lock buffer
        put(item); // put item in buffer
        printf("Producer produced %d\n", item);
        pthread_mutex_unlock(&mutex); // unlock buffer
        sem_post(&full); // signal full slot
    }
    pthread_exit(0);
}

void *consumer(void *arg) {
    int i, item;
    for (i = 0; i < BUFFER_SIZE; i++) {
        sem_wait(&full); // wait for full slot
        pthread_mutex_lock(&mutex); // lock buffer
        item = get(); // get item from buffer
        printf("Consumer consumed %d\n", item);
        pthread_mutex_unlock(&mutex); // unlock buffer
        sem_post(&empty); // signal empty slot
    }
    pthread_exit(0);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    
    // create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // join threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // cleanup semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
