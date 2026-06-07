#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdbool.h>

#define WATER_LABEL '~'
#define EMPTY_LABEL '\0'

#define SHIPS_QTY 5

// Structures sizes
#define ARSENAL_SIZE 4
#define PROJECTILE_LABEL_SIZE 4
#define DAMAGE_MAX_SIZE 9
#define BOARD_SIZE 10
#define PLAYER_NAME_SIZE 11

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Ship {
    int length;
    bool is_sunk;
    bool has_been_recorded;
    char label;
} Ship;

typedef struct Projectile {
    int ammunition;
    int damage_size;
    char label[PROJECTILE_LABEL_SIZE];
    Coord damage[DAMAGE_MAX_SIZE];
} Projectile;

typedef struct Player {
    int ammunition_total;
    int score;
    char name[PLAYER_NAME_SIZE];
    Projectile arsenal[ARSENAL_SIZE];
} Player;

typedef struct GameState {
    bool running;
    char control_board[BOARD_SIZE][BOARD_SIZE];
    char draw_board[BOARD_SIZE][BOARD_SIZE];
    Ship ships[SHIPS_QTY];
    Player player;
} GameState;

// Validation functions
bool validate_coord(Coord coord);
bool validate_projectile(Projectile* arsenal, int i);
bool did_sink_all_ships(Player* player);
bool did_run_out_ammunition(Player* player);

// Modification function
void finish_game(GameState* state);
void init_game_state(GameState* state, const char* player_name);
void update_player_score(Player* player, Ship* ships);
bool fire(GameState* state, int projectile_i, Coord coord);

#endif  // BATTLESHIP_H
