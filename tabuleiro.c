#include <stdio.h>
#include "tabuleiro.h"

void desenha(Tabuleiro *tab) {
    printf("\033[2J\033[H");

    for (int i = 0; i < 3; i++) {
        char simbolos[3];

        for (int j = 0; j < 3; j++) {
            if (tab->M[i][j] == BOLA) {
                simbolos[j] = 'O';
            } else if (tab->M[i][j] == XIS) {
                simbolos[j] = 'X';
            } else {
                simbolos[j] = ' '; 
            }
        }

        printf(" %c | %c | %c \n", simbolos[0], simbolos[1], simbolos[2]);

        if (i < 2) {
            printf("___|___|___\n");
        } else {
            printf("   |   |   \n");
        }  
    }
}
void marcaJogada(Tabuleiro *tab, int x, int y, int tipo) {
    if (x >= 0 && x <= 2 && y >= 0 && y <= 2 && tab->M[x][y] == VAZIO) {
        tab->M[x][y] = tipo;
    }
}

int temVencedor(Tabuleiro *tab)
{
    int soma, cheio = 1;

    for (int l = 0; l < 3; l++) {
        soma = tab->M[l][0] + tab->M[l][1] + tab->M[l][2];
        if (soma == VITORIA_BOLA || soma == VITORIA_XIS) {
            return soma;
        }
    }

    for (int c = 0; c < 3; c++) {
        soma = tab->M[0][c] + tab->M[1][c] + tab->M[2][c];
        if (soma == VITORIA_BOLA || soma == VITORIA_XIS) {
            return soma;
        }
    }

    soma = tab->M[0][0] + tab->M[1][1] + tab->M[2][2];
    if (soma == VITORIA_BOLA || soma == VITORIA_XIS) {
        return soma;
    }

    soma = tab->M[0][2] + tab->M[1][1] + tab->M[2][0];
    if (soma == VITORIA_BOLA || soma == VITORIA_XIS) {
        return soma;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tab->M[i][j] == VAZIO) {
                cheio = 0;
            }
        }
    }
    if (cheio == 1) {
        return EMPATE;
    }

    return VAZIO;
}
