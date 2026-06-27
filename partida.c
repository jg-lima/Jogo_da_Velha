#include <stdio.h>
#include "jogo.h"

int tipoAdversario(int tipo)
{
    if (tipo == BOLA) {
        return XIS;
    }

    return BOLA;
}

char simboloJogador(int tipo)
{
    if (tipo == BOLA) {
        return 'O';
    }

    return 'X';
}

void limpaEntrada(void)
{
    char c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void mostraResultado(int resultado)
{
    if (resultado == EMPATE) {
        printf("Empate!\n");
    } else if (resultado == VITORIA_BOLA) {
        printf("Vencedor: O\n");
    } else if (resultado == VITORIA_XIS) {
        printf("Vencedor: X\n");
    }
}

void configuraJogadores(Partida *p)
{
    int escolha;

    inicializaTabuleiro(&p->tab);
    escolha = 0;

    printf("Jogador 1, digite 1 para jogar com O ou 4 para jogar com X: ");

    while (escolha != BOLA && escolha != XIS) {
        if (scanf("%d", &escolha) != 1) {
            limpaEntrada();
            escolha = 0;
        }

        if (escolha != BOLA && escolha != XIS) {
            printf("Escolha invalida. Digite novamente: ");
        }
    }

    p->jogador1.tipo = escolha;
    p->jogador2.tipo = tipoAdversario(escolha);
}

void configuraJogoIA(Partida *p)
{
    int escolha;

    inicializaTabuleiro(&p->tab);
    escolha = 0;

    printf("Digite 1 para jogar com O ou 4 para jogar com X: ");

    while (escolha != BOLA && escolha != XIS) {
        if (scanf("%d", &escolha) != 1) {
            limpaEntrada();
            escolha = 0;
        }

        if (escolha != BOLA && escolha != XIS) {
            printf("Escolha invalida. Digite novamente: ");
        }
    }

    p->jogadorHumano.tipo = escolha;
    p->jogadorIA.tipo = tipoAdversario(escolha);
}

void jogaComRetorno(JogadorTeclado *jogador, Tabuleiro *tab, int *linha, int *coluna)
{
    int l, c;
    int leitura;

    leitura = 0;
    l = 0;
    c = 0;

    while (leitura != 2 || posicaoValida(tab, l - 1, c - 1) == 0) {
        printf("Jogador %c, digite linha e coluna: ", simboloJogador(jogador->tipo));
        leitura = scanf("%d %d", &l, &c);

        if (leitura != 2) {
            limpaEntrada();
            printf("Entrada invalida.\n");
        } else if (posicaoValida(tab, l - 1, c - 1) == 0) {
            printf("Jogada invalida.\n");
        }
    }

    marcaJogada(tab, l - 1, c - 1, jogador->tipo);
    *linha = l - 1;
    *coluna = c - 1;
}

void joga(JogadorTeclado *jogador, Tabuleiro *tab)
{
    int linha, coluna;

    jogaComRetorno(jogador, tab, &linha, &coluna);
}

int procuraSequencia(Tabuleiro *tab, int tipo, int *linha, int *coluna)
{
    int i, j, soma;

    for (i = 0; i < 3; i++) {
        soma = tab->M[i][0] + tab->M[i][1] + tab->M[i][2];
        if (soma == tipo * 2) {
            for (j = 0; j < 3; j++) {
                if (tab->M[i][j] == VAZIO) {
                    *linha = i;
                    *coluna = j;
                    return 1;
                }
            }
        }
    }

    for (i = 0; i < 3; i++) {
        soma = tab->M[0][i] + tab->M[1][i] + tab->M[2][i];
        if (soma == tipo * 2) {
            for (j = 0; j < 3; j++) {
                if (tab->M[j][i] == VAZIO) {
                    *linha = j;
                    *coluna = i;
                    return 1;
                }
            }
        }
    }

    soma = tab->M[0][0] + tab->M[1][1] + tab->M[2][2];
    if (soma == tipo * 2) {
        for (i = 0; i < 3; i++) {
            if (tab->M[i][i] == VAZIO) {
                *linha = i;
                *coluna = i;
                return 1;
            }
        }
    }

    soma = tab->M[0][2] + tab->M[1][1] + tab->M[2][0];
    if (soma == tipo * 2) {
        for (i = 0; i < 3; i++) {
            if (tab->M[i][2 - i] == VAZIO) {
                *linha = i;
                *coluna = 2 - i;
                return 1;
            }
        }
    }

    return 0;
}

int contaSequencias(Tabuleiro *tab, int tipo)
{
    int total, i, soma, vazias;

    total = 0;

    for (i = 0; i < 3; i++) {
        soma = tab->M[i][0] + tab->M[i][1] + tab->M[i][2];
        vazias = (tab->M[i][0] == VAZIO) + (tab->M[i][1] == VAZIO) + (tab->M[i][2] == VAZIO);
        if (soma == tipo * 2 && vazias == 1) {
            total++;
        }
    }

    for (i = 0; i < 3; i++) {
        soma = tab->M[0][i] + tab->M[1][i] + tab->M[2][i];
        vazias = (tab->M[0][i] == VAZIO) + (tab->M[1][i] == VAZIO) + (tab->M[2][i] == VAZIO);
        if (soma == tipo * 2 && vazias == 1) {
            total++;
        }
    }

    soma = tab->M[0][0] + tab->M[1][1] + tab->M[2][2];
    vazias = (tab->M[0][0] == VAZIO) + (tab->M[1][1] == VAZIO) + (tab->M[2][2] == VAZIO);
    if (soma == tipo * 2 && vazias == 1) {
        total++;
    }

    soma = tab->M[0][2] + tab->M[1][1] + tab->M[2][0];
    vazias = (tab->M[0][2] == VAZIO) + (tab->M[1][1] == VAZIO) + (tab->M[2][0] == VAZIO);
    if (soma == tipo * 2 && vazias == 1) {
        total++;
    }

    return total;
}

int procuraDuasSequencias(Tabuleiro *tab, int tipo, int *linha, int *coluna)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tab->M[i][j] == VAZIO) {
                tab->M[i][j] = tipo;

                if (contaSequencias(tab, tipo) >= 2) {
                    tab->M[i][j] = VAZIO;
                    *linha = i;
                    *coluna = j;
                    return 1;
                }

                tab->M[i][j] = VAZIO;
            }
        }
    }

    return 0;
}

int procuraCantoOposto(Tabuleiro *tab, int adversario, int *linha, int *coluna)
{
    if (tab->M[0][0] == adversario && tab->M[2][2] == VAZIO) {
        *linha = 2;
        *coluna = 2;
        return 1;
    }

    if (tab->M[2][2] == adversario && tab->M[0][0] == VAZIO) {
        *linha = 0;
        *coluna = 0;
        return 1;
    }

    if (tab->M[0][2] == adversario && tab->M[2][0] == VAZIO) {
        *linha = 2;
        *coluna = 0;
        return 1;
    }

    if (tab->M[2][0] == adversario && tab->M[0][2] == VAZIO) {
        *linha = 0;
        *coluna = 2;
        return 1;
    }

    return 0;
}

int procuraCanto(Tabuleiro *tab, int *linha, int *coluna)
{
    if (tab->M[0][0] == VAZIO) {
        *linha = 0;
        *coluna = 0;
        return 1;
    }

    if (tab->M[0][2] == VAZIO) {
        *linha = 0;
        *coluna = 2;
        return 1;
    }

    if (tab->M[2][0] == VAZIO) {
        *linha = 2;
        *coluna = 0;
        return 1;
    }

    if (tab->M[2][2] == VAZIO) {
        *linha = 2;
        *coluna = 2;
        return 1;
    }

    return 0;
}

int procuraVazio(Tabuleiro *tab, int *linha, int *coluna)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tab->M[i][j] == VAZIO) {
                *linha = i;
                *coluna = j;
                return 1;
            }
        }
    }

    return 0;
}

void jogaIA(JogadorIA *jogador, Tabuleiro *tab)
{
    int linha, coluna, adversario;

    linha = 0;
    coluna = 0;
    adversario = tipoAdversario(jogador->tipo);

    if (procuraSequencia(tab, jogador->tipo, &linha, &coluna) == 0) {
        if (procuraSequencia(tab, adversario, &linha, &coluna) == 0) {
            if (procuraDuasSequencias(tab, jogador->tipo, &linha, &coluna) == 0) {
                if (tab->M[1][1] == VAZIO) {
                    linha = 1;
                    coluna = 1;
                } else if (procuraCantoOposto(tab, adversario, &linha, &coluna) == 0) {
                    if (procuraCanto(tab, &linha, &coluna) == 0) {
                        procuraVazio(tab, &linha, &coluna);
                    }
                }
            }
        }
    }

    marcaJogada(tab, linha, coluna, jogador->tipo);
    printf("Maquina jogou na linha %d e coluna %d.\n", linha + 1, coluna + 1);
}

void inicia(Partida *p)
{
    int resultado;
    JogadorTeclado *atual;

    resultado = VAZIO;
    atual = &p->jogador1;

    while (resultado == VAZIO) {
        desenha(&p->tab);
        joga(atual, &p->tab);
        resultado = temVencedor(&p->tab);

        if (atual == &p->jogador1) {
            atual = &p->jogador2;
        } else {
            atual = &p->jogador1;
        }
    }

    desenha(&p->tab);
    mostraResultado(resultado);
}

void iniciaJogoIA(Partida *p)
{
    int resultado;

    resultado = VAZIO;

    while (resultado == VAZIO) {
        desenha(&p->tab);
        jogaIA(&p->jogadorIA, &p->tab);
        resultado = temVencedor(&p->tab);

        if (resultado == VAZIO) {
            desenha(&p->tab);
            joga(&p->jogadorHumano, &p->tab);
            resultado = temVencedor(&p->tab);
        }
    }

    desenha(&p->tab);
    mostraResultado(resultado);
}
