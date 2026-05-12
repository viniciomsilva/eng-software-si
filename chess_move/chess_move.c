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

const char COLUMNS[CB_LEN] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

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

    printf(" ");
    for (short k = 0; k < CB_LEN; k++) {
        printf("%6c", COLUMNS[k]);
    }
    printf("\n");
    for (short l = 0; l <= 50; l++) {
        printf("-");
    }
    printf("\n\n");
}

int main(void) {
    short opt = 0;
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

        switch (opt) {
            case 1:  // TODO: Move PA1
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 2:  // TODO: Move PA2
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 3:  // TODO: Move PA3
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 4:  // TODO: Move PA4
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 5:  // TODO: Move PA5
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 6:  // TODO: Move PA6
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 7:  // TODO: Move PA7
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 8:  // TODO: Move PA8
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 9:  // TODO: Move RK1
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 10:  // TODO: Move KN1
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 11:  // TODO: Move BI1
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 12:  // TODO: Move QEN
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 13:  // TODO: Move KNG
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 14:  // TODO: Move BI2
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 15:  // TODO: Move KN2
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 16:  // TODO: Move RK2
                printf("\nMOVENDO [ %s ] \n", pieces[opt - 1].label);
                break;

            case 99:
                printf("\nSAINDO...");
                opt = 99;
                break;

            default:
                printf("INVALIDA! PRESSIONE QUALQUER TECLA...");
                getchar();
                break;
        }

        getchar();  // TODO: Remove getchar() from here.
    } while (opt != 99);

    return 0;
}
