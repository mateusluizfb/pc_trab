typedef struct Assistant {
  int   index;
  char  name[15];
  short ammo;
} Assistant;

typedef struct Gun {
  int   index;
  short ammo;
} Gun;

typedef struct Shooter {
  int   index;
  char  name[15];
  void  (*atira)(Gun *gun);
} Shooter;

typedef struct Spaceship {
  int       index;
  char      name[20];
  Shooter   shooters[4];
  Gun       guns[4];
  Assistant assistant;
} Spaceship;

void atira(Gun *gun);
