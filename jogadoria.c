#include <stdio.h>
#include "jogo.h"

void jogaIA(JogadorIA *jogador, Tabuleiro *tab) {
    int l, c;
    int adv;
    int jogou = 0;

    if (jogador->tipo == BOLA) {
    adv = XIS;
} 
    else {
        adv = BOLA;
}

   for (l = 0; l < 3; l++) {
    for (c = 0; c < 3; c++) {
        if (jogou == 0 && tab->M[l][c] == VAZIO) {
            tab->M[l][c] = jogador->tipo;

            if (temVencedor(tab) != VAZIO) {
                jogou = 1;

            } else {
                tab->M[l][c] = VAZIO;
            }
        }
    }
}

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            if (jogou == 0 && tab->M[l][c] == VAZIO) {
                tab->M[l][c] = adv;

                if (temVencedor(tab) != VAZIO) {
                    tab->M[l][c] = jogador->tipo;
                    jogou = 1;
                } else {
                    tab->M[l][c] = VAZIO;
                }
            }
        }
    }

    if (jogou == 0 && tab->M[1][1] == VAZIO) {
        tab->M[1][1] = jogador->tipo;
        jogou = 1;
    }

    if (jogou == 0) {
        if (tab->M[0][0] == VAZIO) {
            tab->M[0][0] = jogador->tipo;
            jogou = 1;
        } else if (tab->M[0][2] == VAZIO) {
            tab->M[0][2] = jogador->tipo;
            jogou = 1;
        } else if (tab->M[2][0] == VAZIO) {
            tab->M[2][0] = jogador->tipo;
            jogou = 1;
        } else if (tab->M[2][2] == VAZIO) {
            tab->M[2][2] = jogador->tipo;
            jogou = 1;
        }
    }

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++) {
            if (jogou == 0 && tab->M[l][c] == VAZIO) {
                tab->M[l][c] = jogador->tipo;
                jogou = 1;
            }
        }
    }
}