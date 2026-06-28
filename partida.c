#include <stdio.h>
#include <time.h>
#include "jogo.h"

void configuraJogadores(Partida *p) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p->tab.M[i][j] = VAZIO;
        }
    }
    p->modo = 0;
    printf("    MODO DE JOGO    \n");
    printf("1 - Dois jogadores (Teclado)\n");
    printf("2 - Contra a Maquina (IA)\n");
    while (p->modo != 1 && p->modo != 2) {
        scanf("%d", &p->modo);
        if (p->modo != 1 && p->modo != 2) printf("Opcao invalida. Digite 1 ou 2: ");
    }
    int escolha = 0;
    printf("\nJogador 1, digite 1 para O ou 4 para X: ");
    while (escolha != BOLA && escolha != XIS) {
        scanf("%d", &escolha);
        if (escolha != BOLA && escolha != XIS) {
            printf("Escolha invalida. Digite 1 ou 4: ");
        }
    }

    int tipoAdv;
    if (escolha == BOLA) {
        tipoAdv = XIS;
} 
    else {
        tipoAdv = BOLA;
}   
    if (p->modo == 1) {
        p->jogador1.tipo = escolha;
        p->jogador2.tipo = tipoAdv;
    } else {
        p->jogadorHumano.tipo = escolha;
        p->jogadorIA.tipo = tipoAdv;
    }
}
void inicia(Partida *p) {
    int resultado = VAZIO;
    if (p->modo == 1) {
        JogadorTeclado *atual = &p->jogador1;

        while (resultado == VAZIO) {
            desenha(&p->tab);
            if (atual == &p->jogador1) printf("   JOGADOR 1   \n");
            else printf("   JOGADOR 2   \n");

            joga(atual, &p->tab);
            resultado = temVencedor(&p->tab);
            atual = (atual == &p->jogador1) ? &p->jogador2 : &p->jogador1;
        }

        desenha(&p->tab);
        if (resultado == EMPATE) printf("Deu Velha! Empate!\n");
        else if (resultado == p->jogador1.tipo) printf("Fim de Jogo! Vencedor: Jogador 1!\n");
        else printf("Fim de Jogo! Vencedor: Jogador 2!\n");

    } else {
        
        int turnoDaIA = 1; 
        
        while (resultado == VAZIO) {
            desenha(&p->tab);
            
            if (turnoDaIA == 1) {
                printf("   IA   \n");
                printf("Pensando...\n");
                time_t inicio = time(NULL);
                while (time(NULL) - inicio < 2);

                jogaIA(&p->jogadorIA, &p->tab);
                turnoDaIA = 0;
            } else {
                printf("   JOGADOR 1   \n");
                joga(&p->jogadorHumano, &p->tab);
                turnoDaIA = 1;
            }       
            resultado = temVencedor(&p->tab);
        }
        desenha(&p->tab);
        if (resultado == EMPATE) printf("Deu Velha! Empate!\n");
        else if (resultado == p->jogadorHumano.tipo) printf("Fim de Jogo! Vencedor: Jogador 1!\n");
        else printf("Fim de Jogo! Vencedor: IA!\n");
    }
}