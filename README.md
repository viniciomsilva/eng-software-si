# 👨‍🎓 Engenharia de Software (S1)

> **Universidade:** Estácio\
> **Aluno:** Vinicio Monteiro\
> **Disciplina:** Introdução à Programação de Computadores

Leia em: [🇺🇸 English](./README_EN.md)

Repositório com os códigos dos projetos da disciplina de **Introdução à**
**Programação de Computadores** do primeiro semestre da faculdade de
**Engenharia de Software**, na **Estácio**. Os projetos são jogos simples
desenvolvidos em C, visando assimilar os conceitos básicos de algoritmos e
manipulação de dados e recursos computacionais.

Este repositório existe para medir minha evolução em construção de algoritmos,
arquitetura de software, design e boas práticas. Ou seja, para servir de
histórico para avaliação futura da minha evolução.

## 📑 Ordem de Desenvolvimento dos Projetos

1. 🃏 [Super Trunfo](./super_trumps/);
2. ♟️ [Movimentação do Xadrez](./chess_move/);
3. ⚓ [Batalha Naval](./battleship/).

Cada jogo é um diretório separado. Para cada respectivo diretório, há um script
`.bat` para Windows ou `.sh` para Linux/macOS com o comando de compilação e
execução daquele jogo mandando o executável para `../bin/`.

## 🚀 Introdução

Para a compilação dos jogos, basta instalar o compilador **GCC** do **pacote**
**MinGW** no Windows. Caso use Linux/macOS, o GCC vem instalado por padrão.
E um editor de código simples, recomendo o uso do **VSCode** com o pacote de
extensões para C/C++. Vide os links:

* [Install VSCode](https://code.visualstudio.com/docs/getstarted/overview?os=windows#_install-vs-code);
* [Windows: Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw);
* [Linux/macOS: Using GCC with VSCode](https://code.visualstudio.com/docs/cpp/config-linux).

### Compilação e Execução

Opção \#1 para download: baixar o arquivo ZIP.

<div align="center">
  <img src="./assets/download_zip.png" alt="GitHub's “Download ZIP” button" width="500" />
</div> <!-- div align center -->

Opção \#2 para download: clonar o repositório com Git.

```sh
git clone https://github.com/viniciomsilva/eng-software-si.git your_directory
```

Após baixar o código para sua máquina, entre na pasta de um dos projetos e
execute o script `compile.bat` para compilar e executar automaticamente no
Windows ou o script `compile.sh` para Linux/macOS.

```sh
# Linux/macOS Bash

cd your_directory/battleship

chmod +x compile.sh

./compile.sh
```

```bat
REM Windows CMD

cd your_directory\battleship

compile.bat
```

## 📑 Sobre os Projetos

* 🃏 [Super Trunfo](#-super-trunfo);
* ♟️ [Movimentação do Xadrez](#️-movimentação-do-xadrez);
* ⚓ [Batalha Naval](#-batalha-naval);
* 🛠️ [Componente Utils](#️-componente-utils).

### 🃏 Super Trunfo

Jogo simples onde o jogador informa os atributos de duas cartas do tema cidades.
A carta com os maiores atributos ganha, exceto o atributo de densidade
populacional.

O objetivo principal desse projeto é aprender os tipos primitivos, os operadores
aritméticos e relacionais, estrutura de dados, estruturas de repetição,
vetores, funções básicas, entradas e saídas de dados.

### ♟️ Movimentação do Xadrez

Jogo que mostra um tabuleiro de xadrez padrão (8x8) onde o jogador escolhe uma
peça e a movimenta seguindo as regras clássicas e básicas do xadrez.

*Obs.: Não existe combate entre jogadores ou máquina.*

Aqui há manipulação de matriz bidimensional (cuidando contra estouro de
*buffer*), detecção de colisão entre as peças e validação de entradas,
obedecendo as regras de negócio do jogo. Já é possível  verificar a separação
básica das responsabilidades em módulos e breve conhecimento de ponteiros.

* `chess_move.h`: centraliza as regras de negócio;
* `chess_move_io.h`: cuida da formatação de entrada e saída de dados.

Outro ponto de destaque neste projeto é a lógica para incrementar ou decrementar
as coordenadas das peças para movimentá-las no tabuleiro.  Essa lógica é
facilitada com auxílio de vetores de estruturas com valores para `x` e `y`
simulando a movimentação seguindo os pontos cardeais.

```c
// chess_move.h
typedef struct Direction {
    short x;
    short y;
} Direction;

// chess_move.c
Direction DRTS[8] = {
    { .x = 0,  .y = -1 },  // N
    { .x = 0,  .y = 1  },  // S
    { .x = 1,  .y = 0  },  // E
    { .x = -1, .y = 0  },  // W
    { .x = 1,  .y = -1 },  // NE
    { .x = -1, .y = -1 },  // NW
    { .x = 1,  .y = 1  },  // SE
    { .x = -1, .y = 1  },  // SW
};
```

Assim como no plano cartesiano padrão, `x` representa linha e `y` representa
coluna. No entanto, há divergências notáveis entre a representação cartesiana e
a representação numa manipulação de matrizes. Veja:

* O valor `y` cresce de cima para baixo;
* Para acessar uma posição, `y` vem antes do `x`.

```c
int matrix[3][3] = {
  { 0, 1, 2 },
  { 3, 4, 5 },
  { 7, 8, 9 }
};

int x = 1;
int y = 2;

printf("%d", matrix[y][x]);  // -> 8
```

#### Interface: Movimentação do Xadrez

```txt
  MOVIMENTACAO DO XADREZ 

  8 -      |     | PA3 |     |     |     | QEN |     
  7 -      |     |     |     | PA5 |     |     |     
  6 -      |     |     |     |     |     |     | PA8 
  5 -      | PA2 |     |     |     |     |     |     
  4 -      |     |     |     |     |     | PA7 |     
  3 -  PA1 |     | KN1 | PA4 |     | PA6 |     | BI2 
  2 -  RK1 | BI1 |     |     | KNG |     |     | RK2 
  1 -      |     |     |     |     |     | KN2 |     
        a     b     c     d     e     f     g     h  
  ---------------------------------------------------

  [  1 ] PA1  [  2 ] PA2  [  3 ] PA3  [  4 ] PA4  
  [  5 ] PA5  [  6 ] PA6  [  7 ] PA7  [  8 ] PA8  
  [  9 ] RK1  [ 10 ] KN1  [ 11 ] BI1  [ 12 ] QEN  
  [ 13 ] KNG  [ 14 ] BI2  [ 15 ] KN2  [ 16 ] RK2  
  [ 99 ] SAIR 

  > ESCOLHA UMA PECA: 16
  > PECA ESCOLHIDA:   RK2 

  [ 0 ] NORTE  [ 1 ] SUL  [ 2 ] LESTE  [ 3 ] OESTE 

  > ESCOLHA UMA DIRECAO: 0
  > QUANTIDADE DE CASAS: 2
```

### ⚓ Batalha Naval

Jogo de Batalha Naval simples onde o jogador terá de afundar as embarcações
posicionadas oculta e aleatoriamente pelo computador.

Boa parte da lógica de incremento e decremento de estruturas de coordenadas
em matrizes foi reaproveitada, adaptada e melhorada do jogo anterior.

Neste projeto, o computador posiciona as embarcações de tamanhos diferentes na
horizontal, vertical ou diagonal e sem sobreposição. A escolha da direção e das
coordenadas é sorteada aleatoriamente ao início da execução, garantindo
dinamismo do jogo. As embarcações são:

* Porta-aviões com largura de 5 posições;
* Encouraçado com largura de 4 posições;
* Submarino e destroyer, ambos com largura de 3 posições;
* Patrulha com largura de 2 posições.

O jogador dispõe de arsenal limitado de projéteis com danos em área, com exceção
do tiro. A área dos projéteis se espalha do centro para as laterais. A única
regra para o jogador é que ele não pode lançar o centro de um projétil fora do
tabuleiro. Se ele lançar um projétil de área com o centro muito perto das bordas
do tabuleiro, ele perde boa parte do dano potencial daquele projétil. O arsenal
é composto por:

* Tiro com dano único;
* Bomba com área de dano em formato de sinal de adição, atinge até 5 posições;
* Torpedo com área de dano em formato de sinal de adição maior nas laterais,
  atinge até 7 posições;
* Mina marítima com área de dano em formato de triângulo, atinge até 9 posições.

```txt
  GUNFIRE       ~


  BOMB          ~
              ~ ~ ~
                ~


  TORPEDO       ~
            ~ ~ ~ ~ ~
                ~


  SEA MINE      ~
              ~ ~ ~
            ~ ~ ~ ~ ~
```

O jogador inicia com um arsenal de:

* 20 tiros;
* 3 bombas;
* 4 torpedos;
* 3 minas marítimas;

O tabuleiro mede 10x10, totalizando 100 posições; as embarcações ocupam 17
posições aleatórias; os projéteis, se usados sem desperdício de área, podem
atingir até 90 posições. Essa combinação numérica traz um equilíbrio
interessante para o desafio de afundar todas as embarcações com um arsenal
limitado.

O jogador ganha se afundar todas as embarcações completamente antes do arsenal
esgotar.

#### Interface: Batalha Naval

```txt
    |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |  > PLAYER 5PT
    +-----------------------------------------------------------+
  1 |  ~     ~     ~           ~     ~     A                    |
    |                                                           |
  2 |  D     ~     ~     ~     ~     ~     A     ~              |
    |                                                           |
  3 |  D     ~     ~                       A     ~     ~        |
    |                                                           |
  4 |  D     ~     ~                 ~     A     ~     ~     ~  |
    |                                                           |
  5 |  ~     B     ~                 ~     A     ~     ~     ~  |
    |                                                           |
  6 |  ~     ~     B     ~     ~     ~     ~     ~     ~        |
    |                                                           |
  7 |  ~     ~     ~     B     ~     ~           ~              |
    |                                                           |
  8 |  ~     ~     P     ~     B     ~     ~     ~     ~     ~  |  > [ 1 ] GNF (0)
    |                                                           |  > [ 2 ] BMB (0)
  9 |  ~     ~     P     ~     ~           ~     ~     ~     ~  |  > [ 3 ] TPD (0)
    |                                                           |  > [ 4 ] SMN (0)
 10 |  ~     ~     ~     S     S     S     ~     ~     ~     ~  |  > [ 0 ] SAIR
    +-----------------------------------------------------------+

    > GAME WINS: VOCE AFUNDOU TODOS AS EMBARCACOES...
    > FINALIZANDO...
      PRESSIONE QUALQUER TECLA PARA CONTINUAR...
```

### 🛠️ Componente Utils

Componente com funções genéricas compartilhadas entre os projetos da
Movimentação do Xadrez e a Batalha Naval que não estão diretamente ligadas às
regras de negócio.

## 🤝 Contribuição

Este código está sob licença MIT. No entanto, devido aos fins de manter o
histórico e análise posterior da minha evolução acadêmica na engenharia de
software, toda e qualquer sugestão de melhoria via *Pull Request* será
**recusada**. Caso queira estudar, melhorar ou implementar novas
funcionalidades, você tem total liberdade para fazer um fork deste repositório
e estender o projeto em sua conta.
