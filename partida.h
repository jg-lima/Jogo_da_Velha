#ifndef PARTIDA_H
#define PARTIDA_H

#include "tabuleiro.h"
#include "jogadorteclado.h"
#include "jogadoria.h"

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