#include "battleship_io.h"

#include <stdio.h>

#include "battleship.h"

const char COLUMNS[BOARD_SZ] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

// Auxiliar functions
void draw_line(char c, int len, const char* start, const char* end) {
    printf("\n%s", start);

    while (len > 0) {
        putchar(c);
        len--;
    }

    printf("%s\n", end);
}

// Output functions
void draw_board(char (*draw_board)[BOARD_SZ]) {
    printf("   |");

    for (int i = 0; i < BOARD_SZ; i++) {
        printf("  %c  |", COLUMNS[i]);
    }

    draw_line('-', 59, "   +", "+");

    for (int y = 0; y < BOARD_SZ; y++) {
        printf("%2d |", (y + 1));

        for (int x = 0; x < BOARD_SZ; x++) {
            char content = draw_board[y][x];

            printf("  %c  |", content ? content : ' ');
        }

        if (y != BOARD_SZ - 1) {
            draw_line(' ', 59, "   |", "|");
        }
    }

    draw_line('-', 59, "   +", "+");
}
