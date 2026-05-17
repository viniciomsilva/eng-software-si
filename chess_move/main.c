#include <stdio.h>

#include "src/game.h"
#include "src/io.h"
#include "src/utils.h"

int main(void) {
    State stt;
    short pi, di, sdi, mov, dist = 0;

    init_chessboard(&stt);
    init_pieces(&stt);

    do {
        refresh_chessboard(&stt);

        clear();
        printf("MOVIMENTACAO DO XADREZ \n\n");
        draw_chessboard(&stt);
        print_pieces_menu(&stt);
        read_short(&pi);
        pi--;

        if (pi >= PA_START && pi <= PA_END) {
            printf("> PECA ESCOLHIDA:   %s \n", stt.pieces[pi].label);
            mov = move_piece(&stt, pi, N, 1);
        } else if (pi == RK1 || pi == RK2) {
            printf("> PECA ESCOLHIDA:   %s \n", stt.pieces[pi].label);
            set_direction_x_or_y(&di);
            set_distance(&dist);
            mov = move_piece(&stt, pi, di, dist);
        } else if (pi == KN1 || pi == KN2) {
            printf("> PECA ESCOLHIDA:   %s \n", stt.pieces[pi].label);
            set_direction_x_or_y(&di);
            set_second_direction(&di, &sdi);
            mov = move_knight(&stt, pi, di, sdi);
        } else if (pi == BI1 || pi == BI2) {
            printf("> PECA ESCOLHIDA:   %s \n", stt.pieces[pi].label);
            set_direction_x_and_y(&di);
            set_distance(&dist);
            mov = move_piece(&stt, pi, di, dist);
        } else if (pi == QEN || pi == KNG) {
            printf("> PECA ESCOLHIDA:   %s \n", stt.pieces[pi].label);
            set_direction_for_all(&di);

            if (pi == QEN)
                set_distance(&dist);
            else
                dist = 1;

            mov = move_piece(&stt, pi, di, dist);
        } else if (pi == EXIT_GAME) {
            printf("\nSAINDO...");
            break;
        } else {
            printf("\nOPCAO INVALIDA! PRESSIONE QUALQUER TECLA PARA CONTINUAR.");
            getchar();
            continue;
        }

        if (!mov) {
            printf("\nMOVIMENTO INVALIDO. TENTE NOVAMENTE!");
            getchar();
        }
    } while (pi != EXIT_GAME);

    return 0;
}
