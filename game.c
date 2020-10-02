#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

char startNewGame;
char action;
int gameNotOver = 1;
char playerMove;
int player[2] = {7,3};
int hp = 100;
int damage = 10;
int level = 1;
int xp = 0;
int eHp;
int eDamage;
int map[9][7] = { // Looked up how to declare a matrix at https://beginnersbook.com/2014/01/2d-arrays-in-c-example/
  {-1,-1,-1,-1,-1,-1,-1},
  {-1,+9,+8,+7,+8,+9,-1},
  {-1,+8,+7,+6,+7,+8,-1},
  {-1,+7,+6,+5,+6,+7,-1},
  {-1,+6,+5,+4,+5,+6,-1},
  {-1,+5,+4,+3,+4,+5,-1},
  {-1,+4,+3,+1,+3,+4,-1},
  {-1,+2,+1,+1,+1,+2,-1},
  {-1,-1,-1,-1,-1,-1,-1}
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

int main () {
  system("MODE 56,37");
  _setmode(_fileno(stdout), 0x00020000);
  wprintf(L"CONFIRM:\n\ty = yes\n\tn = no\nMOVEMENT:\n\tw = up\n\ta = left\n\ts = down\n\td = right\nACTIONS:\n\ta = attack\n\ti = inventory\n\tw = wait\n");
  newGame();
  return 0;
}

void newGame () {
  wprintf(L"NEW GAME?\t");
  scanf(" %c",&startNewGame);
  if (startNewGame == 'n') {
    wprintf(L"GOODBYE!");
  } else if (startNewGame == 'd') {
    wprintf(L"DEV MODE!\n");
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
  wprintf(L"GAME OVER!\nYOU REACHED LVL %d\n",level);
  newGame();
}

void cycle () {
  display();
  move();
  display();
  fight();
//  gameNotOver = 0;
}

void move () {
  playerMove = ' ';
  wprintf(L"MOVE WHERE?\t");
  scanf(" %c", &playerMove); // couldnt figure out why scanf("%c") wasnt working, apparently scanf reads the enter key as an input and so gets skipped https://stackoverflow.com/questions/29775323/scanf-function-seems-to-be-skipped-in-c#:~:text=The%20problem%20is%20because%20of,second%20call%20to%20scanf()%20.&text=So%2C%20the%20newline%20character%20is,for%20input%20for%20that%20variable.
  switch (playerMove) {
    case 'w':
      if (map[player[0]-1][player[1]] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[0] = player[0] - 1;
      }
      break;
    case 'a':
      if (map[player[0]][player[1]-1] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[1] = player[1] - 1;
      }
      break;
    case 's':
      if (map[player[0]+1][player[1]] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[0] = player[0] + 1;
      }
      break;
    case 'd':
      if (map[player[0]][player[1]+1] == -1) {
        wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[1] = player[1] + 1;
      }
      break;
    case 'c':
      wprintf(L"YOU CAMP FOR THE NIGHT\n");
      break;
    default:
      wprintf(L"%c IS NOT VALID, USE WASD!\n", playerMove);
      move();
      break;
  }
}

void display () {
  int i;
  int j;
  int k;
  for (i=0;i<9;i++) {
    for (k=0;k<4;k++) {
      for (j=0;j<7;j++) {
        if ((i == player[0]) && (j == player[1])) {
          if (k%2==0) {
            wprintf(L"████████");
          } else {
            wprintf(L"██    ██");
          }
        } else if (map[i][j] == 0) {
          if (k%2==0) {
            wprintf(L"██  ██  ");
          } else {
            wprintf(L"  ██  ██");
          }
        } else if (map[i][j] < 0) {
          wprintf(L"████████");
        } else if (map[i][j] > 0) {
          wprintf(L"        ");
        }

      }
      wprintf(L"\n");
    }
  }
}

void levelUp () {
  hp = hp + 10;
  damage++;
  level++;
  wprintf(L"YOU HAVE REACHED LEVEL %d\n", level);
}

void fight () {
  eHp = (map[player[0]][player[1]] * 75);
  eDamage = (map[player[0]][player[1]] * 10);
  hp = 100 + ((level-1) * 10);
  damage = 10 + ((level-1) * 1);
  wprintf(L"ENEMY ARRIVAL!!\nA LVL %d IMP HAS COME TO MURDER YOU!!\n", map[player[0]][player[1]]);
  while ((hp > 0) && (eHp > 0)) {
    playerTurn();
    if ((hp > 0) && (eHp > 0)) {
      enemyTurn();
    }
  }
  if (hp <= 0) {
    gameNotOver = 0;
  } else if (eHp <= 0) {
    wprintf(L"YOU WIN THE FIGHT!\n");
    xp = xp + (map[player[0]][player[1]] * 50);
    wprintf(L"%dXP GAINED\n", (map[player[0]][player[1]] * 50));
    while (xp >= level*100) {
      levelUp();
    }
  }
}

void playerTurn () {
  wprintf(L"WHAT WILL YOU DO?\t");
  scanf(" %c",&action);
  switch (action) {
    case 'a':
      wprintf(L"YOU SWING YOUR MIGHTY STICK!!\n");
      eHp = eHp - damage;
      wprintf(L"YOU DEAL %d damage!!\t the imp has %d hp left\n",damage,eHp);
      break;
    case 'i':
      wprintf(L"YOU DONT HAVE POCKETS!!\n");
      break;
    case 'w':
      wprintf(L"YOU WAIT FOR AN OPENING!!\n");
      break;
    default:
      wprintf(L"YOU STUMBLE AND FALL!!\n");
      break;
  }
}

void enemyTurn() {
  wprintf(L"THE IMP BITES YOU!!\n");
  hp = hp - eDamage;
  wprintf(L"IT DEALS %d damage!!\t you have %d hp left\n",eDamage,hp);
}
