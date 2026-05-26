#include "battleship_io.h"

#include <stdio.h>

#include "battleship.h"

#define LAST_POS_BOARD (BOARD_SZ - 1)

const char COLUMNS[BOARD_SZ] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

// Auxiliar functions
void draw_div(char c, int len, const char* start, const char* end) {
    printf("\n%s", start);

    while (len > 0) {
        putchar(c);
        len--;
    }

    printf("%s\n", end);
}

void draw_columns_letters() {
    printf("   |");

    for (int i = 0; i < BOARD_SZ; i++) {
        printf("  %c  |", COLUMNS[i]);
    }
}

void draw_cell(char content, int x) {
    printf("  %c  ", content ? content : ' ');

    if (x != LAST_POS_BOARD) {
        putchar(' ');
    }
}

void draw_lines(char (*board)[BOARD_SZ]) {
    for (int y = 0; y < BOARD_SZ; y++) {
        printf("%2d |", (y + 1));

        for (int x = 0; x < BOARD_SZ; x++) {
            draw_cell(board[y][x], x);
        }

        putchar('|');

        if (y != LAST_POS_BOARD) {
            draw_div(' ', 59, "   |", "|");
        }
    }
}

// Output functions
void draw_board(char (*board)[BOARD_SZ]) {
    draw_columns_letters();
    draw_div('-', 59, "   +", "+");
    draw_lines(board);
    draw_div('-', 59, "   +", "+");
}
