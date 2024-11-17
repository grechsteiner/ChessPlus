// LevelTwoComputer.h

#ifndef LevelTwoComputer_h
#define LevelTwoComputer_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/**
 * LevelTwoComputer ComputerPlayer Class
 */
class LevelTwoComputer final : public Cloneable<ComputerPlayer, LevelTwoComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const override;

public:
    explicit LevelTwoComputer(Team team);
    LevelTwoComputer(LevelTwoComputer const &other);
    LevelTwoComputer(LevelTwoComputer &&other) noexcept;
    LevelTwoComputer& operator=(LevelTwoComputer &other);
    LevelTwoComputer& operator=(LevelTwoComputer &&other) noexcept;
    virtual ~LevelTwoComputer() = default;
};


#endif /* LevelTwoComputer_h */
