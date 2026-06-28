#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "jogo.h"

int conecta(char ip[], int porta)
{
    int sock;
    struct sockaddr_in servidor;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(porta);

    if (inet_pton(AF_INET, ip, &servidor.sin_addr) <= 0) {
        perror("Endereco invalido");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        perror("Erro ao conectar");
        close(sock);
        exit(EXIT_FAILURE);
    }

    return sock;
}

int aceita(int porta)
{
    int servidor_fd, cliente_fd;
    struct sockaddr_in endereco;
    socklen_t endereco_len;

    endereco_len = sizeof(endereco);

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor_fd < 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(porta);

    if (bind(servidor_fd, (struct sockaddr *)&endereco, sizeof(endereco)) < 0) {
        perror("Erro no bind");
        close(servidor_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(servidor_fd, 1) < 0) {
        perror("Erro no listen");
        close(servidor_fd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexao na porta %d...\n", porta);

    cliente_fd = accept(servidor_fd, (struct sockaddr *)&endereco, &endereco_len);
    if (cliente_fd < 0) {
        perror("Erro no accept");
        close(servidor_fd);
        exit(EXIT_FAILURE);
    }

    close(servidor_fd);
    printf("Cliente conectado.\n");

    return cliente_fd;
}

void enviaJogada(JogadorRemoto *jogador, int linha, int coluna)
{
    int jogada[2];

    jogada[0] = linha;
    jogada[1] = coluna;

    if (send(jogador->socket, jogada, sizeof(jogada), 0) <= 0) {
        printf("Erro ao enviar jogada.\n");
        close(jogador->socket);
        exit(EXIT_FAILURE);
    }
}

void recebeJogada(JogadorRemoto *jogador, Tabuleiro *tab)
{
    int jogada[2];
    int bytes;

    bytes = recv(jogador->socket, jogada, sizeof(jogada), 0);
    if (bytes <= 0) {
        printf("Conexao encerrada.\n");
        close(jogador->socket);
        exit(EXIT_FAILURE);
    }

    marcaJogada(tab, jogada[0], jogada[1], jogador->tipo);
    printf("Jogador remoto marcou linha %d e coluna %d.\n", jogada[0] + 1, jogada[1] + 1);
}
