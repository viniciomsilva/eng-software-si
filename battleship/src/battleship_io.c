/**
 * @file battleship_io.c
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Implementation of Input and Output operations for the Battleship game.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */
#include "battleship_io.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../utils/utils.h"
#include "battleship.h"

#define DIVISION_TIMES 59                  // umber of characters making up the division line.
#define LAST_BOARD_INDEX (BOARD_SIZE - 1)  // Actual upper bound index of the board matrix.

/**
 * @brief Characters representing the board columns.
 *
 */
const char COLUMNS_LETTERS[BOARD_SIZE] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
};

/**
 * @brief Draws a stylized horizontal division line in the terminal.
 *
 * @param c Character used to construct the line body.
 * @param start Starting string prefix for the line.
 * @param end Ending string suffix for the line.
 */
void draw_division(char c, const char* start, const char* end) {
    printf("%s", start);

    for (int times = 0; times < DIVISION_TIMES; times++) {
        putchar(c);
    }

    printf("%s", end);
}

/**
 * @brief Draws the column headers (letters) for the board grid.
 *
 */
void draw_columns_letters(void) {
    printf("\n   |");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("  %c  |", COLUMNS_LETTERS[i]);
    }
}

/**
 * @brief Draws the content of a single board cell in the terminal.
 *
 * @param content Character content of the cell.
 * @param x Current column index of the cell.
 */
void draw_cell(char content, int x) {
    printf("  %c  ", content ? content : ' ');

    if (x != LAST_BOARD_INDEX) {
        putchar(' ');
    }
}

/**
 * @brief Prints the player's metadata: name and current score.
 *
 * @param player Pointer to the player structure.
 */
void print_player_data(Player* player) {
    printf("  > %s %dPT", player->name, player->score);
}

/**
 * @brief Prints a selectable projectile option. Displays its menu index number,
 * label, and available ammo.
 *
 * @param projectile Pointer to the projectile structure.
 * @param option Selection menu option number.
 */
void print_projectile_option(Projectile* projectile, int option) {
    printf("  > [ %d ] %s (%d) ", option, projectile->label, projectile->count);
}

/**
 * @brief Prints the option to exit the game.
 *
 */
void print_exit_option(void) {
    printf("  > [ %d ] SAIR ", EXIT_OPTION);
}

/**
 * @brief Renders the board rows, cell contents, and side-menus.
 *
 * Iterates through the matrix to render it as a tactical battleship grid,
 * simultaneously embedding player metrics and projectile options into the right
 * margins.
 *
 * @param board Pointer to the 2D array board grid.
 * @param arsenal Pointer to the player's projectile arsenal array.
 */
void draw_lines(char (*board)[BOARD_SIZE], Projectile* arsenal) {
    int projectile_i = 0;
    int menu_line = (BOARD_SIZE - ARSENAL_SIZE + 1);  // Row index where projectile display begins.

    for (int y = 0; y < BOARD_SIZE; y++) {
        printf("%2d |", (y + 1));

        for (int x = 0; x < BOARD_SIZE; x++) {
            draw_cell(board[y][x], x);
        }

        putchar('|');

        // If the current row matches the menu placement layout
        // and there are still unrendered projectiles in the arsenal.
        if (menu_line == y && projectile_i < ARSENAL_SIZE) {
            print_projectile_option(&arsenal[projectile_i], (projectile_i + 1));
            projectile_i++;

            if (projectile_i < ARSENAL_SIZE) {
                draw_division(' ', "\n   |", "|");
                print_projectile_option(&arsenal[projectile_i], (projectile_i + 1));
                projectile_i++;
            }

            putchar('\n');
            menu_line++;
            continue;
        }

        if (y == LAST_BOARD_INDEX) {
            print_exit_option();
            break;
        }

        draw_division(' ', "\n   |", "|\n");
    }
}

void io_read_player_name(char* player_name) {
    char buffer[PLAYER_NAME_SIZE];

    read_str(buffer, sizeof(buffer));
    transform_to_upper(buffer);
    snprintf(player_name, PLAYER_NAME_SIZE, "%s", buffer);
}

Coord io_read_coord(void) {
    char buffer[BUFFER_SIZE];
    Coord coord = { .x = -1, .y = -1 };

    read_str(buffer, sizeof(buffer));
    transform_to_upper(buffer);

    if (buffer[0] == EMPTY) return coord;
    if (buffer[0] < COLUMNS_LETTERS[0] || buffer[0] > COLUMNS_LETTERS[LAST_BOARD_INDEX]) return coord;
    if (!isdigit(buffer[1])) return coord;
    if (buffer[2] != EMPTY && !isdigit(buffer[2])) return coord;

    coord.x = buffer[0] - COLUMNS_LETTERS[0];
    coord.y = atoi(&buffer[1]) - 1;
    return coord;
}

void io_render(GameState* state) {
    char (*board)[BOARD_SIZE] = state->control_board;
    Projectile* arsenal = state->player.arsenal;

    draw_columns_letters();
    print_player_data(&state->player);
    draw_division('-', "\n   +", "+\n");
    draw_lines(board, arsenal);
    draw_division('-', "\n   +", "+\n");
}
