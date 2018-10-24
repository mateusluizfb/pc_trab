#include <stdio.h>
#include <string.h>
#include "./lib/entities.h"

void main() {

  Assistant assistant;
  assistant.index = 1;
  strcpy(assistant.name, "Ajudante Joao");
  assistant.ammo = 2;

  printf("%d\n", assistant.index);
  printf("%s\n", assistant.name);
  printf("%d\n", assistant.ammo);

  Gun gun;
  gun.index = 10;
  gun.ammo = 5;

  Shooter shooter;
  shooter.index = 2;
  strcpy(shooter.name, "Atirador Marcos");
  shooter.atira = atira;
  shooter.atira(&gun);

  Spaceship spaceship;
  spaceship.index = 1;
  strcpy(spaceship.name, "Nave A");
  Shooter shooter_array[4];
  shooter_array[0] = shooter;
  Gun gun_array[4];
  gun_array[0] = gun;
  memcpy(spaceship.shooters, shooter_array, sizeof shooter_array);
  memcpy(spaceship.guns, gun_array, sizeof gun_array);
  spaceship.assistant = assistant;

}
