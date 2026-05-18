#include <stdio.h>

#include "src/game.h"
#include "src/io.h"
#include "src/utils.h"

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

        choice = (short)input_long();

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
