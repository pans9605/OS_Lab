#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 // Size of the buffer

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;  // Counts empty slots
sem_t full;   // Counts filled slots
pthread_mutex_t mutex; // Ensures mutual exclusion

void* producer(void* arg) {
    int item = 1;
    while (1) {
        sem_wait(&empty); // Wait for empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item;
        printf("Produced: %d at %d\n", item, in);
        in = (in + 1) % SIZE;
        item++;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Increase filled slots

        sleep(1);
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full); // Wait for filled slot
        pthread_mutex_lock(&mutex); // Enter critical section

        int item = buffer[out];
        printf("Consumed: %d from %d\n", item, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Increase empty slots

        sleep(1);
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);     // No items to start with
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}

