/**
 * @file battleship_io.h
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Input and Output handler definitions for the Battleship game
 * interface.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */
#ifndef BATTLESHIP_IO_H
#define BATTLESHIP_IO_H

#include "battleship.h"

#define EXIT_OPTION 0  // Game exit option.
#define BUFFER_SIZE 4  // Default buffer size for input data.

/**
 * @brief Reads and sets the player's name.
 *
 * @param player_name Pointer to the buffer where the player's name will be
 * stored.
 */
void io_read_player_name(char* player_name);

/**
 * @brief Translates an attack coordinate iput string into integer values.
 *
 * Example: char buffer[] = "C10"
 *
 * - coord.x = 2 ('C' corresponds to matrix column 2).
 *
 * - coord.y = 9 ("10" corresponds to matrix row 9).
 *
 * For the input "C10", the expected return value is { x = 2, y = 9 }.
 *
 * @return Coord A structure containing the x and y coordinates values.
 */
Coord io_read_coord(void);

/**
 * @brief Renders the current game state in the terminal.
 *
 * @param state Pointer to the current game state structure.
 */
void io_render(GameState* state);

#endif  // BATTLESHIP_IO_H
