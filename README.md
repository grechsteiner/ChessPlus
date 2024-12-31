# Chess Plus

## Photos

<img width="832" alt="Screenshot 2024-12-24 at 8 32 46 PM" src="https://github.com/user-attachments/assets/65bb3abc-e567-4a4e-a974-9df345a12193" />

<img width="832" alt="Screenshot 2024-12-24 at 8 55 14 PM" src="https://github.com/user-attachments/assets/29dce8fd-a0f4-4fc5-b7bc-ab9ccf948fc4" />

<img width="832" alt="Screenshot 2024-12-24 at 8 40 06 PM" src="https://github.com/user-attachments/assets/e64f1208-5dbb-443b-9a10-4c89d690f9fe" />

## Overview

Not just your average chess program, but something much much more... consisting of over 8,000 lines of code.

View the UML diagram [here](https://github.com/grechsteiner/chess_plus/blob/main/ChessPlusUML.pdf).

All the stanard behaviour you'd expect from a chess program, along with the following special features:
- Play on any size board you'd like - try playing on a 10 by 14 board!
- Advanced Pieces: specify `advanced` when placing a piece during setup mode to add additional moves to your favourite piece
- Set pieces to advance in any direction:
  - Pawns moving left/right
  - Castling up/down instead of left/right (when primary advancement direction of Rook & King are set to left or right)
  - etc
- Undo and redo an unlimited number of moves

## Motivation

The primary goal of this project was to experiment with using various design patterns and coding practices. As such, the most efficient way of implementing a chess engine (bitboards) was not used. Instead, a much more OOP style implementation was used. Some of the design patterns used throughout this project include:
- Polymorphic Cloning via the Curiously Recurring Template Pattern (CRTP)
- Observer Pattern
- Strategy Pattern
- Non Virtual Interface Pattern
- Template Method Pattern
- Factory Pattern
- Command Pattern
- Iterator Pattern

## Usage

This project was created with C++17, and utilizes a few standard unicode functions from the boost library for display purposes. 

There are 3 separate screens/states the program can be in, namely `Main Menu`, `Setup`, and `Active Game`. Each state has it's own set of valid commands, which are listed below:
```
Commands:
┏━━━━
┃ Main Menu
┗━┓
  ┠─> `game [PlayerOne:PlayerType] [PlayerTwo:PlayerType]`  ━━━  Starts a fresh game with the specified PlayerTypes
  ┃
  ┠─> `setup`  ━━━  Enters setup mode
┏━┛
┃ Setup
┗━┓
  ┠─> `+ [Square] [PieceType] [PieceLevel]? [PieceDirection]?`  ━━━  Places the specified piece on the board at the indicated square
  ┃
  ┠─> `- [Square]`  ━━━  Removes the piece at the indicated square
  ┃
  ┠─> `swap`  ━━━  Swaps which team will have the first move
  ┃
  ┠─> `standard [PieceLevel]?`  ━━━  Applies the standard chess setup to the board
  ┃
  ┠─> `set [rows:Num] [cols:Num]`  ━━━  Errases all pieces from the board, and set's the board dimensions to the indicated size
  ┃
  ┠─> `done`  ━━━  Exits setup mode
┏━┛
┃ Active Game
┗━┓
  ┠─> `move [fromSquare:Square] [toSquare:Square] [promotionPieceType:PieceType]`  ━━━  Makes the indicated move, if it's a computer players turn just enter `move`
  ┃
  ┠─> `undo`  ━━━  Undoes the last made move
  ┃
  ┠─> `redo`  ━━━  Redos the last undone move
  ┃
  ┠─> `resign`  ━━━  Resigns the game
  ┗━━

Key:
┏━━━━
┠─> PlayerType  ━━━  human|computer[1-5]
┃
┠─> Square  ━━━  [a-z]+[1-9][0-9]*
┃
┠─> PieceType  ━━━  [a-z] (black piece), [A-Z] (white piece)
┃
┠─> PieceLevel  ━━━  basic|advanced
┃
┠─> PieceDirection  ━━━  north|south|west|east
┃
┠─> Num  ━━━  [1-9][0-9]*
┗━━━━
```

## Architectural Summary

This project utilizes a modified MVC (Model-View-Controller) architecture, paired with an observer pattern setup. There is a single Observer Type (TextObserver) which is responsible for rendering the View, which obtains it's data from the Subject/Controller (Game), whose data source is the chess board itself (ChessBoard).

The ChessBoard itself stores various pieces, which are broken down in the following manner: The virtual base piece class, which holds all the general data that all pieces posesses. From there, there are virtual base classes for each type of piece such as King, Bishop, and Rook. These classes hold the logic for computing the standard set of legal moves associated with each of these resepective pieces. Finally, there are concrete Advanced and Basic classes for each piece type (ex: AdvancedBishop and BasicBishop). This is where the set of legal moves for different piece levels is distinguished. 

The Game class processes the general logic of a game: parsing commands, supplying moves to the ChessBoard, obtaining a move from one of the ComputerPlayer classes, etc. 

## Potential Next-Steps

Some potential steps that could be taken to further this project include:

- Providing hints (of various usefulness) to human players by utilizing the same logic used for the different ComputerPlayer levels
- Displaying all legal moves for a given piece on the board at a given time
- Incorporating a graphic display, similar to the command line appearence
- Storing standard chess openings so that players can view when they're played moves correspond to a standard opening, and/or setting ComputerPlayers to follow a standard opening as long as it's possible to do so
- Implementing the ChessBoard and Pieces using bitboards in order to improve the move generation efficiency, opening up the possibility of incorporating more complicated ComputerPlayer algorithms 
