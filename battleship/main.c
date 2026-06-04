#include <stdio.h>
#include <string.h>

#include "../utils/utils.h"
#include "battleship.h"
#include "battleship_io.h"

void pause_game(const char* msg) {
    printf(msg);
    printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR...");
    getchar();
}

int main(void) {
    int opt;
    char player_name[PLAYER_NAME_SZ];
    GameState stt;
    Coord coord_attack;

    printf("\n  > DIGITE SEU NOME [ MAX: %d LETRAS ]: ", (PLAYER_NAME_SZ - 1));
    read_player_name(player_name);

    init_game_state(&stt, player_name);

    while (1) {
        clear();
        render(&stt);

        printf("\n   ATACAR \n");

        do {
            printf("   > PROJETIL..: ");
            opt = (int)read_long(BUFFER_SZ, "   > DIGITE UM NUMERO..: ");

            if (opt == EXIT_OPT) goto finish;

            if (validate_proj(--opt)) break;

            pause_game("   > ERRO: PROJETIL INVALIDO. ");
        } while (1);

        do {
            printf("   > COORDENADA: ");
            coord_attack = read_coord();

            if (validate_coord(coord_attack)) break;

            pause_game("   > ERRO: COORDENADA INVALIDA. ");
        } while (1);

        if (fire(&stt, opt, coord_attack)) {
            update_player_score(&stt.player, stt.ships);
        }
    }

finish:
    printf("   > FINALIZANDO...");
    return 0;
}
