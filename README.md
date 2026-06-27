# Jogo_da_Velha

Projeto da materia de Programacao Estruturada.

## Compilacao

Jogo local:

```bash
gcc main.c partida.c tabuleiro.c -o jogo
```

Jogo remoto:

```bash
gcc servidor.c partida.c tabuleiro.c remoto.c -o servidor
gcc cliente.c partida.c tabuleiro.c remoto.c -o cliente
```

## Como executar

Jogo local:

```bash
./jogo
```

Opcoes do jogo local:

1. Dois jogadores pelo teclado
2. Jogador contra maquina

No jogo contra a maquina, o jogador escolhe apenas se quer jogar com O ou X.
A maquina sempre faz a primeira jogada.

Jogo remoto:

Em um terminal:

```bash
./servidor
```

Em outro terminal:

```bash
./cliente
```

No modo remoto, o servidor joga primeiro com X e o cliente joga em seguida com O.
