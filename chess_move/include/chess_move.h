#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

// Control data
#define PIECES_LEN 16
#define CB_LEN 8
#define CB_LIMIT 7
#define MAX_DISTANCE 5

enum CardinalIndex {
    N,
    S,
    E,
    W,
    NE,
    NW,
    SE,
    SW,
};

enum PiecesIndex {
    PA_START,
    PA_END = 7,
    RK1,
    KN1,
    BI1,
    QEN,
    KNG,
    BI2,
    KN2,
    RK2,
};

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

void init_chessboard(State* stt);
void init_pieces(State* stt);
void refresh_chessboard(State* stt);
short process_piece_turn(State* stt, short pi);

#endif  // CHESS_MOVE_H
