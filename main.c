#include <stdio.h>
#include "jogo.h"

int main(void)
{
    Partida partida;
    int opcao;

    opcao = 0;

    printf("Jogo da Velha\n");
    printf("1 - Dois jogadores pelo teclado\n");
    printf("2 - Jogador contra maquina\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        configuraJogadores(&partida);
        inicia(&partida);
    } else if (opcao == 2) {
        configuraJogoIA(&partida);
        iniciaJogoIA(&partida);
    } else {
        printf("Opcao invalida.\n");
    }

    return 0;
}
