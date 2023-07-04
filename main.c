#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>

typedef struct Player {
  int x;
  int y;
  int hp;
} Player;

int screenSetup();
int mapSetup();
Player *playerSetup();
int inputHandler(int input, Player *player);
int movePlayer(int y, int x, Player *player);
int checkPosition(int newY, int newX, Player *player);

int main() {
  Player *player;
  int c;

  screenSetup();
  mapSetup();

  player = playerSetup();
  while ((c = getch()) != 'q') {
    inputHandler(c, player);
  }
  
  endwin();

  return 0;
}

int screenSetup() {
  initscr();
  noecho();
  refresh();

  return 0;
}

int mapSetup() {
  mvprintw(13, 13, "--------");
  mvprintw(14, 13, "|......|");
  mvprintw(15, 13, "|......|");
  mvprintw(16, 13, "|......|");
  mvprintw(17, 13, "|......|");
  mvprintw(18, 13, "--------");

  mvprintw(2, 40, "--------");
  mvprintw(3, 40, "|......|");
  mvprintw(4, 40, "|......|");
  mvprintw(5, 40, "|......|");
  mvprintw(6, 40, "|......|");
  mvprintw(7, 40, "--------");
}

Player *playerSetup() {
  Player *player;
  player = malloc(sizeof(Player));

  player->x = 14;
  player->y = 14;
  player->hp = 10;

  movePlayer(14, 14, player);

  return player;
}

int inputHandler(int input, Player *player) {
  int newY, newX;
  switch(input) {
    case 'w':
    case 'W':
      newY = player->y-1;
      newX = player->x;
      break;

    case 'a':
    case 'A':
      newY = player->y;
      newX = player->x-1;
      break;

    case 's':
    case 'S':
      newY = player->y+1;
      newX = player->x;
      break;

    case 'd':
    case 'D':
      newY = player->y;
      newX = player->x+1;
      break;

    default:
      break;
  }
  checkPosition(newY, newX, player);
}

int checkPosition(int newY, int newX, Player *player) {
  int space;
  switch(mvinch(newY, newX)) {
    case '.':
      movePlayer(newY, newX, player);
      break;
    default:
      move(player->y, player->x);
      break;
  }
}

int movePlayer(int y, int x, Player *player) {
  mvprintw(player->y, player->x, ".");

  player->y = y;
  player->x = x;

  mvprintw(player->y, player->x, "@");
  move(player->y, player->x);
}