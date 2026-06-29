#include <stdio.h>
#include "jogo.h"

void jogaIA(JogadorIA *jogador, Tabuleiro *tab) {
    int l, c, jogou = 0;
    int adv;

    if (jogador->tipo == XIS) {
        adv = BOLA;
    } 
    else {
    adv = XIS;
    }

    int tipos[] = {jogador->tipo, adv};
    for (int t = 0; t < 2 && jogou != 1; t++) {
        for (l = 0; l < 3 && jogou != 1; l++) {
            for (c = 0; c < 3 && jogou != 1; c++) {
                if (tab->M[l][c] == VAZIO) {
                    tab->M[l][c] = tipos[t];

                    if (temVencedor(tab) != VAZIO) {
                        tab->M[l][c] = jogador->tipo;
                        jogou = 1;
                    } 
                    else {
                        tab->M[l][c] = VAZIO;
                    }
                }
            }
        }
    }

    if (jogou != 1) {
        for (l = 0; l < 3 && jogou != 1; l++) {
            for (c = 0; c < 3 && jogou != 1; c++) {
                if (tab->M[l][c] == VAZIO) {
                    tab->M[l][c] = jogador->tipo;
                    
                    int total = 0;
                    if (total >= 2) jogou = 1;
                    else tab->M[l][c] = VAZIO;
                }
            }
        }
    }

    if (!jogou && tab->M[1][1] == VAZIO) {
        tab->M[1][1] = jogador->tipo;
        jogou = 1;
    }

    if (jogou != 1) {
        if (tab->M[0][0] == adv && tab->M[2][2] == VAZIO){
             tab->M[2][2] = jogador->tipo; jogou = 1; 
            }

        else if (tab->M[2][2] == adv && tab->M[0][0] == VAZIO){
             tab->M[0][0] = jogador->tipo; jogou = 1; 
            }

        else if (tab->M[0][2] == adv && tab->M[2][0] == VAZIO){
             tab->M[2][0] = jogador->tipo; jogou = 1; 
            }

        else if (tab->M[2][0] == adv && tab->M[0][2] == VAZIO){
             tab->M[0][2] = jogador->tipo; jogou = 1;
             }
    }

    if (jogou != 1) {
        int cantos[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
        for(int i=0; i<4 && jogou != 1; i++) {
            if (tab->M[cantos[i][0]][cantos[i][1]] == VAZIO) {
                tab->M[cantos[i][0]][cantos[i][1]] = jogador->tipo;
                jogou = 1;
            }
        }
    }

    for (l = 0; l < 3 && jogou != 1; l++) {
        for (c = 0; c < 3 && jogou != 1; c++) {
            if (tab->M[l][c] == VAZIO) {
                tab->M[l][c] = jogador->tipo;
                jogou = 1;
            }
        }
    }
}