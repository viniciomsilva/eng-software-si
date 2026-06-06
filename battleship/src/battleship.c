#include "battleship.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../utils/utils.h"

#define SMN_DAM_SZ 9
#define TPD_DAM_SZ 7
#define BMB_DAM_SZ 5
#define GNF_DAM_SZ 1

#define SMN 3
#define TPD 2
#define BMB 1
#define GNF 0

#define DRTS_SZ 4

#define WATER_LABEL '~'

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

Coord increment_coord(Coord coord, Coord icr, int times) {
    coord.x += times * icr.x;
    coord.y += times * icr.y;

    return coord;
}

int is_anything(char (*board)[BOARD_SZ], Coord coord, int size, int drt) {
    while (size > 0) {
        if (is_filledout(board, coord)) return 1;

        coord = increment_coord(coord, DIRECTIONS[drt], 1);
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

        Coord last_coord = increment_coord(start_coord, DIRECTIONS[drt], (size - 1));

        if (is_inside_board(last_coord)) break;
    }

    return start_coord;
}

void place_on_board(char (*board)[BOARD_SZ], Ship* ship, Coord coord, int drt) {
    for (int i = 0; i < ship->size; i++) {
        board[coord.y][coord.x] = ship->label;
        coord = increment_coord(coord, DIRECTIONS[drt], 1);
    }
}

void create_ship(char (*board)[BOARD_SZ], Ship* ship, char label, int size) {
    int drt = 0;
    Coord start_coord = { 0 };

    ship->label = label;
    ship->size = size;
    ship->is_sunk = 0;
    ship->has_been_recorded = 0;

    while (1) {
        drt = draw_random(DRTS_SZ);
        start_coord = gen_start_coord(ship->size, drt);

        if (is_anything(board, start_coord, ship->size, drt)) continue;

        break;
    }

    place_on_board(board, ship, start_coord, drt);
}

void create_projectile(Projectile* proj, Coord* damage, int amm, int damage_size, const char* label) {
    proj->ammunition = amm;
    proj->damage_size = damage_size;
    strncpy(proj->label, label, PROJECTILE_LABEL_SZ);
    memcpy(proj->damage, damage, (DAMAGE_MAX_SZ * sizeof(Coord)));
}

void gen_damage(Coord* dest, int proj_type) {
    switch (proj_type) {
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

Collision was_there_collision(char (*board)[BOARD_SZ], Coord target) {
    char content = board[target.y][target.x];
    Collision result = {
        .collided = 0,
        .who = WATER_LABEL,
    };

    if (content == '\0') return result;

    result.collided = 1;
    result.who = content;
    return result;
}

void update_ships_state(Ship* ships, char target_label) {
    for (int i = 0; i < SHIPS_QTY; i++) {
        if (target_label == ships[i].label) {
            ships[i].size--;

            if (!ships[i].size) {
                ships[i].is_sunk = 1;
            }

            break;
        }
    }
}

void fill_in(char (*board)[BOARD_SZ], Coord coord, char content) {
    board[coord.y][coord.x] = content;
}

void init_player_state(Player* player, const char* name) {
    const int amm[ARSENAL_SZ] = { 25, 4, 4, 3 };
    const int sizes[ARSENAL_SZ] = {
        GNF_DAM_SZ,
        BMB_DAM_SZ,
        TPD_DAM_SZ,
        SMN_DAM_SZ,
    };
    const char* labels[ARSENAL_SZ] = { "GNF", "BMB", "TPD", "SMN" };

    strncpy(player->name, name, (PLAYER_NAME_SZ - 1));
    player->name[(PLAYER_NAME_SZ - 1)] = '\0';
    player->score = 0;
    player->amm_total = sum(amm, ARSENAL_SZ);

    for (int i = 0; i < ARSENAL_SZ; i++) {
        Coord damage[DAMAGE_MAX_SZ] = { 0 };

        gen_damage(damage, i);
        create_projectile(&player->arsenal[i], damage, amm[i], sizes[i], labels[i]);
    }
}

void init_boards(GameState* stt) {
    Coord coord = { 0 };

    for (int y = 0; y < BOARD_SZ; y++) {
        coord.y = y;

        for (int x = 0; x < BOARD_SZ; x++) {
            coord.x = x;
            fill_in(stt->control_board, coord, '\0');
            fill_in(stt->draw_board, coord, '\0');
        }
    }
}

void init_ships(GameState* stt) {
    srand(time(NULL));

    const int lengths[SHIPS_QTY] = { 5, 4, 3, 3, 2 };
    const char labels[SHIPS_QTY] = { 'A', 'B', 'S', 'D', 'P' };

    for (int i = 0; i < SHIPS_QTY; i++) {
        create_ship(stt->control_board, &stt->ships[i], labels[i], lengths[i]);
    }
}

// Validation functions
int validate_proj(Projectile* arsenal, int proj_i) {
    return ((proj_i >= 0 || proj_i < ARSENAL_SZ) && arsenal[proj_i].ammunition);
}

int validate_coord(Coord coord) {
    return is_inside_board(coord);
}

int did_sink_all_ships(Player* player) {
    return player->score == SHIPS_QTY;
}

int did_run_out_ammunition(Player* player) {
    return !player->amm_total;
}

// Modification functions
void finish_game(GameState* stt) {
    stt->running = 0;
}

void init_game_state(GameState* stt, const char* player_name) {
    stt->running = 1;
    init_boards(stt);
    init_ships(stt);
    init_player_state(&stt->player, player_name);
}

void update_player_score(Player* player, Ship* ships) {
    for (int i = 0; i < SHIPS_QTY; i++) {
        if (!ships[i].has_been_recorded && ships[i].is_sunk) {
            player->score++;
            ships[i].has_been_recorded = 1;
        }
    }
}

int fire(GameState* stt, int proj_index, Coord coord) {
    int success = 0;
    Projectile* proj = &stt->player.arsenal[proj_index];

    for (int i = 0; i < proj->damage_size; i++) {
        Coord target = increment_coord(coord, proj->damage[i], 1);

        if (is_filledout(stt->draw_board, target)) continue;

        Collision result = was_there_collision(stt->control_board, target);

        if (result.collided) {
            update_ships_state(stt->ships, result.who);
            success = 1;
        }

        fill_in(stt->draw_board, target, result.who);
    }

    stt->player.amm_total--;
    proj->ammunition--;
    return success;
}
