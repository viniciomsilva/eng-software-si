#include <stdio.h>

#include "battleship.h"
#include "battleship_io.h"

int main(void) {
    GameState stt;

    init_boards(&stt);
    init_ships(&stt);

    draw_board(stt.control_board);  // REMEMBER: switch from control_board to draw_board
    return 0;
}
