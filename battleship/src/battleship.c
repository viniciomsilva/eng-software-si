#include "battleship.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SMN_DAM_SZ 9
#define TPD_DAM_SZ 7
#define BMB_DAM_SZ 5
#define GNF_DAM_SZ 1

#define SMN 3
#define TPD 2
#define BMB 1
#define GNF 0

#define DRTS_SZ 4

const Coord DIRECTIONS[DRTS_SZ] = {
    { .x = 0, .y = 1 },
    { .x = 1, .y = 0 },
    { .x = 1, .y = 1 },
    { .x = -1, .y = 1 },
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

void create_projectile(Projectile* proj, Coord* damage, int ammunition, const char* label) {
    proj->ammunition = ammunition;
    strncpy(proj->label, label, PROJECTILE_LABEL_SZ);
    memcpy(proj->damage, damage, DAMAGE_MAX_SZ);
}

void gen_damage(Coord* dest, int dan_map) {
    switch (dan_map) {
        case GNF: {
            Coord src[GNF_DAM_SZ] = {
                { .x = 0, .y = 0 },
            };
            memcpy(dest, src, sizeof(src));
            break;
        }

        case BMB: {
            Coord src[BMB_DAM_SZ] = {
                { .x = 0, .y = 0 },   //
                { .x = -1, .y = 0 },  //
                { .x = 1, .y = 0 },   //
                { .x = 0, .y = -1 },  //
                { .x = 0, .y = 1 },   //
            };
            memcpy(dest, src, sizeof(src));
            break;
        }

        case TPD: {
            Coord src[TPD_DAM_SZ] = {
                { .x = 0, .y = 0 },   //
                { .x = -1, .y = 0 },  //
                { .x = -2, .y = 0 },  //
                { .x = 1, .y = 0 },   //
                { .x = 2, .y = 0 },   //
                { .x = 0, .y = -1 },  //
                { .x = 0, .y = 1 },   //
            };
            memcpy(dest, src, sizeof(src));
            break;
        }

        case SMN: {
            Coord src[SMN_DAM_SZ] = {
                { .x = 0, .y = 0 },   //
                { .x = -1, .y = 0 },  //
                { .x = 1, .y = 0 },   //
                { .x = 0, .y = -1 },  //
                { .x = -2, .y = 1 },  //
                { .x = -1, .y = 1 },  //
                { .x = 0, .y = 1 },   //
                { .x = 1, .y = 1 },   //
                { .x = 2, .y = 1 },   //
            };
            memcpy(dest, src, sizeof(src));
            break;
        }
    }
}

// Modification functions
void init_player_state(Player* player, const char* name) {
    int amm[ARSENAL_SZ] = { 25, 4, 4, 3 };
    const char* labels[ARSENAL_SZ] = { "GNF", "BMB", "TPD", "SMN" };

    strncpy(player->name, name, (PLAYER_NAME_SZ - 1));
    player->name[(PLAYER_NAME_SZ - 1)] = '\0';
    player->score = 0;

    for (int i = 0; i < ARSENAL_SZ; i++) {
        Coord damage[DAMAGE_MAX_SZ] = { 0 };

        gen_damage(damage, i);
        create_projectile(&player->arsenal[i], damage, amm[i], labels[i]);
    }
}

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

    int lengths[SHIPS_QTY] = { 5, 4, 3, 3, 2 };
    char labels[SHIPS_QTY] = { 'A', 'B', 'S', 'D', 'P' };

    for (int i = 0; i < SHIPS_QTY; i++) {
        create_ship(stt->control_board, &stt->ships[i], labels[i], lengths[i]);
    }
}
