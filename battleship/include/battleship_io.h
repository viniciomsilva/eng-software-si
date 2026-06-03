#ifndef BATTLESHIP_IO_H
#define BATTLESHIP_IO_H

#include "battleship.h"

#define EXIT_OPT 0
#define BUFFER_SZ 4

// Input functions
Coord read_coord();
void read_player_name(char* player_name);

// Output functions
void render(GameState*);

#endif  // BATTLESHIP_IO_H
