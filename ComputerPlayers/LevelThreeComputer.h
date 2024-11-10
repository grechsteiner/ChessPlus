// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <vector>

#include "BoardMove.h"
#include "ComputerPlayer.h"
#include "Cloneable.h"


class LevelThreeComputer final : public Cloneable<ComputerPlayer, LevelThreeComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const override;
public:
    explicit LevelThreeComputer(Team team);
    LevelThreeComputer(LevelThreeComputer const &other);
    LevelThreeComputer(LevelThreeComputer &&other) noexcept;
    LevelThreeComputer& operator=(LevelThreeComputer &other);
    LevelThreeComputer& operator=(LevelThreeComputer &&other) noexcept;
    virtual ~LevelThreeComputer() = default;
};


#endif /* LevelThreeComputer_h */
