// BoardDisplayInterface.h

#ifndef BoardDisplayInterface_h
#define BoardDisplayInterface_h

#include <vector>
#include <string>

#include "Piece.h"

class Context;

class BoardDisplayInterface {

private:
    virtual int getNumRowsImpl() const = 0;
    virtual int getNumColsImpl() const = 0;

    virtual Piece const& getPieceAtImpl(int row, int col) const = 0;
    virtual std::vector<std::pair<std::string, std::string>> getMatchingOpeningsImpl() const = 0;

    virtual bool isInCheckImpl(Color color) const = 0;
    virtual bool isInCheckMateImpl(Color color) const = 0;
    virtual bool isInStaleMateImpl(Color color) const = 0;

    virtual Context& getContextImpl() = 0;

public:
    int getNumRows() const;
    int getNumCols() const;

    Piece const& getPieceAt(int row, int col) const;
    std::vector<std::pair<std::string, std::string>> getMatchingOpenings() const;

    bool isInCheck(Color color) const;
    bool isInCheckMate(Color color) const;
    bool isInStaleMate(Color color) const;

    Context& getContext() { return getContextImpl(); }

};


#endif /* BoardDisplayInterface_h */
