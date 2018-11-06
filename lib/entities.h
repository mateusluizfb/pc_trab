typedef struct Assistant {
  int   index;
  char  name[15];
  short ammo;
} Assistant;

typedef struct Gun {
  int   index;
  short ammo;
} Gun;

typedef struct Spaceship {
  int       index;
  char      name[20];
  int       life;
  Gun       *guns;
  Assistant assistant;
} Spaceship;

void shoot(Gun *gun);
void create_spaceship(Spaceship *spaceship, Gun *guns, Assistant *assistant, int index, char name[20], char assistant_name[15]);
