// Utilities.h

#ifndef Utilities_h
#define Utilities_h

#include <optional>

#include "Constants.h"


namespace Utilities {
    std::optional<ComputerPlayerLevel> stringToComputerPlayerLevel(std::string const &str);

    std::optional<PieceType> stringToPieceType(std::string const &str);
    std::optional<PieceLevel> stringToPieceLevel(std::string const &str);
    std::optional<PieceDirection> stringToPieceDirection(std::string const &str);
}


#endif /* Utilities_h */
