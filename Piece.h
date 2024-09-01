// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>

#include "Constants.h"
#include "BoardMove.h"
#include "PieceInfo.h"

class ChessBoard;

class Piece {

private:
    virtual std::vector<BoardMove> getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const = 0;
    
protected:
    Piece(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display);

    PieceInfo pieceInfo;

    // TODO:
    // Factory up for different move types
    // Maybe alter isAttackingMove
    void createAndAppendBoardMove(std::vector<BoardMove> &moves, ChessBoard const &board, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, MoveType moveType, bool isAttackingMove, std::optional<PieceType> promotionPieceType = std::nullopt) const;

public:
    virtual ~Piece() = default;
    
    std::vector<BoardMove> getMoves(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const;
    
    // Getters
    PieceInfo getPieceInfo() const;
};


#endif /* Piece_h */
