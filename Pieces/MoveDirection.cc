// MoveDirection.cc

#include "MoveDirection.h"


/*
 * Basic ctor
 */
MoveDirection::MoveDirection(int rowDirection, int colDirection) :
    rowDirection(rowDirection), colDirection(colDirection) { }

/*
 * Copy ctor
 */
MoveDirection::MoveDirection(MoveDirection const &other) :
    rowDirection(other.rowDirection), colDirection(other.colDirection) { }

/*
 * Move ctor
 */
MoveDirection::MoveDirection(MoveDirection &&other) noexcept :
    rowDirection(other.rowDirection), colDirection(other.colDirection) { }

/*
 * Copy assignment
 */
MoveDirection& MoveDirection::operator=(MoveDirection const &other) {
    if (this != &other) {
        rowDirection = other.rowDirection;
        colDirection = other.colDirection;
    }
    return *this;
}

/*
 * Move assignment
 */
MoveDirection& MoveDirection::operator=(MoveDirection &&other) noexcept {
    if (this != &other) {
        rowDirection = other.rowDirection;
        colDirection = other.colDirection;
    }
    return *this;
}

/*
 * Equality
 */
bool MoveDirection::operator==(MoveDirection const &other) const {
    return
        rowDirection == other.rowDirection &&
        colDirection == other.colDirection;
}

/*
 * Inequality
 */
bool MoveDirection::operator!=(MoveDirection const &other) const {
    return !(*this == other);
}
