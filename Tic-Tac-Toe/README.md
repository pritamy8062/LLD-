# Tic Tac Toe – Low Level Design (C++)

## Problem Statement
Design and implement a Tic Tac Toe game using Object-Oriented principles.
The game should allow two players to play turn by turn and determine:
- Win
- Draw
- Invalid moves

---

## Requirements
- 2 players
- 3×3 board (default)
- Players take turns
- Detect winner (rows, columns, diagonals)
- Detect draw
- Prevent invalid moves

---

## Class Design

### 1. Player
Represents a game player.

**Attributes**
- name
- symbol (X / O)

**Responsibilities**
- Store player details

---

### 2. Board
Represents the game board.

**Attributes**
- 2D grid
- board size

**Responsibilities**
- Place symbols
- Check win conditions
- Check if board is full
- Display board

---

### 3. Game
Controls game flow.

**Attributes**
- Board
- Player 1
- Player 2
- Current Player
- Game state

**Responsibilities**
- Manage turns
- Switch players
- Decide win/draw
- Control overall game flow

---

## Design Principles Used
- **Single Responsibility Principle**
- **Encapsulation**
- **Separation of Concerns**
- **Modular & Extendable Design**

---

## Possible Extensions
- AI Player (Minimax strategy)
- Variable board size (NxN)
- GUI-based version
- Online multiplayer support

---

## How to Run

```bash
g++ tic_tac_toe.cpp -o tic_tac_toe
./tic_tac_toe
