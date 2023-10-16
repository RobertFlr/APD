#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
    schelet pentru exercitiul 5
*/
int *arr;
int array_size;
int num_threads;
typedef struct helper{
  int start, end;
}helper;

void *func(void* arg) {
  helper *h = (helper *)arg;
  for(int i = h->start; i < h->end; i++) {
    arr[i]++;
  }
}

int min(int a, int b) {
  return (a < b) ? a : b;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Specificati dimensiunea array-ului si numarul de thread-uri\n");
    exit(-1);
  }
  void *status;
  array_size = atoi(argv[1]);
  num_threads = atoi(argv[2]);
  pthread_t threads[num_threads];
  helper* helpers = malloc(num_threads * sizeof(helper));

  arr = malloc(array_size * sizeof(int));
  for (int i = 0; i < array_size; i++) {
    arr[i] = i;
  }
  printf("%d", arr[array_size - 1]);
  //thread shenanigans
   for (int id = 0; id < num_threads; id++) {
    helpers[id].start = id * (double)array_size / num_threads;
    helpers[id].end = min((id + 1) * (double)array_size / num_threads, array_size);
    int r = pthread_create(&threads[id], NULL, func, (void*)&helpers[id]);
    if (r) {
      printf("EERROR %d\n", id);
      exit(-1);
    }
  }

  for (int id = 0; id < num_threads; id++) {
    int r = pthread_join(threads[id], &status);

    if (r) {
      printf("Eroare la asteptarea thread-ului %d\n", id);
      exit(-1);
    }
  }
  //no more thread shenanigans
  printf("%d", arr[array_size - 1]);

  return 0;
}
