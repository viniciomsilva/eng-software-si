#include <stdio.h>

#define PIECES_LEN 16
#define CB_LEN 8

const char COLUMNS[CB_LEN] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

typedef struct Piece {
    short x;
    short y;
    char label[4];
} Piece;

void start(char* cb[CB_LEN][CB_LEN], Piece* pcs) {
    for (short i = 0; i < PIECES_LEN; i++) cb[pcs[i].y][pcs[i].x] = pcs[i].label;
}

void chessboard(char* cb[CB_LEN][CB_LEN]) {
    /*
        Example of how the chessboard will be displayed.

        8 -     |     |     |     |     |     |     |
        ...
        2 - PA1 | PA2 | PA3 | PA4 | PA5 | PA6 | PA7 | PA8
        1 - RK1 | KN1 | BI1 | QEN | KNG | BI2 | KN2 | RK2
             a     b     c     d     e     f     g     h
     */

    for (short i = 0; i < CB_LEN; i++) {  // lines
        printf("%d - ", CB_LEN - i);

        for (short j = 0; j < CB_LEN; j++) {  // columns
            printf(" %s ", (cb[i][j]) ? cb[i][j] : "   ");
            if (j < CB_LEN - 1) printf("|");
        }
        printf("\n");
    }

    printf(" ");
    for (short k = 0; k < CB_LEN; k++) printf("%6c", COLUMNS[k]);
    printf("\n");
}

int main(void) {
    char* cb[CB_LEN][CB_LEN] = {NULL};
    Piece pieces[PIECES_LEN] = {
        {.label = "PA1", .x = 0, .y = 6}, {.label = "PA2", .x = 1, .y = 6}, {.label = "PA3", .x = 2, .y = 6},
        {.label = "PA4", .x = 3, .y = 6}, {.label = "PA5", .x = 4, .y = 6}, {.label = "PA6", .x = 5, .y = 6},
        {.label = "PA7", .x = 6, .y = 6}, {.label = "PA8", .x = 7, .y = 6}, {.label = "RK1", .x = 0, .y = 7},
        {.label = "KN1", .x = 1, .y = 7}, {.label = "BI1", .x = 2, .y = 7}, {.label = "QEN", .x = 3, .y = 7},
        {.label = "KNG", .x = 4, .y = 7}, {.label = "BI2", .x = 5, .y = 7}, {.label = "KN2", .x = 6, .y = 7},
        {.label = "RK2", .x = 7, .y = 7},
    };

    start(cb, pieces);
    chessboard(cb);

    return 0;
}
