#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;
pthread_mutex_t mut;

struct thread_arg {
    int vezes;
};

void *thread_func(void *arg) {
    struct thread_arg *targ = (struct thread_arg *) arg;
    int local_id;

    for (int i = 0; i < targ->vezes; i++) {
        pthread_mutex_lock(&mut);
        local_id = count++;
        pthread_mutex_unlock(&mut);

        work(local_id);
    }
    return NULL;
}