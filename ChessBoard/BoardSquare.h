// BoardSquare.h

#ifndef BoardSquare_h
#define BoardSquare_h

#include <optional>
#include <string>


/**
 * BoardSquare Class
 * - Represents a square on a ChessBoard (2D Vector)
 * - Top left = (0, 0)
 */
struct BoardSquare final {
    int boardRow;
    int boardCol;

    explicit BoardSquare(int boardRow, int boardCol);
    BoardSquare(BoardSquare const &other);
    BoardSquare(BoardSquare &&other) noexcept;
    BoardSquare& operator=(BoardSquare const &other);
    BoardSquare& operator=(BoardSquare &&other) noexcept;
    ~BoardSquare() = default;

    bool operator==(BoardSquare const &other) const;
    bool operator!=(BoardSquare const &other) const;

    static std::optional<BoardSquare> createBoardSquare(std::string const &squareStr, int numRowsOnBoard, int numColsOnBoard);
};


#endif /* BoardSquare_h */
