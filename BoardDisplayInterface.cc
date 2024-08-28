// BoardDisplayInterface.cc

#include <vector>
#include <string>

#include "BoardDisplayInterface.h"
#include "Piece.h"


int BoardDisplayInterface::getNumRows() const { return getNumRowsImpl(); }
int BoardDisplayInterface::getNumCols() const { return getNumColsImpl(); }

Piece const& BoardDisplayInterface::getPieceAt(int row, int col) const { return getPieceAtImpl(row, col); }
std::vector<std::pair<std::string, std::string>> BoardDisplayInterface::getMatchingOpenings() const { return getMatchingOpeningsImpl(); }

bool BoardDisplayInterface::isInCheck(Color color) const { return isInCheckImpl(color); }
bool BoardDisplayInterface::isInCheckMate(Color color) const { return isInCheckMateImpl(color); }
bool BoardDisplayInterface::isInStaleMate(Color color) const { return isInStaleMateImpl(color); }
