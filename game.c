#include <stdio.h>

int startNewGame;
int gameNotOver = 1;

char move ();
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
    printf("GOODBYE");
  } else {
    printf("GAME START\n");
    game();
  }
}

void game () {
  while (gameNotOver) {
    cycle();
  }
  printf("GAME OVER\n");
  newGame();
}

void cycle () {
  gameNotOver = 0;
}
