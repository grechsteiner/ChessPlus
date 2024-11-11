// BoardSquare.h

#ifndef BoardSquare_h
#define BoardSquare_h

#include <optional>


/**
 * BoardSquare Class
 * Represents a square in a 2D vector representing a chessboard
 */
struct BoardSquare final {
    int boardRow;
    int boardCol;

    explicit BoardSquare(int boardRow, int boardCol);
    BoardSquare(BoardSquare const &other) = default;
    BoardSquare(BoardSquare &&other) noexcept = default;
    BoardSquare& operator=(BoardSquare const &other) = default;
    BoardSquare& operator=(BoardSquare &&other) noexcept = default;
    ~BoardSquare() = default;

    bool operator==(BoardSquare const &other) const;

    static std::optional<BoardSquare> createBoardSquare(std::string const &squareStr, int numRowsOnBoard, int numColsOnBoard);
};


#endif /* BoardSquare_h */
