#include "nethack.h"

Room *createRoom(int y, int x, int height, int width) {
  Room *room;
  room = malloc(sizeof(Room));

  room->position.y = y;
  room->position.x = x;
  room->height = height;
  room->width = width;

  room->doors = malloc(sizeof(Position)*4);

  // north door
  room->doors[0] = malloc(sizeof(Position));
  room->doors[0]->x = rand() % (width - 2) + room->position.x + 1;
  room->doors[0]->y = room->position.y;

  // west door
  room->doors[1] = malloc(sizeof(Position));
  room->doors[1]->y = rand() % (height - 2) + room->position.y + 1;
  room->doors[1]->x = room->position.x;

  // south door
  room->doors[2] = malloc(sizeof(Position));
  room->doors[2]->x = rand() % (width - 2) + room->position.x + 1;
  room->doors[2]->y = room->position.y + room->height - 1;

  // east door
  room->doors[3] = malloc(sizeof(Position));
  room->doors[3]->y = rand() % (height - 2) + room->position.y + 1;
  room->doors[3]->x = room->position.x + width - 1;

  return room;
}

int drawRoom(Room *room) {
  int y;
  int x;

  for(x = room->position.x; x < room->position.x + room->width; x++) {
    mvprintw(room->position.y, x, "-");
    mvprintw(room->position.y + room->height - 1, x, "-");
  }

  for(y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
    mvprintw(y, room->position.x, "|");
    mvprintw(y, room->position.x + room->width - 1, "|");
    for(x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
      mvprintw(y, x, ".");
    }
  }

  mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
  mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
  mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
  mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

  return 1;
}

int connectDoors(Position *doorOne, Position *doorTwo) {
  Position temp;
  Position prev;
  int count = 0;

  temp.x = doorOne->x;
  temp.y = doorOne->y;

  prev = temp;

  while(1) {
    if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
      prev.x = temp.x;
      temp.x = temp.x - 1;
    }
    else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
      prev.x = temp.x;
      temp.x = temp.x + 1;
    }
    else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
      prev.y = temp.y;
      temp.y = temp.y - 1;
    }
    else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
      prev.y = temp.y;
      temp.y = temp.y + 1;
    }
    else {
      if(count == 0) {
        temp = prev;
        count++;
        continue;
      }
      else
        return 0;
    }

    mvprintw(temp.y, temp.x, "#");
    //getch();

  }

  return 1;
}

