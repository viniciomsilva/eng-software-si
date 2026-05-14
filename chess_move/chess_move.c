#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 24
#define PIECES_LEN 16
#define CB_LEN 8

#ifdef _WIN32
#define CLS_CMD "cls"
#else
#define CLS_CMD "clear"
#endif

// Data Structs
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
short is_path_clear(State* stt, short x, short y);  // TODO: Implementation

// Validation functions;
short move_pawn(State* stt, short i);
short move_rook(State* stt, short i);    // TODO: Implementation
short move_knight(State* stt, short i);  // TODO: Implementation
short move_bishop(State* stt, short i);  // TODO: Implementation
short move_queen(State* stt, short i);   // TODO: Implementation
short move_king(State* stt, short i);    // TODO: Implementation

// Modification functions;
void init(State* stt);
void update_stt(State* stt);
void update_piece(Piece* pc, short x, short y);
void set_square_empty(State* stt, short x, short y);

// Output functions
void clear(void);
void draw(State* stt);

// Main function
int main(void) {
    short opt = 0;
    short mov = 0;
    char buffer[BUFFER_SIZE];
    State stt;

    init(&stt);

    do {
        update_stt(&stt);

        clear();
        printf("MOVIMENTACAO DO XADREZ \n\n");
        draw(&stt);

        // Main menu
        for (short i = 0; i < PIECES_LEN; i++) {
            printf("[ %2d ] %s  ", i + 1, stt.pieces[i].label);
            if (!((i + 1) % 4)) printf("\n");
        }
        printf("[ 99 ] SAIR ");
        printf("\n\n> ESCOLHA UMA OPCAO: ");

        fgets(buffer, sizeof(buffer), stdin);
        opt = (short)strtol(buffer, NULL, 10);

        if (opt >= 1 && opt <= 8) {  // Move Pawns
            mov = move_pawn(&stt, opt - 1);
        } else if (opt == 9 || opt == 16) {  // TODO: Move Rooks
            /* code */
        } else if (opt == 10 || opt == 15) {  // TODO: Move Rights
            /* code */
        } else if (opt == 11 || opt == 14) {  // TODO: Move Bishops
            /* code */
        } else if (opt == 12) {  // TODO: Move Queen
            /* code */
        } else if (opt == 13) {  // TODO: Move King
            /* code */
        } else if (opt == 99) {
            mov = 1;
            printf("\nSAINDO...");
        } else {
            mov = 1;
            printf("OPCAO INVALIDA! PRESSIONE QUALQUER TECLA PARA CONTINUAR.");
            getchar();
        }

        if (!mov) {
            printf("MOVIMENTO INVALIDO! TENTE NOVAMENTE!");
            getchar();
        }
    } while (opt != 99);

    return 0;
}

// Implementation: Verification functions
short is_inside(short x, short y) { return x >= 0 && x < CB_LEN && y >= 0 && y < CB_LEN; }

short is_empty(State* stt, short x, short y) { return stt->chessboard[y][x] == NULL; }

// Implementation: Validation functions
short move_pawn(State* stt, short i) {
    short y = stt->pieces[i].y;
    short x = stt->pieces[i].x;
    short ny = y - 1;

    if (is_inside(x, ny) && is_empty(stt, x, ny)) {
        set_square_empty(stt, x, y);
        update_piece(&stt->pieces[i], x, ny);
        // stt->chessboard[y][x] = NULL;
        // stt->pieces[i].y = ny;
        return 1;
    }

    return 0;
};

// Implementation: Modification functions
void init(State* stt) {
    for (short y = 0; y < CB_LEN; y++) {
        for (short x = 0; x < CB_LEN; x++) {
            set_square_empty(stt, x, y);
        }
    }

    stt->pieces[0] = (Piece){.label = "PA1", .x = 0, .y = 6};
    stt->pieces[1] = (Piece){.label = "PA2", .x = 1, .y = 6};
    stt->pieces[2] = (Piece){.label = "PA3", .x = 2, .y = 6};
    stt->pieces[3] = (Piece){.label = "PA4", .x = 3, .y = 6};
    stt->pieces[4] = (Piece){.label = "PA5", .x = 4, .y = 6};
    stt->pieces[5] = (Piece){.label = "PA6", .x = 5, .y = 6};
    stt->pieces[6] = (Piece){.label = "PA7", .x = 6, .y = 6};
    stt->pieces[7] = (Piece){.label = "PA8", .x = 7, .y = 6};
    stt->pieces[8] = (Piece){.label = "RK1", .x = 0, .y = 7};
    stt->pieces[9] = (Piece){.label = "KN1", .x = 1, .y = 7};
    stt->pieces[10] = (Piece){.label = "BI1", .x = 2, .y = 7};
    stt->pieces[11] = (Piece){.label = "QEN", .x = 3, .y = 7};
    stt->pieces[12] = (Piece){.label = "KNG", .x = 4, .y = 7};
    stt->pieces[13] = (Piece){.label = "BI2", .x = 5, .y = 7};
    stt->pieces[14] = (Piece){.label = "KN2", .x = 6, .y = 7};
    stt->pieces[15] = (Piece){.label = "RK2", .x = 7, .y = 7};
}

void update_stt(State* stt) {
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

void set_square_empty(State* stt, short x, short y) { stt->chessboard[y][x] = NULL; }

// Implementation: Output functions
void clear(void) { system(CLS_CMD); }

void draw(State* stt) {
    for (short y = 0; y < CB_LEN; y++) {
        printf("%d - ", CB_LEN - y);
        for (short x = 0; x < CB_LEN; x++) {
            char* content = stt->chessboard[y][x];
            printf(" %s ", (content) ? content : "   ");
            if (x < CB_LEN - 1) printf("|");
        }
        printf("\n");
    }
    printf("      a     b     c     d     e     f     g     h  \n");
    printf("---------------------------------------------------\n\n");
}
