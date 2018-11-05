#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "./lib/entities.h"
#include <time.h>
#include <unistd.h>

Spaceship spaceship_a;
Assistant assistant_a;
Gun guns_a[4];

Spaceship spaceship_b;
Assistant assistant_b;
Gun guns_b[4];

// pthread_mutex_t lock_;

int shoot_time() {
  srand(time(NULL));
  return ( rand() % 3 ) + 1;
}

void * spaceship_a_attack(void * args) {
  int gun_arr_index = *((int *) args);
  while(1) {
    printf("Nave A -- Arma %d\n", guns_a[gun_arr_index].index);
    shoot(&guns_a[gun_arr_index]);
    int tempo = shoot_time();
    printf("%d\n", tempo);
    sleep(tempo);
  }
}

void * spaceship_b_attack(void * args) {
  int gun_arr_index = *((int *) args);
  while(1) {
    printf("Nave B -- Arma %d\n", guns_b[gun_arr_index].index);
    shoot(&guns_a[gun_arr_index]);
    sleep(shoot_time());
  }
}

void * assistant_a_work(/* arguments */) {
}

void * assistant_b_work(/* arguments */) {
  /* code */
}

void main() {
  for (int i = 0; i < 4; i++) {
    Gun gun;
    guns_a[i] = gun;
  }
  create_spaceship(&spaceship_a, guns_a, &assistant_a, 1, "Nave A", "Assistente A");
  for (int i = 0; i < 4; i++) {
    Gun gun;
    guns_b[i] = gun;
  }
  create_spaceship(&spaceship_b, guns_b, &assistant_b, 1, "Nave B", "Assistente B");

  pthread_t thread_spaceships_guns[8];
  pthread_t thread_assistants[2];

  for (size_t i = 0; i < 4; i++) {
    int * gun_arr_index = (int *) malloc(sizeof(int));
    *gun_arr_index = i;
    pthread_create(&thread_spaceships_guns[i], NULL, spaceship_a_attack, (void *) (gun_arr_index));
  }
  for (size_t i = 0; i < 4; i++) {
    int * gun_arr_index = (int *) malloc(sizeof(int));
    *gun_arr_index = i;
    pthread_create(&thread_spaceships_guns[i], NULL, spaceship_b_attack, (void *) (gun_arr_index));
  }
  pthread_create(&thread_assistants[0], NULL, assistant_a_work, NULL);
  pthread_create(&thread_assistants[1], NULL, assistant_b_work, NULL);
  for (size_t i = 0; i < 8; i++) {
    pthread_join(thread_spaceships_guns[i], NULL);
  }
  pthread_join(thread_assistants[0], NULL);
  pthread_join(thread_assistants[1], NULL);
}
