// LevelTwoComputer.h

#ifndef LevelTwoComputer_h
#define LevelTwoComputer_h

#include <vector>

#include "BoardMove.h"
#include "ComputerPlayer.h"
#include "Cloneable.h"


class LevelTwoComputer final : public Cloneable<ComputerPlayer, LevelTwoComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl() const override;
public:
    explicit LevelTwoComputer(ChessBoard const &chessBoard, Team team);
    LevelTwoComputer(LevelTwoComputer const &other);
    LevelTwoComputer(LevelTwoComputer &&other) noexcept;
    // Copy and move assignment disabled
    virtual ~LevelTwoComputer() = default;
};


#endif /* LevelTwoComputer_h */
