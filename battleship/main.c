#include <stdio.h>
#include <string.h>

#include "battleship.h"
#include "battleship_io.h"

int main(void) {
    GameState stt;

    init_boards(&stt);
    init_ships(&stt);

    init_player_state(&stt.player, "GAMER_NAME");

    render(&stt);
    return 0;
}
