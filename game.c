#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

char startNewGame;
char action;
int gameNotOver = 1;
char playerMove;
int oldMove[2] = {7,3};
int player[2] = {7,3};
int hp = 100;
int damage = 10;
int level = 1;
int sword = 0;
int xp = 0;
int eHp;
int eDamage;
int runAway = 0;
struct Enemy {
  char  name[20];
  char  attack[10];
};
struct Boss {
  char name[20];
  char attack[20];
  char in1[50];
  char in2[50];
  char out1[50];
  char out2[50];
  int  sword;
  char swordName[20];
  int  lvl;
};
struct Enemy enemies[10];
strcpy( enemies[0].name, "ENEMY");
strcpy( enemies[0].attack, "HITS");
strcpy( enemies[1].name, "WEAK IMP");
strcpy( enemies[1].attack, "FLAILS AT");
strcpy(enemies[2].name, "BEEFY IMP");
strcpy(enemies[2].attack, "BITES");
strcpy(enemies[3].name, "STRONG IMP");
strcpy(enemies[3].attack, "KICKS");
strcpy(enemies[4].name, "GUARDIAN IMP");
strcpy(enemies[4].attack, "PARRIES");
strcpy(enemies[5].name, "YOUNG ORC");
strcpy(enemies[5].attack, "PUNCHES");
strcpy(enemies[6].name, "WARRIOR ORC");
strcpy(enemies[6].attack, "CHARGES AT");
strcpy(enemies[7].name, "ASSASSIN ORC");
strcpy(enemies[7].attack, "STABS");
strcpy(enemies[8].name, "SMALL GOBLIN");
strcpy(enemies[8].attack, "TRIPS");
strcpy(enemies[9].name, "UGLY GOBLIN");
strcpy(enemies[9].attack, "LOOKS AT");
struct Boss bosses[3];
strcpy(bosses[0].name, "THE IMPERIAL IMP");
strcpy(bosses[0].attack, "THROWS AN IMP AT YOU");
strcpy(bosses[0].in1, "MUHAHA ... FOOLISH HUMAN ... YOU HAVE ENTERED MY DOMAIN");
strcpy(bosses[0].in2, "YOU SHALL NOW FACE THE WRATH OF THE");
strcpy(bosses[0].out1, "NOOOOOO YOU CURSED HUMAN ... MY COUSINS WILL AVENGE ME");
strcpy(bosses[0].out2, "AS THE IMP DIES YOU NOTICE A DOOR BEHIND HIS THRONE\nINSIDE YOU FIND AN OLD SWORD");
       bosses[0].sword = 1;
strcpy(bosses[0].swordName, "RUSTY SWORD");
       bosses[0].lvl = 4;

strcpy(bosses[1].name, "THE OMINOUS ORC");
strcpy(bosses[1].attack, "THROWS A PILLAR AT YOU");
strcpy(bosses[1].in1, "SO YOU HAVE COME ... IDIOT HUMAN ... YOU HAVE ENTERED MY CASTLE");
strcpy(bosses[1].in2, "YOU SHALL NOW FACE THE FURY OF THE");
strcpy(bosses[1].out1, "FIRST YOU KILL MY COUSIN ... AND THEN YOU SLAY ME");
strcpy(bosses[1].out2, "AS THE ORC DIES HE DROPS HIS MASSIVE SWORD\nIT LOOKS PRETTY MEAN BUT ALSO POWERFUL");
       bosses[1].sword = 2;
strcpy(bosses[1].swordName, "GOBLINSLAYER");
       bosses[1].lvl = 7;

strcpy(bosses[2].name, "THE GLUTINOUS GOBLIN");
strcpy(bosses[2].attack, "CONSUMES A GOBLIN TO SCARE YOU");
strcpy(bosses[2].in1, "HEHEEHE ... TASTY HUMAN ... YOU HAVE ENTERED MY CAVES");
strcpy(bosses[2].in2, "YOU SHALL NOW FACE THE HUNGER OF THE");
strcpy(bosses[2].out1, "ARGHH YOU STUPID HUMAN ... THE SPIDERS WILL FINISH YOU OFF");
strcpy(bosses[2].out2, "AS THE GOBLIN DIES YOU NOTICE A NECKLACE WITH A KEY ON HIS NECK\nIT UNLOCKS A TREASURE CHEST");
       bosses[2].sword = 3;
strcpy(bosses[2].swordName, "SPIDERBANE");
       bosses[2].lvl = 10;

int map[64][60] = { // Looked up how to declare a matrix at https://beginnersbook.com/2014/01/2d-arrays-in-c-example/
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+4,-4,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+3,+3,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+2,+2,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,+4,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+5,+5,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+5,+5,+5,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,+6,+6,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,-5,+6,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,+6,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+6,+6,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,+7,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,+7,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,+7,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+8,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+9,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+9,-6,+9,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+9,+9,+9,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+6,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+5,+6,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+4,+5,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+4,+3,+4,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+1,+3,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+2,+2,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,-9,+2,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+2,+2,+3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+2,+1,+2,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+6,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+5,+6,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+4,+5,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+4,+3,+4,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+1,+3,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+1,+1,+1,+2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+8,+7,+8,+9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+7,+6,+7,+8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+6,+5,+6,+7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+5,+4,+5,+6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+4,+3,+4,+5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,+3,+1,+3,+4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
//  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
//  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  };

void move ();       //done
void cycle ();      //done
void display();     //done
void fight ();      //done
void playerTurn (); //done
void enemyTurn ();  //done
void newGame();     //done
void game ();       //done
void levelUp();     //done
void displayMap();
void bossDead();
void bossIntro();
void bossFight();
void bossTurn();
void fightSetUp();

int main () {
  //system("MODE 56,37");
  system("MODE 120,75");
  _setmode(_fileno(stdout), 0x00020000);
  newGame();
  return 0;
}

void newGame () {
  wprintf(L"\e[1;1H\e[2J");
  wprintf(L"\033[0;33m");
  wprintf(L"CONFIRM:\n\ty = yes\n\tn = no\nMOVEMENT:\n\tw = up\n\ta = left\n\ts = down\n\td = right\n\tz = map\n\tc = camp\nACTIONS:\n\ta = attack\n\tq = inventory\n\tw = wait\n\ts = retreat\n");
  wprintf(L"\033[0;32m");
  wprintf(L"NEW GAME?\t");
  wprintf(L"\033[0;33m");
  wprintf(L"\033[0;36m");
  scanf(" %c",&startNewGame);
  wprintf(L"\033[0m");
  if (startNewGame == 'n') {
    wprintf(L"GOODBYE!");
    wprintf(L"\033[0m");
  } else if (startNewGame == 'd') {
    wprintf(L"DEV MODE!\n");
    wprintf(L"\033[0m");
    gameNotOver = 1;
    player[0] = 7;
    player[1] = 3;
    hp = 100;
    damage = 10;
    level = 100;
    xp = 10000;
    game();
  } else {
    wprintf(L"GAME START!\n");
    wprintf(L"\033[0m");
    gameNotOver = 1;
    player[0] = 7;
    player[1] = 3;
    hp = 100;
    damage = 10;
    level = 1;
    xp = 0;
    game();
  }
}

void game () {
  while (gameNotOver) {
    cycle();
  }
  wprintf(L"\033[0;33m");
  wprintf(L"GAME OVER!\n");
  wprintf(L"\033[0;34m");
  wprintf(L"YOU REACHED LVL %d\n",level);
  wprintf(L"\033[0m");
  newGame();
}

void cycle () {
  display();
  move();
  display();
  fightSetUp();
}

void move () {
  playerMove = ' ';
  wprintf(L"\033[0;32m");
  wprintf(L"MOVE WHERE?\t");
  wprintf(L"\033[0;36m");
  scanf(" %c", &playerMove); // couldnt figure out why scanf("%c") wasnt working, apparently scanf reads the enter key as an input and so gets skipped https://stackoverflow.com/questions/29775323/scanf-function-seems-to-be-skipped-in-c#:~:text=The%20problem%20is%20because%20of,second%20call%20to%20scanf()%20.&text=So%2C%20the%20newline%20character%20is,for%20input%20for%20that%20variable.
  wprintf(L"\033[0m");
  switch (playerMove) {
    case 'w':
      if (map[player[0]-1][player[1]] == -1) {
        wprintf(L"\033[0;33m");
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        wprintf(L"\033[0m");
        move();
      } else {

        oldMove[0] = player[0];
        player[0] = player[0] - 1;
      }
      break;
    case 'a':
      if (map[player[0]][player[1]-1] == -1) {
        wprintf(L"\033[0;33m");
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        wprintf(L"\033[0m");
        move();
      } else {
        oldMove[1] = player[1];
        player[1] = player[1] - 1;
      }
      break;
    case 's':
      if (map[player[0]+1][player[1]] == -1) {
        wprintf(L"\033[0;33m");
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        wprintf(L"\033[0m");
        move();
      } else {
        oldMove[0] = player[0];
        player[0] = player[0] + 1;
      }
      break;
    case 'd':
      if (map[player[0]][player[1]+1] == -1) {
        wprintf(L"\033[0;33m");
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        wprintf(L"\033[0m");
        move();
      } else {
        oldMove[1] = player[1];
        player[1] = player[1] + 1;
      }
      break;
    case 'c':
      wprintf(L"\033[0;34m");
      wprintf(L"YOU CAMP FOR THE NIGHT\n");
      wprintf(L"\033[0m");
      break;
    case 'z':
      wprintf(L"\033[0;34m");
      wprintf(L"YOU OPEN UP YOUR MAP\n");
      wprintf(L"\033[0m");
      displayMap();
      break;
    default:
      wprintf(L"\033[0;33m");
      wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
      wprintf(L"\033[0m");
      move();
      break;
  }
}

void display () {
  int i;
  int j;
  wprintf(L"\033[1;30m");
  wprintf(L"██████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
  for (i=player[0]-2;i<player[0]+3;i++) {
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    for (j=player[1]-2;j<player[1]+3;j++) {
      if ((i == player[0]) && (j == player[1])) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"&&");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] == 0) {
        //
      } else if (map[i][j] == -1) {
        wprintf(L"\033[0;37m");
        wprintf(L"██");
        wprintf(L"\033[0m");
      } else if (map[i][j] > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"  ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] < -3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"**");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      }
    }
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    wprintf(L"\n");
  }
  wprintf(L"\033[1;30m");
  wprintf(L"██████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
}

void displayMap () {
  int i;
  int j;
  wprintf(L"\033[1;30m");
  wprintf(L"████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
  for (i=0;i<63;i++) {
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    for (j=0;j<60;j++) {
      if ((i == player[0]) && (j == player[1])) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"&&");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] == 0) {
        //
      } else if (map[i][j] == -1) {
        wprintf(L"\033[0;37m");
        wprintf(L"██");
        wprintf(L"\033[0m");
      } else if (map[i][j] > 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"  ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      } else if (map[i][j] < -3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
        wprintf(L"**");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
      }
    }
    wprintf(L"\033[1;30m");
    wprintf(L"██");
    wprintf(L"\033[0m");
    wprintf(L"\n");
  }
  wprintf(L"\033[1;30m");
  wprintf(L"████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████");
  wprintf(L"\033[0m");
  wprintf(L"\n");
}

void levelUp () {
  hp = hp + 10;
  damage++;
  level++;
  wprintf(L"\033[0;34m");
  wprintf(L"YOU HAVE REACHED LEVEL %d\n", level);
  wprintf(L"\033[0m");
}

void fightSetUp() {
  runAway = 0;
  eHp = (map[player[0]][player[1]] * 75);
  eDamage = (map[player[0]][player[1]] * 10);
  hp = 100 + ((level-1) * 10);
  damage = 10 + ((level-1) * 1);
  if (eHp < 0) {
    eHp = bosses[abs(map[player[0]][player[1]]+4)] * 100;
    eDamage = bosses[abs(map[player[0]][player[1]]+4)] * 12;
    bossFight();
  } else {
    fight();
  }

}

void fight () {
  wprintf(L"\033[0;33m");
  wprintf(L"A LVL %d ENEMY HAS COME TO MURDER YOU!!\n", map[player[0]][player[1]]);
  wprintf(L"\033[0m");
  while ((hp > 0) && (eHp > 0) && (runAway == 0)) {
    playerTurn();
    if ((hp > 0) && (eHp > 0)) {
      enemyTurn();
    }
  }
  if (hp <= 0) {
    gameNotOver = 0;
  } else if (eHp <= 0) {
    wprintf(L"\033[0;34m");
    wprintf(L"YOU WIN THE FIGHT!\n");
    wprintf(L"\033[0m");
    xp = xp + (map[player[0]][player[1]] * 50);
    wprintf(L"\033[0;33m");
    wprintf(L"%dXP GAINED\n", (map[player[0]][player[1]] * 50));
    wprintf(L"\033[0m");
    while (xp >= level*100) {
      levelUp();
    }
  }
}

void bossFight () {
  wprintf(L"\033[0;33m");
  wprintf(L"BOSS ARRIVAL!!\n");
  wprintf(L"\033[0m");
  bossIntro();
  while ((hp > 0) && (eHp > 0)) {
    playerTurn();
    if ((hp > 0) && (eHp > 0)) {
      bossTurn();
    }
  }
  if (hp <= 0) {
    gameNotOver = 0;
  } else if (eHp <= 0) {
    wprintf(L"\033[0;34m");
    wprintf(L"YOU WIN THE FIGHT!\n");
    wprintf(L"\033[0m");
    xp = xp + (map[player[0]][player[1]] * -200);
    wprintf(L"\033[0;33m");
    wprintf(L"%dXP GAINED\n", (map[player[0]][player[1]] * -200));
    wprintf(L"\033[0m");
    while (xp >= level*100) {
      levelUp();
    }
    bossDead();
  }
}

void playerTurn () {
  wprintf(L"\033[0;32m");
  wprintf(L"WHAT WILL YOU DO?\t");
  wprintf(L"\033[0m");
  wprintf(L"\033[0;36m");
  scanf(" %c",&action);
  wprintf(L"\033[0m");
  switch (action) {
    case 'a':
      wprintf(L"\033[0;34m");
      if (sword == 0) {
        wprintf(L"YOU SWING YOUR MIGHTY STICK!!\n");
        eHp = eHp - damage;
        wprintf(L"YOU DEAL %d DAMAGE!!\t\t\t\t", damage);
      } else if (sword == 1) {
        wprintf(L"YOU THRUST YOUR RUSTY SWORD!!\n");
        eHp = eHp - (damage + 5);
        wprintf(L"YOU DEAL %d DAMAGE!!\t\t\t\t", damage+5);
      } else if (sword == 2) {
        wprintf(L"YOU SLASH WITH GOBLINSLAYER!!\n");
        eHp = eHp - (damage+15);
        wprintf(L"YOU DEAL %d DAMAGE!!\t\t\t\t", damage+15);
      }
      if (map[player[0]][player[1]] > 0) {
        wprintf(L"\033[0;31m");
        wprintf(L"THE %s HAS %d HP LEFT\n",enemies[map[player[0]][player[1]]].name,eHp);
        wprintf(L"\033[0m");
      } else if (map[player[0]][player[1]] < 0) {
        wprintf(L"\033[0;35m");
        wprintf(L"%s HAS %d HP LEFT\n",bosses[abs(map[player[0]][player[1]]+4)].name,eHp);
        wprintf(L"\033[0m");
      }
      break;
    case 'q':
      wprintf(L"\033[0;34m");
      wprintf(L"YOU DONT HAVE POCKETS!!\n");
      wprintf(L"\033[0m");
      break;
    case 'w':
      wprintf(L"\033[0;34m");
      wprintf(L"YOU WAIT FOR AN OPENING!!\n");
      wprintf(L"\033[0m");
      break;
    case 's':
      wprintf(L"\033[0;34m");
      wprintf(L"YOU RUN AWAY LIKE A COWARD!!\n");
      wprintf(L"\033[0m");
      player[0] = oldMove[0];
      player[1] = oldMove[1];
      runAway = 1;
      break;
    default:
      wprintf(L"\033[0;34m");
      wprintf(L"YOU STUMBLE AND FALL!!\n");
      wprintf(L"\033[0m");
      break;
  }
}

void enemyTurn() {
  wprintf(L"\033[0;31m");
  wprintf(L"THE %s %s YOU!!\n",enemies[map[player[0]][player[1]]].name,enemies[map[player[0]][player[1]]].attack);
  hp = hp - eDamage;
  wprintf(L"IT DEALS %d damage!!\t\t\t\t",eDamage);
  wprintf(L"\033[0;34m");
  wprintf(L"YOU HAVE %d HP LEFT\n",hp);
  wprintf(L"\033[0m");
}

void bossTurn () {
  wprintf(L"\033[0;35m");
  wprintf(L"%s %s!!\n",bosses[abs(map[player[0]][player[1]]+4)].name,bosses[abs(map[player[0]][player[1]]+4)].attack);
  hp = hp - eDamage;
  wprintf(L"%s DEALS %d DAMAGE!!\t\t",bosses[abs(map[player[0]][player[1]]+4)].name,eDamage);
  wprintf(L"\033[0;34m");
  wprintf(L"YOU HAVE %d HP LEFT\n",hp);
  wprintf(L"\033[0m");
}

void bossIntro () {
  wprintf(L"\033[0;35m");
  wprintf(L"%s %s %s!!",bosses[abs(map[player[0]][player[1]]+4)].in1,bosses[abs(map[player[0]][player[1]]+4)].in2,bosses[abs(map[player[0]][player[1]]+4)].name);
  wprintf(L"\033[0m");
}

void bossDead() {
  wprintf(L"\033[0;35m");
  wprintf(L"%s!!\n",bosses[abs(map[player[0]][player[1]]+4)].out1);
  map[player[0]][player[1]] = map[player[0]][player[1]] * -1;
  wprintf(L"\033[0;34m");
  wprintf(L"%s\n%s OBTAINED!!\n",bosses[abs(map[player[0]][player[1]]+4)].out2,bosses[abs(map[player[0]][player[1]]+4)].swordName);
  wprintf(L"\033[0m");
  sword = bosses[abs(map[player[0]][player[1]]+4)].sword;
}
