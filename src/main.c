#include "nethack.h"

int main() {
  Player *player;
  int c;
  Position *position;

  Level *level;

  screenSetup();
  level = createLevel();
  player = playerSetup();

  while ((c = getch()) != 'q') {
    position = inputHandler(c, player);
    checkPosition(position, player, level->tiles);
  }
  
  endwin();

  return 0;
}

int screenSetup() {
  srand(time(NULL));
  initscr();
  noecho();
  refresh();

  return 0;
}


