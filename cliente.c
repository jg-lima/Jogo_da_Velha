#include <stdio.h>
#include <unistd.h>
#include "jogo.h"

#define PORTA 8080

int main(void)
{
    Tabuleiro tab;
    JogadorTeclado jogadorLocal;
    JogadorRemoto jogadorRemoto;
    int linha, coluna;
    int resultado;

    inicializaTabuleiro(&tab);

    jogadorLocal.tipo = BOLA;
    jogadorRemoto.tipo = XIS;
    jogadorRemoto.socket = conecta("127.0.0.1", PORTA);

    resultado = VAZIO;

    while (resultado == VAZIO) {
        desenha(&tab);
        printf("Aguardando jogada remota...\n");
        recebeJogada(&jogadorRemoto, &tab);
        resultado = temVencedor(&tab);

        if (resultado == VAZIO) {
            desenha(&tab);
            jogaComRetorno(&jogadorLocal, &tab, &linha, &coluna);
            enviaJogada(&jogadorRemoto, linha, coluna);
            resultado = temVencedor(&tab);
        }
    }

    desenha(&tab);

    if (resultado == EMPATE) {
        printf("Empate!\n");
    } else if (resultado == VITORIA_BOLA) {
        printf("Vencedor: O\n");
    } else if (resultado == VITORIA_XIS) {
        printf("Vencedor: X\n");
    }

    close(jogadorRemoto.socket);
    return 0;
}
