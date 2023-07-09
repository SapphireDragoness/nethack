#ifndef NETHACK_H
#define NETHACK_H
#endif

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Level {
  char **tiles;
  int levelNumber;
  int numberOfRooms;
  struct Room **rooms;
  struct Monster **monsters;
  int numberOfMonsters;
} Level;

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Room {
  Position position;
  int height;
  int width;

  Position **doors;
  //Monster **monsters;
  //Item **items;
} Room;

typedef struct Player {
  Position position;
  int hp;
} Player;

int screenSetup();
Room **roomSetup();
char **saveLevelPositions();

Player *playerSetup();
Position *inputHandler(int input, Player *player);
int movePlayer(Position *position, Player *player, char **level);
int checkPosition(Position *position, Player *player, char **level);

Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);
int connectDoors(Position *doorOne, Position *doorTwo);