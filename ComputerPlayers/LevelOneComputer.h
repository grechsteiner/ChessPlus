// LevelOneComputer.h

#ifndef LevelOneComputer_h
#define LevelOneComputer_h

#include <vector>

#include "BoardMove.h"
#include "ComputerPlayer.h"
#include "Cloneable.h"

class LevelOneComputer final : public Cloneable<ComputerPlayer, LevelOneComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl() const override;
public:
    explicit LevelOneComputer(ChessBoard const &chessBoard, Team team);
    LevelOneComputer(LevelOneComputer const &other);
    LevelOneComputer(LevelOneComputer &&other) noexcept;
    // Copy and move assignment disabled
    virtual ~LevelOneComputer() = default;
};

#endif /* LevelOneComputer_h */
