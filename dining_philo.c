#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t forks[N];  // One mutex for each fork

void* philosopher(void* num) {
    int id = *(int*)num;
    int left= id;
    int right = (id+1)%N;

    while(1){
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d picked up left fork\n", id);

        // Pick up right fork
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d picked up right fork and is eating\n", id);

        sleep(2);  // Simulate eating

        // Put down forks
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d put down forks and starts thinking again\n", id);
    }

    return NULL;
}

int main(){
    pthread_t threads[N];
    int ids[N];

    for(int i=0; i<N; i++){
        pthread_mutex_init(&forks[i],NULL);
    }

    for(int i=0; i<N; i++){
        ids[i]=i;
        pthread_create(&threads[i],NULL,philosopher,&ids[i]);
    }

    for(int i=0; i<N; i++){
        pthread_join(threads[i],NULL);
    }
    return 0;
}
