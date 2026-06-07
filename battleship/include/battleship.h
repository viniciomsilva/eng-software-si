#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define WATER_LABEL '~'
#define EMPTY_LABEL '\0'

#define SHIPS_QTY 5

enum Sizes {
    ARSENAL_SIZE = 4,
    PROJECTILE_LABEL_SIZE = 4,
    DAMAGE_MAX_SIZE = 9,
    BOARD_SIZE = 10,
    PLAYER_NAME_SIZE = 11,
};

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Ship {
    int size;
    int is_sunk;
    int has_been_recorded;
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
    int running;
    char control_board[BOARD_SIZE][BOARD_SIZE];
    char draw_board[BOARD_SIZE][BOARD_SIZE];
    Ship ships[SHIPS_QTY];
    Player player;
} GameState;

// Validation functions
int validate_coord(Coord);
int validate_projectile(Projectile*, int i);
int did_sink_all_ships(Player*);
int did_run_out_ammunition(Player*);

// Modification function
void finish_game(GameState*);
void init_game_state(GameState*, const char* player_name);
void update_player_score(Player*, Ship*);
int fire(GameState*, int projectile_i, Coord coord);

#endif  // BATTLESHIP_H
