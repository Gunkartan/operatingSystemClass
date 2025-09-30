#include <stdio.h>
#include <pthread.h>

int counter = 0;

void *increment(void *arg) {
    for (int i = 0; i < 100000; i++) {
        counter += 2;
    }

    return NULL;
}

int main() {
    pthread_t first, second;
    pthread_create(&first, NULL, increment, NULL);
    pthread_create(&second, NULL, increment, NULL); //Comment this line to test the validity of the code using a single thread.
    pthread_join(first, NULL);
    pthread_join(second, NULL); //Comment this line to test the validity of the code using a single thread.
    printf("%d\n", counter);

    return 0;
}