#include <stdbool.h>
#include <stdio.h>

#include "../utils/utils.h"
#include "battleship.h"
#include "battleship_io.h"

void pause_game(const char* msg) {
    printf("   > ERRO: %s \n", msg);
    printf("     PRESSIONE QUALQUER TECLA PARA CONTINUAR...");
    getchar();
}

int main(void) {
    int option;
    char player_name[PLAYER_NAME_SIZE];
    Coord coord_attack;
    GameState state;

    printf("\n  > DIGITE SEU NOME [ MAX: %d LETRAS ]: ", (PLAYER_NAME_SIZE - 1));
    read_player_name(player_name);

    init_game_state(&state, player_name);

    do {
        clear();
        render(&state);

        if (did_sink_all_ships(&state.player)) {
            printf("   > GAME WINS: VOCE AFUNDOU TODOS AS EMBARCACOES... \n");
            break;
        }

        if (did_run_out_ammunition(&state.player)) {
            printf("   > GAME OVER: VOCE GASTOU TODAS NAS MUNICOES... \n");
            break;
        }

        printf("\n   ATACAR \n");

        do {
            printf("   > PROJETIL..: ");
            option = (int)read_long(BUFFER_SIZE, "   > DIGITE UM NUMERO..: ");

            if (option == EXIT_OPTION) {
                finish_game(&state);
                break;
            }

            if (validate_projectile(state.player.arsenal, --option)) break;

            pause_game("PROJETIL INVALIDO.");
        } while (true);

        if (!state.running) break;

        do {
            printf("   > COORDENADA: ");
            coord_attack = read_coord();

            if (validate_coord(coord_attack)) break;

            pause_game("COORDENADA INVALIDA.");
        } while (true);

        if (fire(&state, option, coord_attack)) {
            update_player_score(&state.player, state.ships);
        }
    } while (state.running);

    printf("   > FINALIZANDO...");
    return 0;
}
