#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/game.h"
#include "src/utils.h"

#define BUFFER_SIZE 24
#define EXIT_GAME 98

// Handling functions / IO
void draw(State* stt);
void pieces_menu(State* stt);

void read_short(short *n);

int main(void) {
    short pi = 0;
    short di = 0;
    short mov = 0;
    short dist = 0;
    // char buffer[BUFFER_SIZE];
    State stt;

    init_chessboard(&stt);
    init_pieces(&stt);

    do {
        update_stt(&stt);

        clear();
        printf("MOVIMENTACAO DO XADREZ \n\n");
        draw(&stt);

        pieces_menu(&stt);
        read_short(&pi);
        pi--;

        if (pi >= 0 && pi < PIECES_LEN) printf("> PECA ESCOLHIDA:   %s \n", stt.pieces[pi].label);

        if (pi >= PA_START && pi <= PA_END) {  // Move Pawns
            mov = move_piece(&stt, pi, N, 1);
        } else if (pi == 8 || pi == 15) {  // Move Rooks
            printf("\n[ %d ] NORTE  [ %d ] SUL  [ %d ] LESTE  [ %d ] OESTE \n", N, S, E, W);
            do {
                printf("\n> ESCOLHA UMA DIRECAO: ");
                read_short(&di);
            } while (di != N && di != S && di != E && di != W);

            printf("> QUANTIDADE DE CASAS: ");
            read_short(&dist);

            mov = move_piece(&stt, pi, di, dist);
        } else if (pi == 9 || pi == 14) {  // Move Knights
            short sdi = 0;

            printf("\n[ %d ] NORTE  [ %d ] SUL  [ %d ] LESTE  [ %d ] OESTE \n", N, S, E, W);
            do {
                printf("\n> ESCOLHA UMA DIRECAO: ");
                read_short(&di);
            } while (di != N && di != S && di != E && di != W);

            if (di == N || di == S) {
                printf("\n[ %d ] LESTE  [ %d ] OESTE \n", E, W);
                do {
                    printf("\n> ESCOLHA UMA DIRECAO: ");
                    read_short(&sdi);
                } while (sdi != E && sdi != W);
            } else {
                printf("\n[ %d ] NORTE  [ %d ] SUL \n", N, S);
                do {
                    printf("\n> ESCOLHA UMA DIRECAO: ");
                    read_short(&sdi);
                } while (sdi != N && sdi != S);
            }

            mov = move_knight(&stt, pi, di, sdi);
        } else if (pi == 10 || pi == 13) {  // Move Bishops
            printf("\n[ %d ] NORDESTE  [ %d ] NOROESTE  [ %d ] SUDOESTE  [ %d ] SUDOESTE \n", NE, NW, SE, SW);

            do {
                printf("\n> ESCOLHA UMA DIRECAO: ");
                read_short(&di);
            } while (di != NE && di != NW && di != SE && di != SW);

            printf("> QUANTIDADE DE CASAS: ");
            read_short(&dist);

            mov = move_piece(&stt, pi, di, dist);
        } else if (pi == QEN) {  // Move Queen
            printf("\n[ %d ] NORTE     [ %d ] SUL       [ %d ] LESTE     [ %d ] OESTE ", N, S, E, W);
            printf("\n[ %d ] NORDESTE  [ %d ] NOROESTE  [ %d ] SUDOESTE  [ %d ] SUDOESTE \n", NE, NW, SE, SW);

            do {
                printf("\n> ESCOLHA UMA DIRECAO: ");
                read_short(&di);
            } while (di < N && di > SW);

            printf("> QUANTIDADE DE CASAS: ");
            read_short(&dist);

            mov = move_piece(&stt, pi, di, dist);
        } else if (pi == KNG) {  // Move King
            printf("\n[ %d ] NORTE     [ %d ] SUL       [ %d ] LESTE     [ %d ] OESTE ", N, S, E, W);
            printf("\n[ %d ] NORDESTE  [ %d ] NOROESTE  [ %d ] SUDOESTE  [ %d ] SUDOESTE \n", NE, NW, SE, SW);

            do {
                printf("\n> ESCOLHA UMA DIRECAO: ");
                read_short(&di);
            } while (di < N && di > SW);

            mov = move_piece(&stt, pi, di, 1);
        } else if (pi == EXIT_GAME) {
            mov = 1;
            printf("\nSAINDO...");
        } else {
            mov = 1;
            printf("\nOPCAO INVALIDA! PRESSIONE QUALQUER TECLA PARA CONTINUAR.");
            getchar();
        }

        if (!mov) {
            printf("\nMOVIMENTO INVALIDO. TENTE NOVAMENTE!");
            getchar();
        }
    } while (pi != EXIT_GAME);

    return 0;
}

// Handling functions / IO
void draw(State* stt) {
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

void pieces_menu(State* stt) {
    for (short i = 0; i < PIECES_LEN; i++) {
        printf("[ %2d ] %s  ", i + 1, stt->pieces[i].label);
        if (!((i + 1) % 4)) printf("\n");
    }
    printf("[ %d ] SAIR ", EXIT_GAME + 1);
    printf("\n\n> ESCOLHA UMA PECA: ");
}

void read_short(short *n) {
    char buffer[BUFFER_SIZE];

    fgets(buffer, sizeof(buffer), stdin);
    *n = (short)strtol(buffer, NULL, 10);
}
