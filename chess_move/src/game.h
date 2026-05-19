#ifndef GAME_H
#define GAME_H

// Control data
#define PIECES_LEN 16
#define CB_LEN 8
#define CB_LIMIT 7
#define MAX_DISTANCE 5

enum CardinalIndex { N, S, E, W, NE, NW, SE, SW };

enum PiecesIndex { PA_START, PA_END = 7, RK1, KN1, BI1, QEN, KNG, BI2, KN2, RK2 };

// Structure data
typedef struct Direction {
    short x;
    short y;
} Direction;

typedef struct Piece {
    short x;
    short y;
    char label[4];
} Piece;

typedef struct State {
    char* chessboard[CB_LEN][CB_LEN];
    Piece pieces[PIECES_LEN];
} State;

// Verification functions
short is_inside(short x, short y);
short is_empty(State* stt, short x, short y);
short is_path_clear(State* stt, short pi, short di, short dist);

// Validation functions
short move_piece(State* stt, short pi, short di, short dist);
short move_knight(State* stt, short pi, short fdi, short sdi);

// Modification functions
void init_chessboard(State* stt);
void init_pieces(State* stt);
void refresh_chessboard(State* stt);
void update_piece(Piece* pc, short x, short y);
void set_square_empty(State* stt, short x, short y);

// Flow control function
short process_piece_turn(State* stt, short pi);

#endif  // GAME_H
