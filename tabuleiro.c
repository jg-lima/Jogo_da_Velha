#include <stdio.h>
#include "jogo.h"

void desenha(Tabuleiro *tab) {
    printf("\n");

    for (int i = 0; i < 3; i++) {
        char simbolos[3];

        for (int j = 0; j < 3; j++) {
            if (tab->M[i][j] == 1) {
                simbolos[j] = 'O';
            } else if (tab->M[i][j] == 4) {
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

int temVencedor(Tabuleiro *tab) {
    int soma;

    for (int l = 0; l < 3; l++) {
        soma = tab->M[l][0] + tab->M[l][1] + tab->M[l][2];
        if (soma == 3 || soma == 12) {
            return soma;
        }
    }

    for (int c = 0; c < 3; c++) {
        soma = tab->M[0][c] + tab->M[1][c] + tab->M[2][c];
        if (soma == 3 || soma == 12) {
            return soma;
        }
    }

    soma = tab->M[0][0] + tab->M[1][1] + tab->M[2][2];
    if (soma == 3 || soma == 12) {
        return soma;
    }

    soma = tab->M[0][2] + tab->M[1][1] + tab->M[2][0];
    if (soma == 3 || soma == 12) {
        return soma;
    }

    return 0;
}