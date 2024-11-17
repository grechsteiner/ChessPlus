// Utilities.cc

#include "Utilities.h"

#include <algorithm>
#include <cctype>
#include <optional>
#include <string>
#include <unordered_map>

#include "Constants.h"


/*
 * Return Optional ComputerPlayerLevel
 * - value if string is associated with a ComputerPlayerLevel
 * - nullopt otherwise
 */
std::optional<ComputerPlayerLevel> Utilities::stringToComputerPlayerLevel(std::string const &str) {
    static std::unordered_map<std::string, ComputerPlayerLevel> mapping = {
        { "1", ComputerPlayerLevel::ONE },
        { "2", ComputerPlayerLevel::TWO },
        { "3", ComputerPlayerLevel::THREE },
        { "4", ComputerPlayerLevel::FOUR },
        { "5", ComputerPlayerLevel::FIVE }
    };

    return mapping.find(str) != mapping.end()
        ? std::make_optional<ComputerPlayerLevel>(mapping[str])
        : std::nullopt;
}

/*
 * Return Optional PlayerType
 * - value if string is associated with a PlayerType
 * - nullopt otherwise
 */
std::optional<PlayerType> Utilities::stringToPlayerType(std::string const &str) {
    static std::unordered_map<std::string, PlayerType> mapping = {
        { "HUMAN", PlayerType::HUMAN },
        { "COMPUTER", PlayerType::COMPUTER }
    };

    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return mapping.find(upperStr) != mapping.end()
        ? std::make_optional<PlayerType>(mapping[upperStr])
        : std::nullopt;
}

/*
 * Return Optional PieceType
 * - value if string is associated with a PieceType
 * - nullopt otherwise
 */
std::optional<PieceType> Utilities::stringToPieceType(std::string const &str) {
    static std::unordered_map<std::string, PieceType> mapping = {
        { "P", PieceType::PAWN },
        { "R", PieceType::ROOK },
        { "N", PieceType::KNIGHT },
        { "B", PieceType::BISHOP },
        { "Q", PieceType::QUEEN },
        { "K", PieceType::KING }
    };

    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return mapping.find(upperStr) != mapping.end()
        ? std::make_optional<PieceType>(mapping[upperStr])
        : std::nullopt;
}

/*
 * Return Optional PieceLevel
 * - value if string is associated with a PieceLevel
 * - nullopt otherwise
 */
std::optional<PieceLevel> Utilities::stringToPieceLevel(std::string const &str) {
    static std::unordered_map<std::string, PieceLevel> mapping = {
        { "BASIC", PieceLevel::BASIC },
        { "ADVANCED", PieceLevel::ADVANCED }
    };

    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return mapping.find(upperStr) != mapping.end()
        ? std::make_optional<PieceLevel>(mapping[upperStr])
        : std::nullopt;
}

/*
 * Return Optional PieceDirection
 * - value if string is associated with a PieceDirection
 * - nullopt otherwise
 */
std::optional<PieceDirection> Utilities::stringToPieceDirection(std::string const &str) {
    static std::unordered_map<std::string, PieceDirection> mapping = {
        { "NORTH", PieceDirection::NORTH },
        { "SOUTH", PieceDirection::SOUTH },
        { "EAST", PieceDirection::EAST },
        { "WEST", PieceDirection::WEST }
    };

    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return mapping.find(upperStr) != mapping.end()
        ? std::make_optional<PieceDirection>(mapping[upperStr])
        : std::nullopt;
}
