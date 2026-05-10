#include <stdio.h>

#define CB_LEN 8

const char COLUMNS[CB_LEN] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

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

    // 2 - PA1 | PA2 | PA3 | PA4 | PA5 | PA6 | PA7 | PA8
    cb[6][0] = "PA1";
    cb[6][1] = "PA2";
    cb[6][2] = "PA3";
    cb[6][3] = "PA4";
    cb[6][4] = "PA5";
    cb[6][5] = "PA6";
    cb[6][6] = "PA7";
    cb[6][7] = "PA8";

    // 1 - RK1 | KN1 | BI1 | QEN | KNG | BI2 | KN2 | RK2
    cb[7][0] = "RK1";
    cb[7][1] = "KN1";
    cb[7][2] = "BI1";
    cb[7][3] = "QEN";
    cb[7][4] = "KNG";
    cb[7][5] = "BI2";
    cb[7][6] = "KN2";
    cb[7][7] = "RK2";

    chessboard(cb);

    return 0;
}
