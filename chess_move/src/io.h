#ifndef IO_H
#define IO_H

#include "game.h"

#define EXIT_GAME 99
#define BUFFER_SIZE 24

// Output functions
void draw_chessboard(State* stt);
void print_pieces_menu(State* stt);

// Input functions
long input_long();
void set_distance(short* dist);
void set_direction_x_or_y(short* di);
void set_direction_x_and_y(short* di);
void set_direction_for_all(short* di);
void set_second_direction(short* fdi, short* sdi);

#endif  // IO_H
