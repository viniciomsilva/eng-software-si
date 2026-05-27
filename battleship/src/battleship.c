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
int is_inside_board(Coord c) {
    return c.x >= 0 && c.x < BOARD_SZ && c.y >= 0 && c.y < BOARD_SZ;
}

int is_filledout(char (*board)[BOARD_SZ], Coord coord) {
    if (!is_inside_board(coord)) return 1;

    return board[coord.y][coord.x];
}

Coord increment(Coord coord, int drt, int times) {
    coord.x += times * DIRECTIONS[drt].x;
    coord.y += times * DIRECTIONS[drt].y;

    return coord;
}

int is_anything(char (*board)[BOARD_SZ], Coord coord, int size, int drt) {
    while (size > 0) {
        if (is_filledout(board, coord)) return 1;

        coord = increment(coord, drt, 1);
        size--;
    }

    return 0;
}

int draw_random(int lim) {
    return rand() % lim;
}

Coord gen_start_coord(int size, int drt) {
    Coord start_coord = { 0 };

    while (1) {
        start_coord.x = draw_random(BOARD_SZ);
        start_coord.y = draw_random(BOARD_SZ);

        Coord last_coord = increment(start_coord, drt, (size - 1));

        if (is_inside_board(last_coord)) break;
    }

    return start_coord;
}

void place_on_board(char (*board)[BOARD_SZ], Ship* ship, Coord coord, int drt) {
    for (int i = 0; i < ship->size; i++) {
        board[coord.y][coord.x] = ship->label;
        ship->coords[i].hit = 0;
        ship->coords[i].x = coord.x;
        ship->coords[i].y = coord.y;
        coord = increment(coord, drt, 1);
    }
}

void create_ship(char (*board)[BOARD_SZ], Ship* ship, char label, int size) {
    int drt = 0;
    Coord start_coord = { 0 };

    ship->label = label;
    ship->size = size;

    while (1) {
        drt = draw_random(DRTS_SZ);
        start_coord = gen_start_coord(ship->size, drt);

        if (is_anything(board, start_coord, ship->size, drt)) continue;

        break;
    }

    place_on_board(board, ship, start_coord, drt);
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
