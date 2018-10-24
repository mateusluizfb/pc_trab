#include <stdio.h>
#include "entities.h"

void atira(Gun *gun) {
  printf("atirei \n");
  (*gun).ammo--;
}
