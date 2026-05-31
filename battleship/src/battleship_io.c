#include "battleship_io.h"

#include <stdio.h>

#include "../../utils/utils.h"
#include "battleship.h"

#define LAST_POS_BOARD (BOARD_SZ - 1)

const char COLUMNS[BOARD_SZ] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
};

// Auxiliar functions
void draw_div(char c, int len, const char* start, const char* end) {
    printf("%s", start);

    while (len > 0) {
        putchar(c);
        len--;
    }

    printf("%s", end);
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

void print_player_data(const char* player_name, int score) {
    printf("  > %s %dPT", player_name, score);
}

void print_proj_opt(int opt, const char* label, int ammunition) {
    printf("  > [ %d ] %s (%d) ", opt, label, ammunition);
}

void print_exit_opt() {
    printf("  > [ %d ] SAIR ", EXIT_OPT);
}

void draw_lines(char (*board)[BOARD_SZ], Projectile* arsenal) {
    int ai = 0;
    int menu_line = BOARD_SZ - ARSENAL_SZ + 1;

    for (int y = 0; y < BOARD_SZ; y++) {
        printf("%2d |", (y + 1));

        for (int x = 0; x < BOARD_SZ; x++) {
            draw_cell(board[y][x], x);
        }

        putchar('|');

        if (menu_line == y && ai < ARSENAL_SZ) {
            print_proj_opt((ai + 1), arsenal[ai].label, arsenal[ai].ammunition);
            ai++;

            draw_div(' ', 59, "\n   |", "|");
            print_proj_opt((ai + 1), arsenal[ai].label, arsenal[ai].ammunition);
            putchar('\n');

            ai++;
            menu_line++;

            continue;
        }

        if (y == LAST_POS_BOARD) {
            print_exit_opt();
        } else {
            draw_div(' ', 59, "\n   |", "|");
            putchar('\n');
        }
    }
}

// Input functions
void read_player_name(char* player_name) {
    char buffer[PLAYER_NAME_SZ];

    read_str(buffer, sizeof(buffer));
    transform_to_upper(buffer);
    snprintf(player_name, PLAYER_NAME_SZ, "%s", buffer);
}

// Output functions
void render(GameState* stt) {
    // REMEMBER: switch from control_board to draw_board
    char (*board)[BOARD_SZ] = stt->control_board;
    Projectile* arsenal = stt->player.arsenal;

    draw_columns_letters();
    print_player_data(stt->player.name, stt->player.score);
    draw_div('-', 59, "\n   +", "+\n");
    draw_lines(board, arsenal);
    draw_div('-', 59, "\n   +", "+\n");
}
