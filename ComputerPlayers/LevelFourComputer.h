// LevelFourComputer.h

#ifndef LevelFourComputer_h
#define LevelFourComputer_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "ChessBoard.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/**
 * LevelFourComputer ComputerPlayer Class
 */
class LevelFourComputer final : public Cloneable<ComputerPlayer, LevelFourComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const override;

public:
    explicit LevelFourComputer(Team team);
    LevelFourComputer(LevelFourComputer const &other);
    LevelFourComputer(LevelFourComputer &&other) noexcept;
    LevelFourComputer& operator=(LevelFourComputer &other);
    LevelFourComputer& operator=(LevelFourComputer &&other) noexcept;
    virtual ~LevelFourComputer() = default;
};


#endif /* LevelFourComputer_h */
