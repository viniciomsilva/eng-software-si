#include "battleship_io.h"

#include <stdio.h>

#include "battleship.h"

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
void draw_board(char (*draw_board)[BOARD_SIZE]) {
    printf("   |");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("  %c  |", COLUMNS[i]);
    }

    draw_line('-', 59, "   +", "+");

    for (int y = 0; y < BOARD_SIZE; y++) {
        printf("%2d |", (y + 1));

        for (int x = 0; x < BOARD_SIZE; x++) {
            char content = draw_board[y][x];

            printf("  %c  |", content ? content : ' ');
        }

        if (y != BOARD_SIZE - 1) {
            draw_line(' ', 59, "   |", "|");
        }
    }

    draw_line('-', 59, "   +", "+");
}
