#include "nethack.h"

Player *playerSetup() {
  Player *player;
  player = malloc(sizeof(Player));

  player->position.x = 14;
  player->position.y = 14;
  player->hp = 10;

  mvprintw(player->position.y, player->position.x, "@");
  move(player->position.y, player->position.x);
  return player;
}

Position *inputHandler(int input, Player *player) {
  Position *position;
  position = malloc(sizeof(Position));
  switch(input) {
    case 'w':
    case 'W':
      position->y = player->position.y-1;
      position->x = player->position.x;
      break;

    case 'a':
    case 'A':
      position->y = player->position.y;
      position->x = player->position.x-1;
      break;

    case 's':
    case 'S':
      position->y = player->position.y+1;
      position->x = player->position.x;
      break;

    case 'd':
    case 'D':
      position->y = player->position.y;
      position->x = player->position.x+1;
      break;

    default:
      break;
  }
  return position;
}

int checkPosition(Position *position, Player *player, char **level) {
  int space;
  switch(mvinch(position->y, position->x)) {
    case '+':
    case '#':
    case '.':
      movePlayer(position, player, level);
      break;
    default:
      move(player->position.y, player->position.x);
      break;
  }
}

int movePlayer(Position *position, Player *player, char **level) {
  char buffer[8];

  sprintf(buffer, "%c", level[player->position.y][player->position.x]);

  mvprintw(player->position.y, player->position.x, buffer);

  player->position.y = position->y;
  player->position.x = position->x;

  mvprintw(player->position.y, player->position.x, "@");
  move(player->position.y, player->position.x);
}