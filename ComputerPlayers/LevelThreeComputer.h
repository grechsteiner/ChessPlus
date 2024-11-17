// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/**
 * LevelThreeComputer ComputerPlayer Class
 */
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
