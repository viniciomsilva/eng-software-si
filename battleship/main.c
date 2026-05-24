#include <stdio.h>

#include "battleship.h"
#include "battleship_io.h"

int main(void) {
    GameState stt;

    init_boards(&stt);
    draw_board(stt.draw_board);
    return 0;
}
