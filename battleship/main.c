#include <stdio.h>

#include "src/battleship.h"
#include "src/battleship_io.h"

int main(void) {
    GameState stt;

    init_boards(&stt);
    draw_board(stt.draw_board);
    return 0;
}
