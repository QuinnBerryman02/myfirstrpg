#include <stdio.h>

int startNewGame;
int gameNotOver = 1;
char playerMove;
int player[2] = {7,3};
int hp = 100;
int damage = 10;
int level = 1;
int xp = 0;
int map[9][7] = { // Looked up how to declare a matrix at https://beginnersbook.com/2014/01/2d-arrays-in-c-example/
  {0,0,0,0,0,0,0},
  {0,9,8,7,8,9,0},
  {0,8,7,6,7,8,0},
  {0,7,6,5,6,7,0},
  {0,6,5,4,5,6,0},
  {0,5,4,3,4,5,0},
  {0,4,3,2,3,4,0},
  {0,3,2,1,2,3,0},
  {0,0,0,0,0,0,0}

};

void move ();       //done
void cycle ();      //work in progress
void display();     //done
void fight ();      //not done
void playerTurn (); //not done
void enemyTurn ();  //not done
void gameOver();    //not done
void newGame();     //done
void game ();       //done
void levelUp();     //not done

int main () {
  newGame();
  return 0;
}

void newGame () {
  printf("NEW GAME?\t");
  scanf("%d",&startNewGame);
  if (startNewGame == 0) {
    printf("GOODBYE!");
  } else {
    printf("GAME START!\n");
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
  printf("GAME OVER!\n");
  newGame();
}

void cycle () {
  move();
  display();
//  gameNotOver = 0;
}

void move () {
  playerMove = ' ';
  printf("MOVE WHERE?\t");
  scanf(" %c", &playerMove); // couldnt figure out why scanf("%c") wasnt working, apparently scanf reads the enter key as an input and so gets skipped https://stackoverflow.com/questions/29775323/scanf-function-seems-to-be-skipped-in-c#:~:text=The%20problem%20is%20because%20of,second%20call%20to%20scanf()%20.&text=So%2C%20the%20newline%20character%20is,for%20input%20for%20that%20variable.
  switch (playerMove) {
    case 'w':
      if (map[player[0]-1][player[1]] == 0) {
        printf("%c IS NOT VALID, USE WASD!\n", playerMove);
        move();
      } else {
        player[0] = player[0] - 1;
      }
      break;
    case 'a':
    if (map[player[0]][player[1]-1] == 0) {
      printf("%c IS NOT VALID, USE WASD!\n", playerMove);
      move();
    } else {
      player[1] = player[1] - 1;
    }
      break;
    case 's':
    if (map[player[0]+1][player[1]] == 0) {
      printf("%c IS NOT VALID, USE WASD!\n", playerMove);
      move();
    } else {
      player[0] = player[0] + 1;
    }
      break;
    case 'd':
    if (map[player[0]][player[1]+1] == 0) {
      printf("%c IS NOT VALID, USE WASD!\n", playerMove);
      move();
    } else {
      player[1] = player[1] + 1;
    }
      break;
    default:
      printf("%c IS NOT VALID, USE WASD!\n", playerMove);
      move();
  }
}

void display () {
  int i;
  int j;
  for (i=0;i<9;i++) {
    for (j=0;j<7;j++) {
      if ((i == player[0]) && (j == player[1])) {
        printf("@");
      } else if ((map[i][j] == 0) && ((i == 0) || (i == 8)) && ((j != 0) && (j != 6))) {
        printf("-");
      } else if ((map[i][j] == 0) && ((j == 0) || (j == 6)) && ((i != 0) && (i != 8))) {
        printf("|");
        if (j==6) {
          printf("\n");
        }
      } else if ((map[i][j] == 0) && ((i == 0) || (i == 8)) && ((j == 0) || (j == 6))) {
        printf("Q");
        if (j==6) {
          printf("\n");
        }
      } else {
        printf(" ");
      }
    }
  }
}
