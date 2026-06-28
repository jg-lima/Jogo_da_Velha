#ifndef JOGO_H
#define JOGO_H

#define VAZIO 0
#define BOLA 1
#define XIS 4
#define EMPATE 2
#define VITORIA_BOLA 3
#define VITORIA_XIS 12

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
    int tipo;
} JogadorIA;

void jogaIA(JogadorIA *jogador, Tabuleiro *tab);

typedef struct {
    Tabuleiro tab;
    JogadorTeclado jogador1; 
    JogadorTeclado jogador2;
    JogadorTeclado jogadorHumano;
    JogadorIA jogadorIA;
    int modo;
} Partida;

void configuraJogadores(Partida *p);
void inicia(Partida *p);

#endif
