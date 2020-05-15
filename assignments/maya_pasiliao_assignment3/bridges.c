// wait -> semaphore is locked
// signal -> semaphore is released

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t ok_to_cross = 1;
sem_t mutex;

// void enter_bridge();
// void exit_bridge();

void* thread(void* arg) {
    //wait
    sem_wait(&mutex);
    printf("\nEntered..\n");

    //critical section
    sleep(4);

    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
}

int main () {
    sem_init(&mutex, 0, 1);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread,NULL);
    sleep(2);
    pthread_create(&t2,NULL,thread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);

    return 0;
}

// // wait
// void enter_bridge() {
//     sem_wait(ok_to_cross);
//     printf()
// }

// // signal
// void exit_bridge() {
//     sem_post(ok_to_cross);
// }