#include "chess_move_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"
#include "chess_move.h"

// Auxiliar function
void set_direction(short* di, short start, short end) {
    do {
        printf("\n> ESCOLHA UMA DIRECAO: ");

        *di = (short)read_long(BUFFER_SIZE, "  DIGITE UM NUMERO: ");
    } while (*di < start || *di > end);
}

// Output functions
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

// Input functions
void set_distance(short* dist) {
    printf("> QUANTIDADE DE CASAS: ");

    *dist = (short)read_long(BUFFER_SIZE, "  DIGITE UM NUMERO: ");
}

void set_direction_x_or_y(short* di) {
    printf("\n[ %d ] NORTE  [ %d ] SUL  [ %d ] LESTE  [ %d ] OESTE \n", N, S, E, W);
    set_direction(di, N, W);
}

void set_direction_x_and_y(short* di) {
    printf("\n[ %d ] NORDESTE  [ %d ] NOROESTE  [ %d ] SUDESTE  [ %d ] SUDOESTE \n", NE, NW, SE, SW);
    set_direction(di, NE, SW);
}

void set_direction_for_all(short* di) {
    printf("\n[ %d ] NORTE     [ %d ] SUL       [ %d ] LESTE    [ %d ] OESTE ", N, S, E, W);
    printf("\n[ %d ] NORDESTE  [ %d ] NOROESTE  [ %d ] SUDESTE  [ %d ] SUDOESTE \n", NE, NW, SE, SW);
    set_direction(di, N, SW);
}

void set_second_direction(short* fdi, short* sdi) {
    if (*fdi == N || *fdi == S) {
        printf("\n[ %d ] LESTE  [ %d ] OESTE \n", E, W);
        set_direction(sdi, E, W);
    } else {
        printf("\n[ %d ] NORTE  [ %d ] SUL \n", N, S);
        set_direction(sdi, N, S);
    }
}
