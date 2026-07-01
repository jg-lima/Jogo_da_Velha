#include "jogadorteclado.h"
#include <stdio.h>

void joga(JogadorTeclado *jogador, Tabuleiro *tab){
    int x = -1, y = -1;
    printf("Digite as coordenadas x e y para sua jogada(exemplo: 1 0 -> x=1 e y=0)");
    scanf("%d %d", &x, &y);

    while (x < 0 || x > 2 || y < 0 || y > 2 || tab->M[x][y] != VAZIO) {
        printf("Jogada invalida! Digite novamente (linha e coluna entre 0 e 2): ");
        scanf("%d %d", &x, &y);
    }

    marcaJogada(tab, x, y, jogador->tipo);
}