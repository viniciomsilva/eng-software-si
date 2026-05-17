#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

// Auxiliar function
void set_direction(short* di, short start, short end) {
    do {
        printf("\n> ESCOLHA UMA DIRECAO: ");
        read_short(di);
    } while (*di < start || *di > end);
}

// Output functions
void draw_chessboard(State* stt) {
    for (short y = 0; y < CB_LEN; y++) {
        printf("%d - ", CB_LEN - y);
        for (short x = 0; x < CB_LEN; x++) {
            char* content = stt->chessboard[y][x];
            printf(" %s ", (content) ? content : "   ");
            if (x < CB_LEN - 1) printf("|");
        }
        printf("\n");
    }
    printf("      a     b     c     d     e     f     g     h  \n");
    printf("---------------------------------------------------\n\n");
}

void print_pieces_menu(State* stt) {
    for (short i = 0; i < PIECES_LEN; i++) {
        printf("[ %2d ] %s  ", i + 1, stt->pieces[i].label);
        if (!((i + 1) % 4)) printf("\n");
    }
    printf("[ %d ] SAIR ", EXIT_GAME + 1);
    printf("\n\n> ESCOLHA UMA PECA: ");
}

// Input functions
void read_short(short* n) {
    char buffer[BUFFER_SIZE];
    char* endptr;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\n') {
            printf("DIGITE APENAS NUMEROS...");
            continue;
        }

        long value = strtol(buffer, &endptr, 10);

        if (*endptr != '\0') {
            printf("DIGITE APENAS NUMEROS...");
            continue;
        }

        *n = (short)value;
        break;
    }
}

void set_distance(short* dist) {
    printf("> QUANTIDADE DE CASAS: ");
    read_short(dist);
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
