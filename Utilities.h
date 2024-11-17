// Utilities.h

#ifndef Utilities_h
#define Utilities_h

#include <optional>
#include <string>

#include "Constants.h"


/**
 * Global Utility Methods
 */
namespace Utilities {
    std::optional<ComputerPlayerLevel> stringToComputerPlayerLevel(std::string const &str);
    std::optional<PlayerType> stringToPlayerType(std::string const &str);
    std::optional<PieceType> stringToPieceType(std::string const &str);
    std::optional<PieceLevel> stringToPieceLevel(std::string const &str);
    std::optional<PieceDirection> stringToPieceDirection(std::string const &str);
}


#endif /* Utilities_h */
