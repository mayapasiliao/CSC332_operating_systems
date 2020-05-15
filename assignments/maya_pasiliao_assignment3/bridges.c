// Compile with -pthread
// This program assumes there can only be one farmer on the bridge at a time
// wait -> semaphore is locked
// signal -> semaphore is released

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t ok_to_cross;

void* cross_bridge(void* arg) {
    // wait
    sem_wait(&ok_to_cross);
    printf("%s farmer can cross bridge\n", arg);

    // critical section
    int seconds = rand() % 4;
    printf("%s is traveling on the bridge...\n", arg);
    sleep(seconds);

    // signal
    printf("%s farmer has left the bridge\n\n", arg);
    sem_post(&ok_to_cross);

}

int main () {
    // Initialize semaphore to 1
    sem_init(&ok_to_cross, 0, 1);

    pthread_t north1, south1, north2;
    pthread_create(&north1, NULL, cross_bridge, "north1");
    pthread_create(&south1, NULL, cross_bridge, "south1");
    pthread_create(&north2, NULL, cross_bridge, "north2");

    pthread_join(north1, NULL);
    pthread_join(south1, NULL);
    pthread_join(north2, NULL);

    sem_destroy(&ok_to_cross);

    return 0;
}