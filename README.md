# Chess Plus

## Overview

Not just your average chess program, rather something much much more...

All the stanard behaviour you'd expect from a chess program, along with the following special features:
- Play on any size board you'd like, try playing on a 10 by 14 board!
- Advanced pieces, specify `advanced` when placing a piece during setup mode to add additional moves to your favourite piece
- Set pieces to advance in any direction:
  - Pawns moving left/right
  - Castling up/down instead of left/right
  - etc
- Undo and redo unlimited moves



## Motivation

The primary goal of this project was to experiment with using various design patterns and coding practices. As such, the most efficient way of implementing a chess engine (bitboards), was not used. Instead, a much more OOP style implementation was used. Some of the design patterns used throughout this project include:
- Polymorphic Cloning via the Curiously Recurring Template Pattern (CRTP)
- Observer Pattern
- Strategy Pattern
- Non Virtual Interface Pattern
- Template Method Pattern
- Factory Pattern
- Command Pattern
- Iterator Pattern

## Usage

This project was created with C++17, and utilizes a few stanrd unicode method from the boost library. 

There are 3 separate screens/states the program can be in, namely `Main Menu`, `Setup`, and `Active Game`. Each state has it's own set of valid commands, which are listed below:
```
Commands:
┏━━━━
┃ Main Menu
┗━┓
  ┠─> `game [playerOne] [playerTwo]`  ━━━  Starts a fresh game
  ┃
  ┠─> `setup`  ━━━  Enters setup mode
┏━┛
┃ Setup
┗━┓
  ┠─> `+ [square] [pieceType] [pieceLevel]? [pieceDirection]?`  ━━━  Places the indicated piece on the board at the indicated square
  ┃
  ┠─> `- [square]`  ━━━  Removes the piece at the indicated square
  ┃
  ┠─> `swap`  ━━━  Swaps which team will have the first move
  ┃
  ┠─> `standard [pieceLevel]?`  ━━━  Applies the standard chess setup to the board
  ┃
  ┠─> `set [numRows] [numCols]`  ━━━  Errases all pieces from the board, and set's the board dimensions to the indicated size
  ┃
  ┠─> `done`  ━━━  Exits setup mode
┏━┛
┃ Active Game
┗━┓
  ┠─> `move [fromSquare] [toSquare] [promotionPieceType]`  ━━━  Makes the indicated move, if it's a computer players turn just enter `move`
  ┃
  ┠─> `undo`  ━━━  Undoes the last made move
  ┃
  ┠─> `redo`  ━━━  Redos the last undone move
  ┃
  ┠─> `resign`  ━━━  Resigns the game
  ┗━━

Key:
┏━━━━
┠─> player  ━━━  human|computer[1-5]
┃
┠─> square  ━━━  [a-z]+[1-9][0-9]*
┃
┠─> pieceType  ━━━  [a-zA-Z]
┃
┠─> pieceLevel  ━━━  basic|advanced
┃
┠─> pieceDirection  ━━━  north|south|west|east
┃
┠─> numRows/numCols  ━━━  [1-9][0-9]*
┗━━━━
```

## Architectural Summary

This project utilizes a modified model-view-controller architecture, paired with an observer pattern setup. There is a single Observer Type (TextObserver) which is responsible for redering the view, which obtains it's data from the Subject/Controller (Game), whose primary data source is the chess board itself (ChessBoard).c

## Potential Next-Steps
