#include "battleship.h"

const char COLUMNS[BOARD_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

// Modification functions
void init_boards(GameState* stt) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            stt->control_board[y][x] = '\0';
            stt->draw_board[y][x] = '\0';
        }
    }
}
