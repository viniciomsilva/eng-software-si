#include "battleship.h"

#include <stdlib.h>
#include <time.h>

#define DRTS_SZ 4

const Coord DIRECTIONS[DRTS_SZ] = {
    { .x = 0, .y = 1 },   // vertical
    { .x = 1, .y = 0 },   // horizontal
    { .x = 1, .y = 1 },   // positive diagonal
    { .x = -1, .y = 1 },  // negative diagonal
};

// Auxiliar functions
int is_inside_board(int value) {
    return value >= 0 && value < BOARD_SZ;
}

int is_filledout(char (*board)[BOARD_SZ], Coord coord) {
    return board[coord.y][coord.x];
}

int is_anything(char (*board)[BOARD_SZ], Coord coord, int size, int drt) {
    for (int i = 0; i < size; i++) {
        if (is_filledout(board, coord)) return 1;

        coord.x += DIRECTIONS[drt].x;
        coord.y += DIRECTIONS[drt].y;
    }

    return 0;
}

int draw(int lim) {
    return rand() % lim;
}

int gen_coord(int size, int drt, int is_x) {
    int icr = is_x ? DIRECTIONS[drt].x : DIRECTIONS[drt].y;

    while (1) {
        int coord = draw(BOARD_SZ);
        int last_coord = coord + size * icr;

        if (!is_inside_board(last_coord)) continue;

        return coord;
    }
}

void place_on_board(char (*board)[BOARD_SZ], Ship* ship, Coord coord, int drt) {
    for (int i = 0; i < ship->size; i++) {
        board[coord.y][coord.x] = ship->label;
        coord.x += DIRECTIONS[drt].x;
        coord.y += DIRECTIONS[drt].y;
    }
}

void create_ship(char (*board)[BOARD_SZ], Ship* ship, char label, int size) {
    Coord coord = { 0 };
    int drt = draw(DRTS_SZ);

    ship->label = label;
    ship->size = size;

    while (1) {
        coord.x = gen_coord(ship->size, drt, 1);
        coord.y = gen_coord(ship->size, drt, 0);

        if (is_anything(board, coord, ship->size, drt)) continue;

        place_on_board(board, ship, coord, drt);
        break;
    }
}

// Modification functions
void init_boards(GameState* stt) {
    for (int y = 0; y < BOARD_SZ; y++) {
        for (int x = 0; x < BOARD_SZ; x++) {
            stt->control_board[y][x] = '\0';
            stt->draw_board[y][x] = '\0';
        }
    }
}

void init_ships(GameState* stt) {
    srand(time(NULL));

    /*
        Aircraft carrier    A       5 coords
        Battleship          B       4 coords
        Submarine           S       3 coords
        Destroyer           D       3 coords
        Patrol boat         P       2 coords
     */

    int lengths[SHIPS_QTY] = { 5, 4, 3, 3, 2 };
    char labels[SHIPS_QTY] = { 'A', 'B', 'S', 'D', 'P' };

    for (int i = 0; i < SHIPS_QTY; i++) {
        create_ship(stt->control_board, &stt->ships[i], labels[i], lengths[i]);
    }
}
