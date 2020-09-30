#include <stdio.h>

int startNewGame;

char move ();
void cycle ();
void display();
void fight ();
void playerTurn ();
void enemyTurn ();
void gameOver();
void newGame();

int main () {
  newGame();
  return 0;
}

void newGame () {
  printf("Would you like to start a new game?\t");
  scanf("%d",&startNewGame);
  if (startNewGame == 0) {
    printf("Goodbye");
  } else {
    printf("Game start!");
  }
}
