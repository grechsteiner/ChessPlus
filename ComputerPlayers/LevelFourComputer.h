// LevelFourComputer.h

#ifndef LevelFourComputer_h
#define LevelFourComputer_h

#include <vector>

#include "BoardMove.h"
#include "ComputerPlayer.h"
#include "Cloneable.h"


class LevelFourComputer final : public Cloneable<ComputerPlayer, LevelFourComputer> {
private:
    std::unique_ptr<BoardMove> generateMoveImpl() const override;
public:
    explicit LevelFourComputer(ChessBoard const &chessBoard, Team team);
    LevelFourComputer(LevelFourComputer const &other);
    LevelFourComputer(LevelFourComputer &&other) noexcept;
    // Copy and move assignment disabled
    virtual ~LevelFourComputer() = default;
};


#endif /* LevelFourComputer_h */
