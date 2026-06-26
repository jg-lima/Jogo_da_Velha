#include <stdio.h>
#include "jogo.h"

void configuraJogadores(Partida *p){
    int escolha = 0;

    printf("Digite '1' para jogar com O ou '4' para jogar com X: ");

    while (escolha != 1 && escolha != 4){
        scanf("%d", &escolha);
        if (escolha != 1 && escolha != 4){
            printf("Escolha inválida, Digite novamente: ");
        }
    }

    if (escolha == 4) {
        p->jogador1.tipo = 4;
        p->jogador2.tipo = 1;

    } else {
        p->jogador1.tipo = 1;
        p->jogador2.tipo = 4;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p->tab.M[i][j] = 0;
        }
}