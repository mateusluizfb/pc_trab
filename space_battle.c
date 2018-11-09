#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "./lib/entities.h"
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

Spaceship spaceship_a;
Assistant assistant_a;
Gun guns_a[4];

Spaceship spaceship_b;
Assistant assistant_b;
Gun guns_b[4];

int game_over_called = 0;

pthread_mutex_t lock_spaceship_a;
pthread_mutex_t lock_spaceship_b;
pthread_mutex_t lock_game_over;

pthread_mutex_t sem_assistente_a;
pthread_mutex_t sem_assistente_b;

pthread_t thread_spaceships_guns[8];
pthread_t thread_assistants[2];

// int shoot_time() {
//   time_t t;
//   srand((unsigned) time(&t));
//   return rand() % 5;
// }
//
// int assistant_time() {
//
//   return ( rand() % 5 ) + 1;
// }

void game_over() {
  printf("          _ ._  _ , _ ._       \n");
  printf("        (_ ' ( `  )_  .__)     \n");
  printf("      ( (  (    )   `)  ) _)   \n");
  printf("     (__ (_   (_ . _) _) ,__)  \n");
  printf("         `~~`\\ ' . /`~~`      \n");
  printf("              ;   ;            \n");
  printf("              /   \\            \n");
  printf("_____________/_ __ \\_____________\n");

  for (size_t i = 0; i < 8; i++) {
    pthread_kill(thread_spaceships_guns[i], SIGKILL);
  }
}

void assistant_a_work(Gun *gun) {
  pthread_mutex_lock(&sem_assistente_a);
  (*gun).ammo = 4;
  printf("\n");
  printf("Assistente Nave A - Arma %d sem munição, indo buscar balas de canhão\n", (*gun).index);
  printf("   ⚆ _ ⚆             >=>     \n");
  printf("                   >=>>=>    \n");
  sleep(( rand() % 5 ) + 1);
  printf("\n");
  printf("Assistente Nave A - Arma %d carregada!!!  ̿ ̿ ̿'̿'\\̵͇̿̿\\з=(•_•)=ε/̵͇̿̿/'̿'̿ ̿ \n", (*gun).index);
  pthread_mutex_unlock(&sem_assistente_a);
}

void * assistant_b_work(Gun *gun) {
  pthread_mutex_lock(&sem_assistente_b);
  (*gun).ammo = 4;
  printf("\n");
  printf("Assistente Nave B - Arma %d sem munição, indo buscar balas de canhão\n", (*gun).index);
  printf("   ⚆ _ ⚆             >=>     \n");
  printf("                   >=>>=>    \n");
  sleep(( rand() % 5 ) + 1);
  printf("\n");
  printf("Assistente Nave B - Arma %d carregada!!! ̿ ̿ ̿'̿'\\̵͇̿̿\\з=(•_•)=ε/̵͇̿̿/'̿'̿ ̿ \n", (*gun).index);
  pthread_mutex_unlock(&sem_assistente_b);
}

void * spaceship_a_attack(void * args) {
  int gun_arr_index = *((int *) args);
  while(1) {
    if (guns_a[gun_arr_index].ammo <= 0) {
      assistant_a_work(&guns_a[gun_arr_index]);
    }
    guns_a[gun_arr_index].ammo--;
    sleep(( rand() % 5 ) + 1);

    pthread_mutex_lock(&lock_spaceship_b);
      int dano = ( rand() % 5 ) + 1;

      printf("\nNave A - Arma %d atirou dando %d de dano, sobraram %d balas de canhão.\n", guns_a[gun_arr_index].index, dano, guns_a[gun_arr_index].ammo);
      printf("   /\\                    /\\     \n");
      printf("  |A |      ===}=>      |B |     \n");
      printf("  VvvV                  VvvV     \n");
      printf("\n");

      spaceship_b.life -= dano;
      if (spaceship_b.life <= 0) {
        pthread_mutex_lock(&lock_game_over);
        if (!game_over_called) {
          game_over_called = 1;
          printf("Nave B - IS DIE\n");
          game_over();
        }
        pthread_mutex_unlock(&lock_game_over);
      } else {
        if (spaceship_b.life <= 0) {
          printf("NAVE B - HP: 0\n");
        } else {
          printf("NAVE B - HP: %d\n", spaceship_b.life);
        }
      }
    pthread_mutex_unlock(&lock_spaceship_b);
  }
}

void * spaceship_b_attack(void * args) {
  int gun_arr_index = *((int *) args);
  while(1) {
    if (guns_b[gun_arr_index].ammo <= 0) {
      assistant_b_work(&guns_b[gun_arr_index]);
    }
    guns_b[gun_arr_index].ammo--;
    sleep(( rand() % 5 ) + 1);

    pthread_mutex_lock(&lock_spaceship_a);

      int dano = ( rand() % 5 ) + 1;
      printf("\nNave B -- Arma %d atirou dando %d de dano, sobraram %d balas de canhão.\n", guns_b[gun_arr_index].index, dano, guns_b[gun_arr_index].ammo);
      printf("   /\\                    /\\     \n");
      printf("  |A |      <={===      |B |     \n");
      printf("  VvvV                  VvvV     \n");
      printf("\n");

      spaceship_a.life -= dano;
      if (spaceship_a.life <= 0) {
        pthread_mutex_lock(&lock_game_over);
        if (!game_over_called) {
          game_over_called = 1;
          printf("Nave A - IS DIE\n");
          game_over();
        }
        pthread_mutex_unlock(&lock_game_over);
      } else {
        if (spaceship_a.life <= 0) {
          printf("NAVE A - HP: 0\n");
        } else {
          printf("NAVE A - HP: %d\n", spaceship_a.life);
        }
      }
    pthread_mutex_unlock(&lock_spaceship_a);
  }
}

void main() {
  srand(time(NULL));

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
  // pthread_create(&thread_assistants[0], NULL, assistant_a_work, NULL);
  // pthread_create(&thread_assistants[1], NULL, assistant_b_work, NULL);

  // sem_init(&sem_assistente_a, 0, 1);

  for (size_t i = 0; i < 8; i++) {
    pthread_join(thread_spaceships_guns[i], NULL);
  }
  // pthread_join(thread_assistants[0], NULL);
  // pthread_join(thread_assistants[1], NULL);
}
