#ifndef TABULEIRO_H
#define TABULEIRO_H

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

#endif