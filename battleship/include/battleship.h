#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define PLAYER_NAME_SZ 11
#define BOARD_SZ 10
#define DAMAGE_MAX_SZ 9
#define PROJECTILE_LABEL_SZ 4
#define ARSENAL_SZ 4

#define SHIPS_QTY 5

typedef struct AttackStatus {
    int proj_fail;
    int coord_fail;
    int success;
} AttackStatus;

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
    Coord damage[DAMAGE_MAX_SZ];
    int ammunition;
    int damage_size;
    char label[PROJECTILE_LABEL_SZ];
} Projectile;

typedef struct Player {
    Projectile arsenal[ARSENAL_SZ];
    int score;
    char name[PLAYER_NAME_SZ];
} Player;

typedef struct GameState {
    Player player;
    Ship ships[SHIPS_QTY];
    char control_board[BOARD_SZ][BOARD_SZ];
    char draw_board[BOARD_SZ][BOARD_SZ];
} GameState;

// Validation functions
int validate_coord(Coord);
int validate_proj(int proj_type);

// Modification function
void init_game_state(GameState*, const char* player_name);
void update_player_score(Player*, Ship*);
int fire(GameState*, int proj_index, Coord coord);

#endif  // BATTLESHIP_H
