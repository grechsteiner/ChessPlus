// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <vector>

#include "BoardMove.h"
#include "ComputerPlayer.h"
#include "Cloneable.h"


class LevelThreeComputer final : public Cloneable<ComputerPlayer, LevelThreeComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl() const override;
public:
    explicit LevelThreeComputer(ChessBoard const &chessBoard, Team team);
    LevelThreeComputer(LevelThreeComputer const &other);
    LevelThreeComputer(LevelThreeComputer &&other) noexcept;
    // Copy and move assignment disabled
    virtual ~LevelThreeComputer() = default;
};


#endif /* LevelThreeComputer_h */
