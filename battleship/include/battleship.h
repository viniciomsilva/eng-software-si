#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define BOARD_SZ 10
#define SHIPS_QTY 5
#define SHIPS_MAX_SZ 5

typedef struct Coord {
    int x;
    int y;
    // int hit;
} Coord;

typedef struct Ship {
    // Coord coords[SHIPS_MAX_SZ];
    int size;
    char label;
} Ship;

typedef struct GameState {
    Ship ships[SHIPS_QTY];
    char control_board[BOARD_SZ][BOARD_SZ];
    char draw_board[BOARD_SZ][BOARD_SZ];
} GameState;

// Modification function
void init_boards(GameState*);
void init_ships(GameState*);

#endif  // BATTLESHIP_H
