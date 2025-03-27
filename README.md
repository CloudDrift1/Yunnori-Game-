# Yut Nori/Yunnori (윷놀이) - Traditional Korean Board Game in C++

This repository contains an implementation of **Yut Nori (윷놀이)**, a traditional Korean board game, in C++17. The game includes both a **Basic** and **Advanced** version. The advanced version features enhanced functionality like login, save, pause, exit, loading games, and multiple players with different animal characters that have unique abilities. For more detail, check the <span style="color: green;">game_rules.pdf</span> file. 

## About Yut Nori (윷놀이)

Yut Nori (윷놀이) is a traditional Korean board game, often played during the Lunar New Year holiday. It involves a game board, sticks that are thrown to determine movement, and animal characters with special abilities.

- **Wikipedia**: [Yut Nori](https://en.wikipedia.org/wiki/Yut)

## Features

### Basic Version
- A simple implementation of the traditional Yut Nori game with standard rules.
- Players take turns throwing Yut sticks and move their pieces according to the result.

### Advanced Version
The advanced version includes the following features:

- **Login**: Players can log in to save progress and resume later.
- **Save/Load Game**: Players can save the game state and load it later.
- **Pause/Exit**: Players can pause the game or exit it at any time.
- **Multiple Players**: The game supports 2 to 4 players.
- **Animal Selection**: Each player can choose one of the following animals:
  - **Pig**: If someone else catches you, the other player’s turn ends immediately.
  - **Dog**: Even if the stick result is `geol`, you get to throw again.
  - **Sheep**: If you catch someone else, you get two chances to throw again.
  - **Cow**: You can only move along the yellow path.

### Skills for Each Animal:
- **Pig**: If another player catches you, that player must end their turn immediately.
- **Dog**: Even if the stick result is `geol` (no movement), you get to throw again.
- **Sheep**: If you catch another player, you get two chances to throw again.
- **Cow**: You are restricted to moving along the yellow path only.

## Requirements

To run the game, you will need a C++17 compliant compiler. The following tools and libraries are required:

- C++17 or later
- A C++ compiler (e.g., `g++` or `clang++`)
- Basic C++ Standard Library for file I/O and string manipulation
- Cmake
## Compilation and Execution

### To Compile:
Use the following command to compile the project:

```bash
mkdir build
cd build
cmake ..
make
```
### To Run:
After compiling, run the executable:

```bash
./yunnori
```
Sample advanced game board with 4 players and 4 pieces per player.

![image](https://github.com/user-attachments/assets/22d34d21-dcd5-4aa6-9abf-fa1c90539263)

## Game Modes:
* Basic Mode: Start a game with a simple set of rules.

* Advanced Mode: Start a game with login, save/load, and animal-specific abilities.


## Game Controls
* Throwing Yut sticks: Players take turns throwing sticks. The result of each throw determines how far they move.

* Movement: Players move along the board following the results of their throws and their animal abilities.

* Catching: If one player lands on another player's spot, the catching player's turn is modified based on their selected animal.
  
* Stacking: If a player's pieces stack, the pieces can move together

## Acknowledgments
Yut Nori (윷놀이) is a traditional Korean game that has been played for centuries. Learn more about its history and significance during Korean holidays like Lunar New Year.

Game logic and rules have been slightly modified for a more efficient implementation.
