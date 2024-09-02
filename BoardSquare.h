// BoardSquare.h

#ifndef BoardSquare_h
#define BoardSquare_h


/**
 * BoardSquare Class
 * Represents a square in a 2D vector representing a chessboard
 */
class BoardSquare final {

private:
    int boardRow;
    int boardCol;

public:
    explicit BoardSquare(int boardRow, int boardCol);
    BoardSquare(BoardSquare const &other) = default;
    BoardSquare(BoardSquare &&other) noexcept = default;
    BoardSquare& operator=(BoardSquare const &other) = default;
    BoardSquare& operator=(BoardSquare &&other) noexcept = default;
    ~BoardSquare() = default;

    bool operator==(BoardSquare const &other) const;

    int getBoardRow() const;
    int getBoardCol() const;
};


#endif /* BoardSquare_h */
