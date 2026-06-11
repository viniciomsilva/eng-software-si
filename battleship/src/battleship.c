#include "battleship.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../utils/utils.h"

// Ship labels
#define AIC 'A'  // AIRCRAFT CARRIER
#define BSH 'B'  // BATTLESHIP
#define SUB 'S'  // SUBMARINE
#define DES 'D'  // DESTROYER
#define PAB 'P'  // PATROL BOAT

// Ship lengths
#define AIC_LENGTH 5
#define BSH_LENGTH 4
#define SUB_LENGTH 3
#define DES_LENGTH 3
#define PAB_LENGTH 2

// Projectiles indexes
#define GNF 0  // GUNFIRE
#define BMB 1  // BOMB
#define TPD 2  // TORPEDO
#define SMN 3  // SEA MINE

// Projectiles damage sizes
#define GNF_DAMAGE_SIZE 1
#define BMB_DAMAGE_SIZE 5
#define TPD_DAMAGE_SIZE 7
#define SMN_DAMAGE_SIZE 9

// Projectiles ammunition
#define GNF_AMMUNITION 20
#define BMB_AMMUNITION 3
#define TPD_AMMUNITION 4
#define SMN_AMMUNITION 3

#define DIRECTIONS_SIZE 4
#define PLAYER_NAME_REAL_SIZE (PLAYER_NAME_SIZE - 1)

const Coord DIRECTIONS[DIRECTIONS_SIZE] = {
    { .x = 0, .y = 1 },
    { .x = 1, .y = 0 },
    { .x = 1, .y = 1 },
    { .x = -1, .y = 1 },
};

// Auxiliar structures
typedef struct Collision {
    bool collided;
    char who;
} Collision;

typedef struct Path {
    Coord source;
    Coord direction;
    int displacement;
} Path;

typedef struct ShipPattern {
    int length;
    char label;
} ShipPattern;

typedef struct ProjectilePattern {
    int ammunition;
    int damage_size;
    const char* label;
    Coord* damage;
} ProjectilePattern;

// Auxiliar functions
bool is_inside_board(Coord coord) {
    return coord.x >= 0 && coord.x < BOARD_SIZE && coord.y >= 0 && coord.y < BOARD_SIZE;
}

bool is_filledout(char (*board)[BOARD_SIZE], Coord coord) {
    return !is_inside_board(coord) || board[coord.y][coord.x] != EMPTY_LABEL;
}

void decrement_ammunition(int* projetil_ammunition, int* player_total_ammunition) {
    *projetil_ammunition -= 1;
    *player_total_ammunition -= 1;
}

int draw_random(int limit) {
    return rand() % limit;
}

Coord increment_coord(Path path) {
    path.source.x += path.direction.x * path.displacement;
    path.source.y += path.direction.y * path.displacement;
    return path.source;
}

Coord gen_start_coord(Path path, int length) {
    path.displacement = --length;

    while (true) {
        path.source.x = draw_random(BOARD_SIZE);
        path.source.y = draw_random(BOARD_SIZE);

        Coord last_coord = increment_coord(path);

        if (is_inside_board(last_coord)) break;
    }

    return path.source;
}

bool is_anything(char (*board)[BOARD_SIZE], Path path, int length) {
    path.displacement = 1;

    while (length > 0) {
        if (is_filledout(board, path.source)) return true;

        path.source = increment_coord(path);
        length--;
    }

    return false;
}

void place_on_board(char (*board)[BOARD_SIZE], Ship* ship, Path path) {
    path.displacement = 1;

    for (int i = 0; i < ship->length; i++) {
        board[path.source.y][path.source.x] = ship->label;
        path.source = increment_coord(path);
    }
}

void create_ship(char (*board)[BOARD_SIZE], Ship* ship, ShipPattern pattern) {
    Path path = { 0 };

    ship->label = pattern.label;
    ship->length = pattern.length;
    ship->is_sunk = false;
    ship->has_been_recorded = false;

    while (true) {
        path.direction = DIRECTIONS[draw_random(DIRECTIONS_SIZE)];
        path.source = gen_start_coord(path, pattern.length);

        if (is_anything(board, path, pattern.length)) continue;

        break;
    }

    place_on_board(board, ship, path);
}

void create_projectile(Projectile* projectile, ProjectilePattern pattern) {
    int mem_size_damage = DAMAGE_MAX_SIZE * sizeof(Coord);

    projectile->ammunition = pattern.ammunition;
    projectile->damage_size = pattern.damage_size;
    strncpy(projectile->label, pattern.label, PROJECTILE_LABEL_SIZE);
    memcpy(projectile->damage, pattern.damage, mem_size_damage);
}

void gen_damage(Coord* dest, int projectile_i) {
    switch (projectile_i) {
        case GNF: {
            Coord src[GNF_DAMAGE_SIZE] = {
                { .x = 0, .y = 0 },
            };

            memcpy(dest, src, sizeof(src));
            break;
        }

        case BMB: {
            Coord src[BMB_DAMAGE_SIZE] = {
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
            Coord src[TPD_DAMAGE_SIZE] = {
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
            Coord src[SMN_DAMAGE_SIZE] = {
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

Collision was_there_collision(char (*board)[BOARD_SIZE], Coord target) {
    char content = board[target.y][target.x];
    Collision result = {
        .collided = false,
        .who = WATER_LABEL,
    };

    if (content == EMPTY_LABEL) return result;

    result.collided = true;
    result.who = content;
    return result;
}

void update_ships_state(Ship* ships, char target_label) {
    for (int i = 0; i < SHIPS_QTY; i++) {
        if (target_label == ships[i].label) {
            ships[i].length--;

            if (!ships[i].length) {
                ships[i].is_sunk = true;
            }

            break;
        }
    }
}

void fill_in(char (*board)[BOARD_SIZE], Coord coord, char content) {
    board[coord.y][coord.x] = content;
}

void init_player_state(Player* player, const char* name) {
    const int ammunition[ARSENAL_SIZE] = {
        GNF_AMMUNITION,
        BMB_AMMUNITION,
        TPD_AMMUNITION,
        SMN_AMMUNITION,
    };
    const int damage_sizes[ARSENAL_SIZE] = {
        GNF_DAMAGE_SIZE,
        BMB_DAMAGE_SIZE,
        TPD_DAMAGE_SIZE,
        SMN_DAMAGE_SIZE,
    };
    const char* labels[ARSENAL_SIZE] = {
        "GNF",
        "BMB",
        "TPD",
        "SMN",
    };

    strncpy(player->name, name, PLAYER_NAME_REAL_SIZE);
    player->name[PLAYER_NAME_REAL_SIZE] = EMPTY_LABEL;
    player->score = 0;
    player->wins = false;
    player->ammunition_total = sum(ammunition, ARSENAL_SIZE);

    for (int i = 0; i < ARSENAL_SIZE; i++) {
        Coord damage[DAMAGE_MAX_SIZE] = { 0 };
        gen_damage(damage, i);

        ProjectilePattern pattern = {
            .ammunition = ammunition[i],
            .label = labels[i],
            .damage = damage,
            .damage_size = damage_sizes[i],
        };
        create_projectile(&player->arsenal[i], pattern);
    }
}

void init_boards(GameState* state) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Coord coord = {
                .x = x,
                .y = y,
            };

            fill_in(state->control_board, coord, EMPTY_LABEL);
            fill_in(state->draw_board, coord, EMPTY_LABEL);
        }
    }
}

void init_ships(GameState* state) {
    srand(time(NULL));

    const int lengths[SHIPS_QTY] = {
        AIC_LENGTH, BSH_LENGTH, SUB_LENGTH, DES_LENGTH, PAB_LENGTH,
    };
    const char labels[SHIPS_QTY] = {
        AIC, BSH, SUB, DES, PAB,
    };

    for (int i = 0; i < SHIPS_QTY; i++) {
        ShipPattern pattern = {
            .label = labels[i],
            .length = lengths[i],
        };

        create_ship(state->control_board, &state->ships[i], pattern);
    }
}

// Validation functions
bool validate_projectile(Projectile* arsenal, int i) {
    return i >= 0 && i < ARSENAL_SIZE && arsenal[i].ammunition;
}

bool validate_coord(Coord coord) {
    return is_inside_board(coord);
}

bool did_sink_all_ships(Player* player) {
    return player->score == SHIPS_QTY;
}

bool did_run_out_ammunition(Player* player) {
    return !player->ammunition_total;
}

// Modification functions
void finish_game(GameState* state) {
    state->running = false;
}

void init_game_state(GameState* state, const char* player_name) {
    state->running = true;
    init_boards(state);
    init_ships(state);
    init_player_state(&state->player, player_name);
}

void update_player_score(Player* player, Ship* ships) {
    for (int i = 0; i < SHIPS_QTY; i++) {
        if (!ships[i].has_been_recorded && ships[i].is_sunk) {
            ships[i].has_been_recorded = true;
            player->score++;
        }
    }
}

void open_all_draw_board(GameState* state) {
    char (*control_board)[BOARD_SIZE] = state->control_board;
    char (*draw_board)[BOARD_SIZE] = state->draw_board;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Coord coord = {
                .x = x,
                .y = y,
            };

            if (is_filledout(draw_board, coord)) continue;
            if (control_board[y][x] == EMPTY_LABEL) continue;

            fill_in(draw_board, coord, control_board[y][x]);
        }
    }
}

void set_player_wins(Player* player) {
    player->wins = true;
}

bool fire(GameState* state, int projectile_i, Coord coord) {
    bool success = false;
    Projectile* projectile = &state->player.arsenal[projectile_i];
    Path path = {
        .source = coord,
        .displacement = 1,
    };

    for (int i = 0; i < projectile->damage_size; i++) {
        path.direction = projectile->damage[i];
        Coord target = increment_coord(path);

        if (is_filledout(state->draw_board, target)) continue;

        Collision result = was_there_collision(state->control_board, target);

        if (result.collided) {
            update_ships_state(state->ships, result.who);
            success = true;
        }

        fill_in(state->draw_board, target, result.who);
    }

    decrement_ammunition(&projectile->ammunition, &state->player.ammunition_total);
    return success;
}
