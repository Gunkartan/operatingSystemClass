#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREADS 2
#define ITERATIONS 15000

typedef struct qnode {
    struct qnode *next;
    int locked;
} qnode_t;

typedef struct {
    qnode_t *tail;
} mcs_lock_t;

void mcs_lock(mcs_lock_t *lock, qnode_t *node) {
    node->next = NULL;
    node->locked = 1;
    qnode_t *pred = lock->tail;
    lock->tail = node;

    if (pred != NULL) {
        pred->next = node;

        while (node->locked);
    }
}

void mcs_unlock(mcs_lock_t *lock, qnode_t *node) {
    if (node->next == NULL) {
        if (lock->tail == node) {
            lock->tail = NULL;

            return;
        }

        while (node->next == NULL);
    }

    node->next->locked = 0;
}

mcs_lock_t lock = { NULL };
long counter = 0;

void *worker(void *arg) {
    qnode_t node;

    for (int i = 0; i < ITERATIONS; i++) {
        mcs_lock(&lock, &node);
        counter++;
        mcs_unlock(&lock, &node);
    }

    return NULL;
}

int main(void) {
    pthread_t threads[THREADS];

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected: %d | Counter: %ld\n", THREADS * ITERATIONS, counter);

    return 0;
}