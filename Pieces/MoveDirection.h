// MoveDirection.h

#ifndef MoveDirection_h
#define MoveDirection_h


/**
 * MoveDirection Struct
 * Represents a direction a Piece can move as part of a BoardMove
 */
struct MoveDirection final {
    int rowDirection;
    int colDirection;

    explicit MoveDirection(int rowDirection, int colDirection);
    MoveDirection(MoveDirection const &other);
    MoveDirection(MoveDirection &&other) noexcept;
    MoveDirection& operator=(MoveDirection const &other);
    MoveDirection& operator=(MoveDirection &&other) noexcept;
    ~MoveDirection() = default;

    bool operator==(MoveDirection const &other) const;
    bool operator!=(MoveDirection const &other) const;
};


#endif /* MoveDirection_h */
