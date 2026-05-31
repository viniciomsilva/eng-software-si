#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define PLAYER_NAME_SZ 11
#define BOARD_SZ 10
#define DAMAGE_MAX_SZ 9
#define SHIPS_MAX_SZ 5
#define PROJECTILE_LABEL_SZ 4
#define ARSENAL_SZ 4

#define SHIPS_QTY 5

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct ShipCoord {
    int x;
    int y;
    int hit;
} ShipCoord;

typedef struct Ship {
    ShipCoord coords[SHIPS_MAX_SZ];
    int size;
    char label;
} Ship;

typedef struct Projectile {
    Coord damage[DAMAGE_MAX_SZ];
    int ammunition;
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

// Modification function
void init_player_state(Player*, const char* name);
void init_boards(GameState*);
void init_ships(GameState*);

#endif  // BATTLESHIP_H
