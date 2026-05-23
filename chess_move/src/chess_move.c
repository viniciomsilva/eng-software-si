#include "chess_move.h"

#include <stdio.h>
#include <string.h>

#include "chess_move_io.h"

Direction DRTS[8] = {
    { .x = 0,  .y = -1 },  // N
    { .x = 0,  .y = 1  },  // S
    { .x = 1,  .y = 0  },  // E
    { .x = -1, .y = 0  },  // W
    { .x = 1,  .y = -1 },  // NE
    { .x = -1, .y = -1 },  // NW
    { .x = -1, .y = 1  },  // SE
    { .x = 1,  .y = 1  },  // SW
};

// Verification functions
short is_inside(short x, short y) {
    return x >= 0 && x <= CB_LIMIT && y >= 0 && y <= CB_LIMIT;
}

short is_empty(State* stt, short x, short y) {
    return !stt->chessboard[y][x];
}

short is_path_clear(State* stt, short pi, short di, short dist) {
    short x = stt->pieces[pi].x;
    short y = stt->pieces[pi].y;

    for (short i = 0; i < dist; i++) {
        x += DRTS[di].x;
        y += DRTS[di].y;

        if (!is_empty(stt, x, y)) return 0;
    }

    return 1;
}

// Validation functions
short move_piece(State* stt, short pi, short di, short dist) {
    if (dist <= 0 || dist > MAX_DISTANCE) return 0;

    short x = stt->pieces[pi].x;
    short y = stt->pieces[pi].y;

    short nx = x + DRTS[di].x * dist;
    short ny = y + DRTS[di].y * dist;

    if (is_inside(nx, ny) && is_path_clear(stt, pi, di, dist)) {
        set_square_empty(stt, x, y);
        update_piece(&stt->pieces[pi], nx, ny);
        return 1;
    }

    return 0;
}

short move_knight(State* stt, short pi, short fdi, short sdi) {
    short x = stt->pieces[pi].x;
    short y = stt->pieces[pi].y;

    short nx = x + DRTS[fdi].x * 2;
    short ny = y + DRTS[fdi].y * 2;

    if (fdi == N || fdi == S) {
        nx = x + DRTS[sdi].x;
    } else {
        ny = y + DRTS[sdi].y;
    }

    if (is_inside(nx, ny) && is_empty(stt, nx, ny)) {
        set_square_empty(stt, x, y);
        update_piece(&stt->pieces[pi], nx, ny);
        return 1;
    }

    return 0;
}

// Modification functions
void init_chessboard(State* stt) {
    for (short y = 0; y < CB_LEN; y++) {
        for (short x = 0; x < CB_LEN; x++) {
            set_square_empty(stt, x, y);
        }
    }
}

void init_pieces(State* stt) {
    short x = 0;
    short y = CB_LEN - 2;
    char* labels[PIECES_LEN] = {
        "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7", "PA8",  // second-to-last row
        "RK1", "KN1", "BI1", "QEN", "KNG", "BI2", "KN2", "RK2",  // last row
    };

    for (short i = 0; i < PIECES_LEN; i++) {
        strncpy(stt->pieces[i].label, labels[i], 3);
        stt->pieces[i].label[3] = '\0';
        stt->pieces[i].x = x;
        stt->pieces[i].y = y;

        if (x < CB_LIMIT) {  // continue on this row
            x++;
            continue;
        }

        y++;  // move to the next row
        x = 0;
    }
}

void refresh_chessboard(State* stt) {
    for (short i = 0; i < PIECES_LEN; i++) {
        short y = stt->pieces[i].y;
        short x = stt->pieces[i].x;

        stt->chessboard[y][x] = stt->pieces[i].label;
    }
}

void update_piece(Piece* pc, short x, short y) {
    pc->x = x;
    pc->y = y;
}

void set_square_empty(State* stt, short x, short y) {
    stt->chessboard[y][x] = NULL;
}

// Flow control function
short process_piece_turn(State* stt, short pi) {
    if (pi >= PA_START && pi <= PA_END) {
        return move_piece(stt, pi, N, 1);
    }

    short di, dist;

    if (pi == KN1 || pi == KN2) {
        short sdi;

        set_direction_x_or_y(&di);
        set_second_direction(&di, &sdi);

        return move_knight(stt, pi, di, sdi);
    }

    if (pi == RK1 || pi == RK2) {
        set_direction_x_or_y(&di);
    }

    if (pi == BI1 || pi == BI2) {
        set_direction_x_and_y(&di);
    }

    if (pi == QEN || pi == KNG) {
        set_direction_for_all(&di);
    }

    if (pi == KNG) {
        dist = 1;
    } else {
        set_distance(&dist);
    }

    return move_piece(stt, pi, di, dist);
}
