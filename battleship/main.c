#include <stdio.h>
#include <string.h>

#include "battleship.h"
#include "battleship_io.h"

int main(void) {
    GameState stt;
    char player_name[PLAYER_NAME_SZ];

    init_boards(&stt);
    init_ships(&stt);

    printf("\n  > DIGITE SEU NOME [ MAX: %d LETRAS ]: ", (PLAYER_NAME_SZ - 1));
    read_player_name(player_name);
    init_player_state(&stt.player, player_name);

    render(&stt);
    return 0;
}
