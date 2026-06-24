/**
 * @file main.c
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Main game file (chess move).
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */
#include <stdio.h>

#include "../utils/utils.h"
#include "chess_move.h"
#include "chess_move_io.h"

int main(void) {
    State stt;
    short choice, pi;

    init_chessboard(&stt);
    init_pieces(&stt);

    do {
        refresh_chessboard(&stt);

        clear();
        printf("MOVIMENTACAO DO XADREZ \n\n");
        draw_chessboard(&stt);
        print_pieces_menu(&stt);

        choice = (short)read_long(BUFFER_SIZE, "  DIGITE UM NUMERO: ");

        if (choice == EXIT_GAME) break;

        pi = choice - 1;

        if (pi < PA_START || pi > RK2) {
            printf("\n  OPCAO INVALIDA!");
            printf("\n  PRESSIONE QUALQUER TECLA PARA CONTINUAR.");
            getchar();
            continue;
        }

        printf("> PECA ESCOLHIDA:   %s \n", stt.pieces[pi].label);

        if (!process_piece_turn(&stt, pi)) {
            printf("\n  MOVIMENTO INVALIDO. TENTE NOVAMENTE!");
            getchar();
        }
    } while (choice != EXIT_GAME);

    printf("\n  SAINDO...");
    return 0;
}
