#ifndef BATTLESHIP_IO_H
#define BATTLESHIP_IO_H

#include "battleship.h"

#define EXIT_OPT 0

// Input functions
void read_player_name(char* player_name);

// Output functions
void render(GameState*);

#endif  // BATTLESHIP_IO_H
