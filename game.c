#include <stdio.h>

int startNewGame;
int gameNotOver = 1;
char playerMove;
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

void move ();
void cycle ();
void display();
void fight ();
void playerTurn ();
void enemyTurn ();
void gameOver();
void newGame();
void game ();

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
  gameNotOver = 0;
}

void move () {
  playerMove = ' ';
  printf("MOVE WHERE?\t");
  scanf(" %c", &playerMove); // couldnt figure out why scanf("%c") wasnt working, apparently scanf reads the enter key as an input and so gets skipped https://stackoverflow.com/questions/29775323/scanf-function-seems-to-be-skipped-in-c#:~:text=The%20problem%20is%20because%20of,second%20call%20to%20scanf()%20.&text=So%2C%20the%20newline%20character%20is,for%20input%20for%20that%20variable.
  switch (playerMove) { 
    case 'w':
      break;
    case 'a':
      break;
    case 's':
      break;
    case 'd':
      break;
    default:
      printf("%c IS NOT VALID, USE WASD!\n", playerMove);
      move();
  }
}
