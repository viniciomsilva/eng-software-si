/**
 * @file chess_move.h
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Definitions of the structures and functions for state management and
 * business rule validation in the game.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#define PIECES_LEN 16          // Number of chess pieces.
#define CB_LEN 8               // Size of the chessboard.
#define CB_LIMIT (CB_LEN - 1)  // Last position of the chessboard.

/**
 * @enum CardinalIndex
 * @brief Indices for piece movement directions.
 *
 */
enum CardinalIndex {
    N,  /**< Index: movement to the north (on the vertical axis). */
    S,  /**< Index: movement to the south (on the vertical axis). */
    E,  /**< Index: movement to the east (on the horizontal axis). */
    W,  /**< Index: movement to the west (on the horizontal axis). */
    NE, /**< Index: movement to the northeast (diagonally). */
    NW, /**< Index: movement to the northwest (diagonally). */
    SE, /**< Index: movement to the southeast (diagonally). */
    SW, /**< Index: movement to the southwest (diagonally). */
};

/**
 * @enum PiecesIndex
 * @brief Indices of the chess pieces.
 *
 */
enum PiecesIndex {
    PA_START,   /**< Index: first pawn. */
    PA_END = 7, /**< Index: last pawn. */
    RK1,        /**< Index: first rook. */
    KN1,        /**< Index: first knight. */
    BI1,        /**< Index: first bishop. */
    QEN,        /**< Index: queen. */
    KNG,        /**< Index: king. */
    BI2,        /**< Index: second bishop. */
    KN2,        /**< Index: second knight. */
    RK2,        /**< Index: second rook. */
};

/**
 * @struct Direction
 * @brief Structures the coordinates for pieces movement directions.
 *
 * Since the chessboard is a two-dimensional matrix, the movement directions are
 * Cartesian coordinate, where x indicates the row and y indicates de column.
 *
 */
typedef struct Direction {
    short x; /**< Position in the matrix row. X-axis. */
    short y; /**< Position in the matrix column. Y-axis. */
} Direction;

/**
 * @struct Piece
 * @brief Structure representing a chess piece.
 *
 * Each piece stores its square (Cartesian position in the matrix) x and y, as
 * well as its label.
 *
 */
typedef struct Piece {
    short x;       /**< Position in the matrix row. X-axis. */
    short y;       /**< Position in the matrix column. Y-axis. */
    char label[4]; /**< Piece's label. Ex.: King => KNG */
} Piece;

/**
 * @struct State
 * @brief Struture representing the game state.
 *
 * Stores the state of the chessboard and the state of the pieces.
 *
 */
typedef struct State {
    char* chessboard[CB_LEN][CB_LEN]; /**< Matrix of strings representing the chessboard. */
    Piece pieces[PIECES_LEN];         /**< Array of pieces. */
} State;

/**
 * @brief Initializes the chessboard state, iterating through the strings matrix
 * and setting each square [y][x] as an empty string.
 *
 * @param stt Pointer to the game state.
 *
 */
void init_chessboard(State* stt);

/**
 * @brief Initializes the state of the pieces, defining their squares on the
 * board and their labels.
 *
 * Considering the perspective of the white pieces on the real 8x8 chess board,
 * the pieces occupy rows 1 and 2 from bottom to top, with row 2 being entirely
 * occupied by the 8 pawns.
 * To mimic the layout of a real chessboard, where rows are counted from bottom
 * to top and the matrix is rendered from top to bottom, the pieces start
 * receiving row position 6 in the matrix.
 * When iterating through the pieces array, each piece receives its position in
 * the matrix and the label corresponding to that piece on that specific square
 * of the real chessboard.
 *
 * @param stt Pointer to the game state.
 */
void init_pieces(State* stt);

/**
 * @brief Updates the chessboard state based on the pieces' state, iterating
 * through the pieces array and copying their labels to the corresponding square
 * on the chessboard.
 *
 * @param stt Pointer to the game state.
 *
 */
void refresh_chessboard(State* stt);

/**
 * @brief Processes the movement of each piece according to the game's business
 * rules. The rules are as follows:
 *
 * > Pawns: only one square north and cannot move backward;
 *
 * > Knights: L-shaped movement, can jump over other pieces;
 *
 * > Rooks: up to five squares vertically or horizontally;
 *
 * > Bishops: up to five squares diagonally;
 *
 * > Queen: up to five squares in the any direction;
 *
 * > King: only one square in the any direction.
 *
 * The input values are validated according to the movement rules of the pieces
 * and the chessboard boundaries. If the move is validated and executed, it
 * return 1.
 *
 * @param stt Pointer to the game state.
 * @param pi Piece index.
 * @return short 1 for true and 0 for false.
 */
short process_piece_turn(State* stt, short pi);

#endif  // CHESS_MOVE_H
