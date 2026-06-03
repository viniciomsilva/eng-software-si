#include <stdio.h>
#include <string.h>

#include "../utils/utils.h"
#include "battleship.h"
#include "battleship_io.h"

int main(void) {
    char player_name[PLAYER_NAME_SZ];
    GameState stt;

    printf("\n  > DIGITE SEU NOME [ MAX: %d LETRAS ]: ", (PLAYER_NAME_SZ - 1));
    read_player_name(player_name);

    init_boards(&stt);
    init_ships(&stt);
    init_player_state(&stt.player, player_name);

    while (1) {
        clear();
        render(&stt);

        printf("\n   ATACAR");
        printf("\n   > PROJETIL..: ");

        int opt = (int)read_long(BUFFER_SZ, "   > DIGITE UM NUMERO..: ");

        if (opt == EXIT_OPT) break;

        printf("   > COORDENADA: ");
        Coord coord_attack = read_coord();

        putchar('\n');
        printf("Coord: { .x = %d, .y = %d }", coord_attack.x, coord_attack.y);
        getchar();
    }

    printf("   > FINALIZANDO...");
    return 0;
}
