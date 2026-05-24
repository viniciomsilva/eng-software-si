#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define BOARD_SIZE 10
#define VESSEL_MAX_SIZE 5

typedef struct VesselCoord {
    int x;
    int y;
    int hit;
} VesselCoord;

typedef struct Vessel {
    VesselCoord coords[VESSEL_MAX_SIZE];
    int size;
    char label;
} Vessel;

typedef struct GameState {
    char control_board[BOARD_SIZE][BOARD_SIZE];
    char draw_board[BOARD_SIZE][BOARD_SIZE];
} GameState;

extern const char COLUMNS[BOARD_SIZE];

// Modification function
void init_boards(GameState*);

#endif  // BATTLESHIP_H
