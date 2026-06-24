/**
 * @file chess_move.c
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Implementation of state manipulation and control function, business
 * rules and game flow.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro.
 *
 */

#include "chess_move.h"

#include <stdio.h>
#include <string.h>

#include "chess_move_io.h"

#define DRTS_LEN 8      // Number of movement directions.
#define MAX_DISTANCE 5  // Maximum distance in squares that pieces can advance.

/**
 * @brief Cardinal direction for pieces movement on the chessboard.
 * These elements map the increments or decrements in the x, y, or both values
 * of the pieces, enabling movement in that direction.
 * Unlike a standard Cartesian plane, here the point (0,0) represents the
 * top-left of the matrix. Therefore, y increases downwards and x increases to
 * the right.
 *
 * @note The order of the elements must be preserved for the movements to
 * function correctly.
 *
 */
const Direction DRTS[DRTS_LEN] = {
    { .x =  0, .y = -1 }, /**< North. Decrements on the y-axis. */
    { .x =  0, .y =  1 }, /**< South. Increments on the y-axis. */
    { .x =  1, .y =  0 }, /**< East. Increments on the x-axis. */
    { .x = -1, .y =  0 }, /**< West. Decrements on the x-axis. */
    { .x =  1, .y = -1 }, /**< Northeast. Increments on the x-axis and decrements on the y-axis. */
    { .x = -1, .y = -1 }, /**< Northwest. Decrements on the both axes. */
    { .x =  1, .y =  1 }, /**< Southeast. Increments on both axes. */
    { .x = -1, .y =  1 }, /**< Southwest. Decrements on the x-axis and increments on the y-axis. */
};

/**
 * @brief Check if the x and y values are within th boundaries of the chessboard.
 *
 * @param x Column value (x-axis).
 * @param y Row value (y-axis).
 * @return short 1 for true and 0 for false.
 *
 */
short is_inside(short x, short y) {
    return x >= 0 && x <= CB_LIMIT && y >= 0 && y <= CB_LIMIT;
}

/**
 * @brief Check if a specific square on the chessboard is empty.
 *
 * @param stt Pointer to the game state.
 * @param x Column value (x-axis).
 * @param y Row value (y-axis).
 * @return short 1 for true and 0 for false.
 *
 */
short is_empty(State* stt, short x, short y) {
    return !stt->chessboard[y][x];
}

/**
 * @brief Check if all squares from the current piece's square up to the
 * destination square (distance multiplied by direction) on the chessboard are
 * empty.
 *
 * @param stt Pointer to the game state.
 * @param pi Piece index.
 * @param di Direction index.
 * @param dist Distance value.
 * @return short 1 for true and 0 for false.
 *
 */
short is_path_clear(State* stt, short pi, short di, short dist) {
    short x = stt->pieces[pi].x;
    short y = stt->pieces[pi].y;

    for (short i = 0; i < dist; i++) {
        x += DRTS[di].x;
        y += DRTS[di].y;

        if (!is_empty(stt, x, y)) return 0;
    }

    return 1;
}

/**
 * @brief Set a chessboard square as empty.
 *
 * @param stt Pointer to the game state.
 * @param x Column value (x-axis).
 * @param y Row value (y-axis).
 *
 */
void set_square_empty(State* stt, short x, short y) {
    stt->chessboard[y][x] = NULL;
}

/**
 * @brief Update the piece's square.
 *
 * @param pc Pointer to the piece.
 * @param x New x value for the piece.
 * @param y New y value for the piece.
 *
 */
void update_piece(Piece* pc, short x, short y) {
    pc->x = x;
    pc->y = y;
}

/**
 * @brief Validate business rules and whther values comply with chessboard
 * boundaries to move the piece
 *
 * @param stt Pointer to the game state.
 * @param pi Piece index.
 * @param di Direction index.
 * @param dist Distance value.
 * @return short 1 for true and 0 for false.
 *
 */
short move_piece(State* stt, short pi, short di, short dist) {
    // Is the movement distance is less than or equal to 0 or greater than the
    // maximum allowed, the move is invalid and returns 0.
    if (dist <= 0 || dist > MAX_DISTANCE) return 0;

    short x = stt->pieces[pi].x;
    short y = stt->pieces[pi].y;

    // Calculate the new square for the piece.
    // The new square is equal to the current square plus the direction
    // multiplied by the distance.
    short nx = x + DRTS[di].x * dist;
    short ny = y + DRTS[di].y * dist;

    // If the new square is inside the chessboard and the path to it is clear,
    // then: set the current square as empty, update de piece's square to the
    // new one, and returns 1.
    if (is_inside(nx, ny) && is_path_clear(stt, pi, di, dist)) {
        set_square_empty(stt, x, y);
        update_piece(&stt->pieces[pi], nx, ny);
        return 1;
    }

    return 0;
}

/**
 * @brief Calculate the knight's L-shaped move and validate if values comply
 * with chessboard boundaries.
 *
 * @param stt Pointer to the game state.
 * @param pi Piece index.
 * @param fdi Index of the first direction.
 * @param sdi Index of the second direction.
 * @return short 1 for true and 0 for false.
 *
 */
short move_knight(State* stt, short pi, short fdi, short sdi) {
    short x = stt->pieces[pi].x;
    short y = stt->pieces[pi].y;

    // Calculate the resulting square from the first direction.
    // The first move advances two squares vertically or horizontally.
    // Initially, the new square is equal to the current square plus the
    // direction multiplied by 2.
    // Since the movement is horizontal or vertical, one of the values, x or y,
    // will always remain the same.
    // Because for these specific directions, either x or y is 0.
    short nx = x + DRTS[fdi].x * 2;
    short ny = y + DRTS[fdi].y * 2;

    // If the first move was vertical, the second will be horizontal, so:
    // calculate the new value of x, which is the current x plus the direction's
    // x. Otherwise: calculate the new value of y, which is the current y plus
    // the direction's y.
    if (fdi == N || fdi == S) {
        nx = x + DRTS[sdi].x;
    } else {
        ny = y + DRTS[sdi].y;
    }

    // If the new square is inside the chessboard and is empty, then:
    // set the current square as empty, update the piece's square to the new
    // one, and return 1.
    if (is_inside(nx, ny) && is_empty(stt, nx, ny)) {
        set_square_empty(stt, x, y);
        update_piece(&stt->pieces[pi], nx, ny);
        return 1;
    }

    return 0;
}

void init_chessboard(State* stt) {
    for (short y = 0; y < CB_LEN; y++) {
        for (short x = 0; x < CB_LEN; x++) {
            set_square_empty(stt, x, y);
        }
    }
}

void init_pieces(State* stt) {
    short x = 0;
    short y = CB_LEN - 2;
    char* labels[PIECES_LEN] = {
        "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7", "PA8",  // second-to-last row
        "RK1", "KN1", "BI1", "QEN", "KNG", "BI2", "KN2", "RK2",  // last row
    };

    for (short i = 0; i < PIECES_LEN; i++) {
        strncpy(stt->pieces[i].label, labels[i], 3);
        stt->pieces[i].label[3] = '\0';
        stt->pieces[i].x = x;
        stt->pieces[i].y = y;

        if (x < CB_LIMIT) {  // continue on this row
            x++;
            continue;
        }

        y++;  // move to the next row
        x = 0;
    }
}

void refresh_chessboard(State* stt) {
    for (short i = 0; i < PIECES_LEN; i++) {
        short y = stt->pieces[i].y;
        short x = stt->pieces[i].x;

        stt->chessboard[y][x] = stt->pieces[i].label;
    }
}

short process_piece_turn(State* stt, short pi) {
    if (pi >= PA_START && pi <= PA_END) {
        return move_piece(stt, pi, N, 1);
    }

    short di, dist;

    if (pi == KN1 || pi == KN2) {
        short sdi;

        set_direction_x_or_y(&di);
        set_second_direction(&di, &sdi);

        return move_knight(stt, pi, di, sdi);
    }

    if (pi == RK1 || pi == RK2) {
        set_direction_x_or_y(&di);
    }

    if (pi == BI1 || pi == BI2) {
        set_direction_x_and_y(&di);
    }

    if (pi == QEN || pi == KNG) {
        set_direction_for_all(&di);
    }

    if (pi == KNG) {
        dist = 1;
    } else {
        set_distance(&dist);
    }

    return move_piece(stt, pi, di, dist);
}
