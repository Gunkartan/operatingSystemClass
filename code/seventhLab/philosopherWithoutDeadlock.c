#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 5

sem_t forks[N];
pthread_mutex_t mutex;

int left(int p) {
    return p;
}

int right(int p) {
    return (p + 1) % N;
}

void think(int p) {
    printf("Philosopher %d is thinking.\n", p);
    usleep(100000);
}

void eat(int p) {
    printf("Philosopher %d starts eating.\n", p);
    usleep(100000);
    printf("Philosopher %d finishes eating.\n", p);
}

void getForks(int p) {
    pthread_mutex_lock(&mutex);
    sem_wait(&forks[left(p)]);
    printf("Philosopher %d picked up the left fork %d.\n", p, left(p));
    sem_wait(&forks[right(p)]);
    printf("Philosopher %d picked up the right fork %d.\n", p, right(p));
    pthread_mutex_unlock(&mutex);
}

void putForks(int p) {
    sem_post(&forks[left(p)]);
    sem_post(&forks[right(p)]);
    printf("Philosopher %d put down forks.\n", p);
}

void *philosopher(void *num) {
    int p = *(int *)num;

    while (1) {
        think(p);
        getForks(p);
        eat(p);
        putForks(p);
    }
}

int main() {
    pthread_t tid[N];
    int phil[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}