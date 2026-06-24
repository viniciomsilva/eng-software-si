# 👨‍🎓 Software Engineering (1st Semester)

> **University:** Estácio\
> **Student:** Vinicio Monteiro\
> **Course:** Introduction to Computer Programming

Read in: [🇧🇷 Português](./README.md)

Repository containing the project code for the **Introduction to Computer**
**Programming** course during the first semester of the **Software Engineering**
degree at **Estácio**. The projects are simple games developed in C, aiming to
assimilate basic concepts of algorithms, data manipulation, and computing
resources.

This repository exists to track my progress in algorithm construction, software
architecture, design, and best practices. In other words, it serves as a
historical record for future evaluation of my evolution.

## 📑 Project Development Order

1. 🃏 [Super Trumps](./super_trumps/);
2. ♟️ [Chess Move](./chess_move/);
3. ⚓ [Battleship](./battleship/).

Each game is in a separate directory. For each respective directory, there is a
`.bat` script for Windows or a `.sh` script for Linux/macOS containing the
compilation and execution commands for that game, sending the executable to
`../bin/`.

## 🚀 Introduction

To compile the games, simply install the **GCC** compiler from the **MinGW**
**package** on Windows. If you use Linux/macOS, GCC is installed by default.
As for a simple code editor, I recommend using **VSCode** with the C/C++
extension pack. See the links below:

* [Install VSCode](https://code.visualstudio.com/docs/getstarted/overview?os=windows#_install-vs-code);
* [Windows: Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw);
* [Linux/macOS: Using GCC with VSCode](https://code.visualstudio.com/docs/cpp/config-linux).

### Compilation and Execution

Download Option \#1: Download the ZIP file.

<div align="center">
  <img src="./assets/download_zip.png" alt="GitHub's “Download ZIP” button" width="500" />
</div> <!-- div align center -->

Download Option \#2: Clone the repository using Git.

```sh
git clone https://github.com/viniciomsilva/eng-software-si.git your_directory
```

After downloading the code to your machine, navigate to one of the project
folders and run the `compile.bat` script to automatically compile and run on
Windows, or the `compile.sh` script for Linux/macOS.

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

## 📑 About the Projects

* 🃏 [Super Trumps](#-super-trumps);
* ♟️ [Chess Move](#️-chess-move);
* ⚓ [Battleships](#-battleship);
* 🛠️ [Utils Components](#️-utils-component).

### 🃏 Super Trumps

A simple game where the player inputs the attributes of two city-themed cards.
The card with the higher attributes wins, except for the population density
attribute.

The main objective of this project is to learn primitive types, arithmetic and
relational operators, data structures, loops (repetition structures), arrays,
basic functions, and data input/output (I/O).

### ♟️ Chess Move

A game that displays a standard chess board (8x8) where the player chooses a
piece and moves it according to classical and basic chess rules.

*Note: There is no combat between players or against the machine.*

This project involves manipulating a two-dimensional array (taking care to
prevent buffer overflows), piece collision detection, and input validation,
adhering to the game's business rules. It already demonstrates a basic
separation of concerns into modules and a brief introduction to pointers.

* `chess_move.h`: centralizes the business rules;
* `chess_move_io.h`: handles the formatting of data input and output.

Another highlight of this project is the logic used to increment or decrement
piece coordinates to move them across the board. This logic is streamlined with
the help of arrays of structs containing `x` and `y` values, simulating movement
along the cardinal points.

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

Just like in a standard Cartesian plane, `x` represents the row and `y`
represents the column. However, there are notable discrepancies between the
Cartesian representation and matrix manipulation. See below:

* The `y` value increases from top to bottom;
* To access a position, `y` comes before `x`.

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

#### Interface: Chess Move

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

### ⚓ Battleship

A simple Battleship game where the player must sink ships placed hidden and
randomly by the computer.

Much of the logic for incrementing and decrementing coordinate structures within
matrices was reused, adapted, and improved from the previous game.

In this project, the computer places ships of various sizes horizontally,
vertically, or diagonally without overlap. The choice of direction and
coordinates is randomly determined at the start of execution, ensuring a dynamic
game. The ships are:

* Aircraft carrier with a width of 5 positions;
* Battleship with a width of 4 positions;
* Submarine and destroyer, both with a width of 3 positions;
* Patrol boat with a width of 2 positions.

The player has a limited arsenal of projectiles with area-of-effect (AoE)
damage, with the exception of the standard shot. The projectile damage spreads
outward from the center. The only rule for the player is that the center of a
projectile cannot be launched outside the board. If an AoE projectile is
launched too close to the edges of the board, much of its potential damage area
is lost. The arsenal consists of:

* Shot with single-target damage;
* Bomb with a plus-sign (+) shaped damage area, hitting up to 5 positions;
* Torpedo with a larger plus-sign shaped damage area on the sides, hitting up to
  7 positions;
* Sea mine with a triangle-shaped damage area, hitting up to 9 positions.

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

The player starts with an arsenal of:

* 20 gunfires;
* 3 bombs;
* 4 torpedos;
* 3 sea mines;

The board measures 10x10, totaling 100 positions; the ships occupy 17 random
positions; the projectiles, if used efficiently without wasting area, can cover
up to 90 positions. This numerical combination brings an interesting balance to
the challenge of sinking all ships with a limited arsenal.

The player wins by completely sinking all ships before the arsenal runs out.

#### Interface: Battleship

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

### 🛠️ Utils Component

A component with generic functions shared between the Chess Move and Battleship
projects that are not directly tied to the business rules.

## 🤝 Contribution

This code is under the MIT license. However, for the purpose of maintaining a
historical record and enabling subsequent analysis of my academic progress in
software engineering, any and all optimization suggestions via *Pull Requests*
will be **declined**. If you wish to study, improve, or implement new features,
you are entirely free to *fork* this repository and extend the project under
your own account.
