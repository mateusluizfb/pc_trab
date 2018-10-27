#include <stdio.h>
#include <string.h>
#include "entities.h"

void shoot(Gun *gun) {
  printf("atirei \n");
  (*gun).ammo--;
}

void create_guns(Gun *guns, int quantity) {
  for (int i = 0; i < quantity; i++) {
    guns[i].index = i + 1;
    guns[i].ammo = 4;
  }
}

void create_assistant(Assistant *assistant, int index, char assistant_name[15]) {
  (*assistant).index = index;
  strcpy((*assistant).name, assistant_name);
}

void create_spaceship(Spaceship *spaceship, Gun *guns, Assistant *assistant, int index, char name[20], char assistant_name[15]) {
  (*spaceship).index = index;
  strcpy((*spaceship).name, name);

  create_guns(guns, 4);
  (*spaceship).guns = guns;

  create_assistant(assistant, index, assistant_name);
  (*spaceship).assistant = *assistant;
}
