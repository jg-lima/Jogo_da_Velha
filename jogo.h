#ifndef JOGO_H
#define JOGO_H

typedef enum {
    VAZIO = 0,
    BOLA = 1,
    EMPATE = 2,
    VITORIA_BOLA = 3,
    XIS = 4,
    VITORIA_XIS = 12
} EstadoJogo;

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
