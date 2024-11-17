// LevelOneComputer.h

#ifndef LevelOneComputer_h
#define LevelOneComputer_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "ChessBoard.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/**
 * LevelOneComputer ComputerPlayer Class
 */
class LevelOneComputer final : public Cloneable<ComputerPlayer, LevelOneComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const override;

public:
    explicit LevelOneComputer(Team team);
    LevelOneComputer(LevelOneComputer const &other);
    LevelOneComputer(LevelOneComputer &&other) noexcept;
    LevelOneComputer& operator=(LevelOneComputer &other);
    LevelOneComputer& operator=(LevelOneComputer &&other) noexcept;
    virtual ~LevelOneComputer() = default;
};


#endif /* LevelOneComputer_h */
