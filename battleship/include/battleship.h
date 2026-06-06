#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define PLAYER_NAME_SZ 11
#define BOARD_SZ 10
#define DAMAGE_MAX_SZ 9
#define PROJECTILE_LABEL_SZ 4
#define ARSENAL_SZ 4

#define SHIPS_QTY 5

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
    char label[PROJECTILE_LABEL_SZ];
    Coord damage[DAMAGE_MAX_SZ];
} Projectile;

typedef struct Player {
    int amm_total;
    int score;
    char name[PLAYER_NAME_SZ];
    Projectile arsenal[ARSENAL_SZ];
} Player;

typedef struct GameState {
    int running;
    char control_board[BOARD_SZ][BOARD_SZ];
    char draw_board[BOARD_SZ][BOARD_SZ];
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
