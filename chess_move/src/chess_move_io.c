/**
 * @file chess_move_io.c
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Implementation of functions related to I/O operations.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro.
 *
 */

#include "chess_move_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"
#include "chess_move.h"

/**
 * @brief Set the piece movement direction index by validating whether the value
 * entered by the user fails within the range specified by the start and end
 * parameters. The value entered by the user is considered invalid if it is less
 * than start or greater than end.
 *
 * @param di Pointer to the direction index.
 * @param start Start value of the valid range.
 * @param end End value of the valid range.
 *
 */
void set_direction(short* di, short start, short end) {
    short index = 0;

    do {
        printf("\n> ESCOLHA UMA DIRECAO: ");

        index = (short)read_long(BUFFER_SIZE, "  DIGITE UM NUMERO: ");
    } while (index < start || index > end);

    *di = index;
}

void draw_chessboard(State* stt) {
    char* content;

    for (short y = 0; y < CB_LEN; y++) {
        printf("%d - ", CB_LEN - y);

        for (short x = 0; x < CB_LEN; x++) {
            content = stt->chessboard[y][x];

            printf(" %s ", (content) ? content : "   ");

            if (x < CB_LIMIT) {
                printf("|");
            }
        }

        printf("\n");
    }

    printf("      a     b     c     d     e     f     g     h  \n");
    printf("---------------------------------------------------\n\n");
}

void print_pieces_menu(State* stt) {
    short n;

    for (short i = 0; i < PIECES_LEN; i++) {
        n = i + 1;

        printf("[ %2d ] %s  ", n, stt->pieces[i].label);

        if (!(n % 4)) {
            printf("\n");
        }
    }

    printf("[ %d ] SAIR ", EXIT_GAME);
    printf("\n\n> ESCOLHA UMA PECA: ");
}

void set_distance(short* dist) {
    printf("> QUANTIDADE DE CASAS: ");

    *dist = (short)read_long(BUFFER_SIZE, "  DIGITE UM NUMERO: ");
}

void set_direction_x_or_y(short* di) {
    // Display the possible directions for vertical or horizontal movement.
    printf("\n[ %d ] NORTE  [ %d ] SUL  [ %d ] LESTE  [ %d ] OESTE \n", N, S, E, W);

    // The valid direction range goes from north to west.
    set_direction(di, N, W);
}

void set_direction_x_and_y(short* di) {
    // Display the possible directions for diagonal movement.
    printf("\n[ %d ] NORDESTE  [ %d ] NOROESTE  [ %d ] SUDESTE  [ %d ] SUDOESTE \n", NE, NW, SE, SW);

    // The valid direction range goes from northeast to southwest.
    set_direction(di, NE, SW);
}

void set_direction_for_all(short* di) {
    // Display the possible directions for movement along any axis.
    printf("\n[ %d ] NORTE     [ %d ] SUL       [ %d ] LESTE    [ %d ] OESTE ", N, S, E, W);
    printf("\n[ %d ] NORDESTE  [ %d ] NOROESTE  [ %d ] SUDESTE  [ %d ] SUDOESTE \n", NE, NW, SE, SW);

    // The valid directio range goes from north to southwest.
    set_direction(di, N, SW);
}

void set_second_direction(short* fdi, short* sdi) {
    // If the first direction is north or south (vertical axis),
    // the second direction must be restricted to east or west (horizontal axis).
    // Otherwise, the opposite logic applies.
    if (*fdi == N || *fdi == S) {
        printf("\n[ %d ] LESTE  [ %d ] OESTE \n", E, W);
        set_direction(sdi, E, W);
    } else {
        printf("\n[ %d ] NORTE  [ %d ] SUL \n", N, S);
        set_direction(sdi, N, S);
    }
}
