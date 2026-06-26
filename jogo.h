#ifndef JOGO_H
#define JOGO_H

typedef struct { 
    int M[3][3];
} Tabuleiro;

void desenha(Tabuleiro *tab);
int temVencedor(Tabuleiro *tab);
void marcaJogada(Tabuleiro *tab, int x, int y, int tipo);

typedef struct {
    int tipo;
} JogadorTeclado;

void joga(JogadorTeclado *jogador, Tabuleiro *tab);

typedef struct {
    Tabuleiro tab;
    JogadorTeclado jogador1; 
    JogadorTeclado jogador2;
} Partida;

void configuraJogadores(Partida *p);
void inicia(Partida *p);

#endif