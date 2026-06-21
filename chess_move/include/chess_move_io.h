/**
 * @file chess_move_io.h
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Function definitions related to I/O operations.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */

#ifndef CHESS_MOVE_IO_H
#define CHESS_MOVE_IO_H

#include "chess_move.h"

#define EXIT_GAME 99   // Game exit option.
#define BUFFER_SIZE 24 // Default buffer size for input data.

/**
 * @brief Display the chessboard matrix in the classic chessboard layout with
 * pieces placed on the cells.
 *
 * The function traverses the chessboard matrix and checks whether there is
 * content int each position. If a piece label is found in the current position,
 * the function prints it.
 *
 * @param stt Pointer to the application state.
 *
 */
void draw_chessboard(State* stt);

/**
 * @brief Display the menu containing the available pieces to move.
 *
 * The function traverses the pieces array within the state and prints a numeric
 * value associated with each piece label.
 *
 * @param stt Pointer to the application state.
 *
 */
void print_pieces_menu(State* stt);

/**
 * @brief Set the number of squares the piece will move.
 *
 * @param dist Pointer to the distance.
 */
void set_distance(short* dist);

/**
 * @brief Set the piece movement direction for vertical or horizontal movement.
 *
 * @param di Pointer to the direction index.
 *
 */
void set_direction_x_or_y(short* di);

/**
 * @brief Set the piece movement direction for diagonal movement.
 *
 * @param di Pointer to the direction index.
 *
 */
void set_direction_x_and_y(short* di);

/**
 * @brief Set the piece movement direction for all possible directions.
 *
 * @param di Pointer to the direction index.
 *
 */
void set_direction_for_all(short* di);

/**
 * @brief Set the second movement direction according to the first direction for
 * knight L-shaped moves.
 *
 * If the first direction is vertical, the second direction must be horizontal,
 * and vice versa.
 *
 * @param fdi Pointer to the first direction index.
 * @param sdi Pointer to the second direction index.
 *
 */
void set_second_direction(short* fdi, short* sdi);

#endif  // CHESS_MOVE_IO_H
