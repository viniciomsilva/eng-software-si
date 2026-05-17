#ifndef IO_H
#define IO_H

#include "game.h"

#define BUFFER_SIZE 24
#define EXIT_GAME 98

// Output functions
void draw_chessboard(State* stt);
void print_pieces_menu(State* stt);

// Input functions
void read_short(short* n);
void set_distance(short* dist);
void set_direction_x_or_y(short* di);
void set_direction_x_and_y(short* di);
void set_direction_for_all(short* di);
void set_second_direction(short* fdi, short* sdi);

#endif  // IO_H
