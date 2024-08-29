// ChessBoard.cc

#include <vector>
#include <string>

#include "ChessBoard.h"
#include "Piece.h"


int ChessBoard::getNumRows() const { return getNumRowsImpl(); }
int ChessBoard::getNumCols() const { return getNumColsImpl(); }

Piece const& ChessBoard::getPieceAt(int row, int col) const { return getPieceAtImpl(row, col); }
std::vector<std::pair<std::string, std::string>> ChessBoard::getMatchingOpenings() const { return getMatchingOpeningsImpl(); }

bool ChessBoard::isInCheck(Color color) const { return isInCheckImpl(color); }
bool ChessBoard::isInCheckMate(Color color) const { return isInCheckMateImpl(color); }
bool ChessBoard::isInStaleMate(Color color) const { return isInStaleMateImpl(color); }
