#include <stdio.h>
#include "jogo.h"

void inicializaTabuleiro(Tabuleiro *tab)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tab->M[i][j] = VAZIO;
        }
    }
}

void desenha(Tabuleiro *tab)
{
    int i, j;
    char simbolos[3];

    printf("\033[2J\033[H");
    printf("Linhas e colunas de 1 a 3\n\n");

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
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

    printf("\n");
}

int tabuleiroCheio(Tabuleiro *tab)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tab->M[i][j] == VAZIO) {
                return 0;
            }
        }
    }

    return 1;
}

int temVencedor(Tabuleiro *tab)
{
    int soma;
    int l, c;

    for (l = 0; l < 3; l++) {
        soma = tab->M[l][0] + tab->M[l][1] + tab->M[l][2];
        if (soma == VITORIA_BOLA || soma == VITORIA_XIS) {
            return soma;
        }
    }

    for (c = 0; c < 3; c++) {
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

    if (tabuleiroCheio(tab) == 1) {
        return EMPATE;
    }

    return VAZIO;
}

int posicaoValida(Tabuleiro *tab, int x, int y)
{
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        return 0;
    }

    if (tab->M[x][y] != VAZIO) {
        return 0;
    }

    return 1;
}

void marcaJogada(Tabuleiro *tab, int x, int y, int tipo)
{
    if (posicaoValida(tab, x, y) == 1) {
        tab->M[x][y] = tipo;
    }
}
