#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#define THREADS 2
#define ITERATIONS 1500000

typedef struct qnode {
    struct qnode *next;
    _Atomic int locked;
} qnode_t;

typedef struct {
    _Atomic(qnode_t *) tail;
} mcs_lock_t;

void mcs_lock(mcs_lock_t *lock, qnode_t *node) {
    node->next = NULL;
    atomic_store_explicit(&node->locked, 1, memory_order_relaxed);
    qnode_t *pred = atomic_exchange_explicit(&lock->tail, node, memory_order_acq_rel);

    if (pred != NULL) {
        pred->next = node;

        while (atomic_load_explicit(&node->locked, memory_order_acquire));
    }
}

void mcs_unlock(mcs_lock_t *lock, qnode_t *node) {
    if (node->next == NULL) {
        qnode_t *expected = node;

        if (atomic_compare_exchange_strong_explicit(&lock->tail, &expected, NULL, memory_order_release, memory_order_relaxed)) {
            return;
        }

        while (node->next == NULL);
    }

    atomic_store_explicit(&node->next->locked, 0, memory_order_release);
}

mcs_lock_t lock = { ATOMIC_VAR_INIT(NULL) };
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