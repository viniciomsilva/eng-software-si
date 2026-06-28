/**
 * @file main.c
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Main game file (battleship).
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */
#include <stdio.h>

#include "../utils/utils.h"
#include "battleship.h"
#include "battleship_io.h"

#define MAX_PLAYER_NAME_LEN (PLAYER_NAME_SIZE - 1)  // Real size of the player name.

/**
 * @brief Pause the game and display an important message until the user presses
 * any key.
 *
 * @param msg Message to be displayed.
 */
void pause_game(const char* msg) {
    printf("%s", msg);
    printf("     PRESSIONE QUALQUER TECLA PARA CONTINUAR...");
    getchar();
}

int main(void) {
    int option;
    char player_name[PLAYER_NAME_SIZE];
    Coord coord_attack;
    GameState state;

    printf("\n  > DIGITE SEU NOME [ MAX: %d LETRAS ]: ", MAX_PLAYER_NAME_LEN);
    io_read_player_name(player_name);

    init_game_state(&state, player_name);

    do {
        clear();
        io_render(&state);

        if (did_sink_all_ships(&state.player)) {
            set_player_wins(&state.player);
            break;
        }

        if (did_run_out_ammunition(&state.player)) {
            open_all_draw_board(&state);
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

            pause_game("   > ERRO: PROJETIL INVALIDO. \n");
        } while (true);

        if (!state.running) break;

        do {
            printf("   > COORDENADA: ");
            coord_attack = io_read_coord();

            if (validate_coord(coord_attack)) break;

            pause_game("   > ERRO: COORDENADA INVALIDA. \n");
        } while (true);

        if (fire(&state, option, coord_attack)) {
            update_player_score(&state.player, state.ships);
        }
    } while (state.running);

    if (state.running) {
        if (state.player.wins) {
            printf("\n   > GAME WINS: VOCE AFUNDOU TODOS AS EMBARCACOES... \n");
        } else {
            clear();
            io_render(&state);
            printf("\n   > GAME OVER: VOCE GASTOU TODAS NAS MUNICOES... \n");
        }
    }

    pause_game("   > FINALIZANDO... \n");
    return 0;
}
