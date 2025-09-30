#include <stdio.h>
#include <pthread.h>

int counter = 0;

void *increment(void *arg) {
    for (int i = 0; i < 10000; i++) {
        counter += 2;
    }

    return NULL;
}

int main() {
    pthread_t first, second;
    pthread_create(&first, NULL, increment, NULL);
    pthread_create(&second, NULL, increment, NULL);
    pthread_join(first, NULL);
    pthread_join(second, NULL);
    printf("%d\n", counter);

    return 0;
}