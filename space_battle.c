#include <stdio.h>
#include <string.h>
#include "./lib/entities.h"

void main() {
  Spaceship spaceship_a;
  Assistant assistant_a;
  Gun guns_a[4];
  for (int i = 0; i < 4; i++) {
    Gun gun;
    guns_a[i] = gun;
  }
  create_spaceship(&spaceship_a, guns_a, &assistant_a, 1, "Nave A", "Assistente A");

  Spaceship spaceship_b;
  Assistant assistant_b;
  Gun guns_b[4];
  for (int i = 0; i < 4; i++) {
    Gun gun;
    guns_b[i] = gun;
  }
  create_spaceship(&spaceship_b, guns_b, &assistant_b, 1, "Nave B", "Assistente B");

  
}
