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

void inicializaTabuleiro(Tabuleiro *tab);
void desenha(Tabuleiro *tab);
int temVencedor(Tabuleiro *tab);
int tabuleiroCheio(Tabuleiro *tab);
int posicaoValida(Tabuleiro *tab, int x, int y);
void marcaJogada(Tabuleiro *tab, int x, int y, int tipo);

typedef struct {
    int tipo;
} JogadorTeclado;

void joga(JogadorTeclado *jogador, Tabuleiro *tab);
void jogaComRetorno(JogadorTeclado *jogador, Tabuleiro *tab, int *linha, int *coluna);

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
} Partida;

void configuraJogadores(Partida *p);
void configuraJogoIA(Partida *p);
void inicia(Partida *p);
void iniciaJogoIA(Partida *p);

typedef struct {
    int socket;
    int tipo;
} JogadorRemoto;

int conecta(char ip[], int porta);
int aceita(int porta);
void enviaJogada(JogadorRemoto *jogador, int linha, int coluna);
void recebeJogada(JogadorRemoto *jogador, Tabuleiro *tab);

#endif
