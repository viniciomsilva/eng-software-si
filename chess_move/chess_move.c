#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 24
#define PIECES_LEN 16
#define CB_LEN 8

#ifdef _WIN32
#define CLS_CMD "cls"
#else
#define CLS_CMD "clear"
#endif

typedef struct Piece {
    short x;
    short y;
    char label[4];
} Piece;

void clear(void) { system(CLS_CMD); }

void update_cb(char* cb[CB_LEN][CB_LEN], Piece* pcs) {
    for (short i = 0; i < PIECES_LEN; i++) {
        cb[pcs[i].y][pcs[i].x] = pcs[i].label;
    }
}

void display_cb(char* cb[CB_LEN][CB_LEN]) {
    for (short i = 0; i < CB_LEN; i++) {  // lines
        printf("%d - ", CB_LEN - i);

        for (short j = 0; j < CB_LEN; j++) {  // columns
            printf(" %s ", (cb[i][j]) ? cb[i][j] : "   ");
            if (j < CB_LEN - 1) printf("|");
        }
        printf("\n");
    }
    printf("      a     b     c     d     e     f     g     h  \n");
    printf("---------------------------------------------------\n\n");
}

short move_pawn(char* cb[CB_LEN][CB_LEN], Piece* pawn) {
    // Moves only one square forward along the Y-axis.
    // It cannot move backward.
    // It cannot jump over other pieces.
    short ny = pawn->y - 1;

    if (ny < 0) return 0;           // Verifica se está no limite do tabuleiro.
    if (cb[ny][pawn->x]) return 0;  // Verifica se o destino está vazio.

    cb[pawn->y][pawn->x] = NULL;
    pawn->y = ny;

    return 1;
};

int main(void) {
    short opt = 0;
    short mov = 0;
    char buffer[BUFFER_SIZE];
    char* cb[CB_LEN][CB_LEN] = {NULL};
    Piece pieces[PIECES_LEN] = {
        {.label = "PA1", .x = 0, .y = 6},  // Pawn
        {.label = "PA2", .x = 1, .y = 6},  // Pawn
        {.label = "PA3", .x = 2, .y = 6},  // Pawn
        {.label = "PA4", .x = 3, .y = 6},  // Pawn
        {.label = "PA5", .x = 4, .y = 6},  // Pawn
        {.label = "PA6", .x = 5, .y = 6},  // Pawn
        {.label = "PA7", .x = 6, .y = 6},  // Pawn
        {.label = "PA8", .x = 7, .y = 6},  // Pawn
        {.label = "RK1", .x = 0, .y = 7},  // Rook
        {.label = "KN1", .x = 1, .y = 7},  // Knight
        {.label = "BI1", .x = 2, .y = 7},  // Bishop
        {.label = "QEN", .x = 3, .y = 7},  // Queen
        {.label = "KNG", .x = 4, .y = 7},  // King
        {.label = "BI2", .x = 5, .y = 7},  // Bishop
        {.label = "KN2", .x = 6, .y = 7},  // Knight
        {.label = "RK2", .x = 7, .y = 7},  // Rook
    };

    do {
        update_cb(cb, pieces);

        clear();
        printf("MOVIMENTACAO DO XADREZ \n\n");
        display_cb(cb);

        // main menu
        for (short i = 0; i < PIECES_LEN; i++) {
            printf("[ %2d ] %s  ", i + 1, pieces[i].label);
            if (!((i + 1) % 4)) printf("\n");
        }
        printf("[ 99 ] SAIR ");

        printf("\n\n> ESCOLHA UMA OPCAO: ");
        fgets(buffer, sizeof(buffer), stdin);
        opt = (short)strtol(buffer, NULL, 10);

        if (opt >= 1 && opt <= 8) {  // Move Pawns
            mov = move_pawn(cb, &pieces[opt - 1]);
        } else if (opt == 9 || opt == 16) {  // TODO: Move Rooks
            /* code */
        } else if (opt == 10 || opt == 15) {  // TODO: Move Rights
            /* code */
        } else if (opt == 11 || opt == 14) {  // TODO: Move Bishops
            /* code */
        } else if (opt == 12) {  // TODO: Move Queen
            /* code */
        } else if (opt == 13) {  // TODO: Move King
            /* code */
        } else if (opt == 99) {
            printf("\nSAINDO...");
        } else {
            mov = 1;
            printf("OPCAO INVALIDA! PRESSIONE QUALQUER TECLA PARA CONTINUAR.");
            getchar();
        }

        if (!mov) {
            printf("MOVIMENTO INVALIDO! TENTE NOVAMENTE!");
            getchar();
        }
    } while (opt != 99);

    return 0;
}
