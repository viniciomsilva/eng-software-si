#include "battleship_io.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../utils/utils.h"
#include "battleship.h"

#define DIVISION_TIMES 59
#define BOARD_REAL_SIZE (BOARD_SIZE - 1)

const char COLUMNS[BOARD_SIZE] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
};

// Auxiliar functions
void draw_division(char c, const char* start, const char* end) {
    printf("%s", start);

    for (int times = 0; times < DIVISION_TIMES; times++) {
        putchar(c);
    }

    printf("%s", end);
}

void draw_columns_letters(void) {
    putchar('\n');
    printf("   |");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("  %c  |", COLUMNS[i]);
    }
}

void draw_cell(char content, int x) {
    printf("  %c  ", content ? content : ' ');

    if (x != BOARD_REAL_SIZE) {
        putchar(' ');
    }
}

void print_player_data(Player* player) {
    printf("  > %s %dPT", player->name, player->score);
}

void print_projectile_option(Projectile* projectile, int option) {
    printf("  > [ %d ] %s (%d) ", option, projectile->label, projectile->ammunition);
}

void print_exit_option(void) {
    printf("  > [ %d ] SAIR ", EXIT_OPTION);
}

void draw_lines(char (*board)[BOARD_SIZE], Projectile* arsenal) {
    int projectile_i = 0;
    int menu_line = (BOARD_SIZE - ARSENAL_SIZE + 1);

    for (int y = 0; y < BOARD_SIZE; y++) {
        printf("%2d |", (y + 1));

        for (int x = 0; x < BOARD_SIZE; x++) {
            draw_cell(board[y][x], x);
        }

        putchar('|');

        if (menu_line == y && projectile_i < ARSENAL_SIZE) {
            print_projectile_option(&arsenal[projectile_i], (projectile_i + 1));

            projectile_i++;

            draw_division(' ', "\n   |", "|");
            print_projectile_option(&arsenal[projectile_i], (projectile_i + 1));
            putchar('\n');

            projectile_i++;
            menu_line++;
            continue;
        }

        if (y == BOARD_REAL_SIZE) {
            print_exit_option();
        } else {
            draw_division(' ', "\n   |", "|");
            putchar('\n');
        }
    }
}

// Input functions
void read_player_name(char* player_name) {
    char buffer[PLAYER_NAME_SIZE];

    read_str(buffer, sizeof(buffer));
    transform_to_upper(buffer);
    snprintf(player_name, PLAYER_NAME_SIZE, "%s", buffer);
}

Coord read_coord(void) {
    char buffer[BUFFER_SIZE];
    Coord coord = { .x = -1, .y = -1 };

    read_str(buffer, sizeof(buffer));
    transform_to_upper(buffer);

    if (buffer[0] == EMPTY_LABEL) return coord;

    if (buffer[0] < COLUMNS[0] || buffer[0] > COLUMNS[BOARD_REAL_SIZE]) return coord;

    if (!isdigit(buffer[1])) return coord;

    if (buffer[2] != EMPTY_LABEL && !isdigit(buffer[2])) return coord;

    coord.x = buffer[0] - COLUMNS[0];
    coord.y = atoi(&buffer[1]) - 1;
    return coord;
}

// Output functions
void render(GameState* stt) {
    char (*board)[BOARD_SIZE] = stt->draw_board;
    Projectile* arsenal = stt->player.arsenal;

    draw_columns_letters();
    print_player_data(&stt->player);
    draw_division('-', "\n   +", "+\n");
    draw_lines(board, arsenal);
    draw_division('-', "\n   +", "+\n");
}
