#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;
sem_t mutex;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mutex);

    printf("Reader %d is reading shared data: %d\n", reader_id, shared_data);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mutex);

    return NULL;
}
void *writer(void *arg) {
    int writer_id = *(int *)arg;

    sem_wait(&rw_mutex);
    shared_data += 10;
    printf("Writer %d modified shared data to: %d\n", writer_id, shared_data);
    sleep(2);
    sem_post(&rw_mutex);

    return NULL;
}
int main() {
    pthread_t readers[5], writers[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < 5; i++)
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    return 0;
}
