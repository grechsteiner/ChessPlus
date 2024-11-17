// ChessBoard.cc

#include "ChessBoardImpl.h"

#include <algorithm>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Cloneable.h"
#include "Constants.h"
#include "Piece.h"
#include "PieceData.h"
#include "PieceFactory.h"
#include "PieceInfo.h"


#pragma mark - Specific To ChessBoardImpl

// Basic ctor
ChessBoardImpl::ChessBoardImpl(int numRows, int numCols) : Cloneable<ChessBoard, ChessBoardImpl>() {
    grid.resize(numRows);
    for (int row = 0; row < numRows; ++row) {
        grid[row].resize(numCols);
    } 
}

// Copy ctor
ChessBoardImpl::ChessBoardImpl(ChessBoardImpl const &other) : Cloneable<ChessBoard, ChessBoardImpl>() {
    // Copy grid
    grid.resize(other.getNumRowsOnBoard());
    for (int row = 0; row < other.getNumRowsOnBoard(); ++row) {
        grid[row].resize(other.getNumColsOnBoard());
        for (int col = 0; col < other.getNumColsOnBoard(); ++col) {
            if (other.grid[row][col] != nullptr) {
                grid[row][col] = other.grid[row][col]->clone();
            }
        }
    } 
    
    // Copy completed moves
    for (std::unique_ptr<BoardMove> const &completedMove : other.completedMoves) {
        completedMoves.emplace_back(completedMove->clone());
    }

    // Copy redo moves
    for (std::unique_ptr<BoardMove> const &redoMove : other.redoMoves) {
        redoMoves.emplace_back(redoMove->clone());
    }
}

// Move ctor
ChessBoardImpl::ChessBoardImpl(ChessBoardImpl &&other) noexcept : 
    grid(std::move(other.grid)), completedMoves(std::move(other.completedMoves)), redoMoves(std::move(other.redoMoves)) { }

// Copy assignment
ChessBoardImpl& ChessBoardImpl::operator=(ChessBoardImpl const &other) {
    if (this != &other) {
        // Copy grid
        grid.resize(other.getNumRowsOnBoard());
        for (int row = 0; row < other.getNumRowsOnBoard(); ++row) {
            grid[row].resize(other.getNumColsOnBoard());
            for (int col = 0; col < other.getNumColsOnBoard(); ++col) {
                if (other.grid[row][col] != nullptr) {
                    grid[row][col] = other.grid[row][col]->clone();
                }
            }
        }
        
        // Copy completed moves
        for (std::unique_ptr<BoardMove> const &completedMove : other.completedMoves) {
            completedMoves.emplace_back(completedMove->clone());
        }

        // Copy redo moves
        for (std::unique_ptr<BoardMove> const &redoMove : other.redoMoves) {
            redoMoves.emplace_back(redoMove->clone());
        }
    }
    return *this;
}

// Move assignment
ChessBoardImpl& ChessBoardImpl::operator=(ChessBoardImpl &&other) noexcept {
    if (this != &other) {
        grid = std::move(other.grid);
        completedMoves = std::move(other.completedMoves);
        redoMoves = std::move(other.redoMoves);
    }
    return *this;
}

/*
 * Returns team opposite to team argument
 */
Team ChessBoardImpl::getOtherTeam(Team team) const { 
    return team == teamOne 
        ? teamTwo 
        : teamOne; 
}

/*
 * Generates all pseudo legal moves originating from the BoardSquare argument
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    if (isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare)) {
        std::unique_ptr<ChessBoard> tempBoard(this->clone());
        return grid[boardSquare.boardRow][boardSquare.boardCol]->getMoves(tempBoard, boardSquare, onlyAttackingMoves);
    } else {
        return std::vector<std::unique_ptr<BoardMove>>();
    }
}

/*
 * Generate all pseudo legal moves that can be made by the Team argument
 * onlyAttackingMoves: if true, do not generate any moves that are non-capturing moves (castling)
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllPseudoLegalMoves(Team team, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> boardMoves;
    for (ChessBoard::BoardSquareIterator it = this->begin(); it != this->end(); ++it) {
        std::optional<PieceData> pieceData = getPieceDataAt(*it);
        if (pieceData.has_value() && pieceData.value().team == team) {
            std::vector<std::unique_ptr<BoardMove>> pieceBoardMoves = generateAllPseudoLegalMovesAtSquare(*it, onlyAttackingMoves);
            for (std::unique_ptr<BoardMove> &pieceBoardMove : pieceBoardMoves) {
                boardMoves.emplace_back(std::move(pieceBoardMove));
            }
            pieceBoardMoves.clear();
        }
    }
    return boardMoves;
}

/*
 * Clears the recorded redo moves
 */
void ChessBoardImpl::clearRedoMoves() {
    redoMoves.clear();
}

/*
 * True if Team argument has a legal move available to make, false otherwise
 */
bool ChessBoardImpl::canMakeMove(Team team) const {
    return !generateAllLegalMoves(team).empty();
}

/*
 * True if BoardMove argument would apply check after being made, false otherwise
 */
bool ChessBoardImpl::doesMoveApplyCheck(std::unique_ptr<BoardMove> const &boardMove) const {
    Team otherTeam = getOtherTeam(getPieceDataAt(boardMove->getFromSquare()).value().team);
    ChessBoardImpl temp(*this);
    temp.makeMove(boardMove);

    return temp.isInCheck(otherTeam);
}

/*
 * True if BoardMove argument would capture a piece after being made, false otherwise 
 */
bool ChessBoardImpl::doesMoveCapturePiece(std::unique_ptr<BoardMove> const &boardMove) const {
    Team movedPieceTeam = getPieceDataAt(boardMove->getFromSquare()).value().team;
    std::optional<PieceData> attackedPieceData = getPieceDataAt(boardMove->getCaptureSquare()).value();
    
    return attackedPieceData.has_value() && attackedPieceData.value().team != movedPieceTeam;
}

/*
 * True if BoardMove argument would leave a piece on it's own team attacked after being made, false otherwise
 */
bool ChessBoardImpl::doesMoveLeavePieceAttacked(std::unique_ptr<BoardMove> const &boardMove) const {
    Team movedPieceTeam = getPieceDataAt(boardMove->getFromSquare()).value().team;
    ChessBoardImpl temp(*this);
    temp.makeMove(boardMove);

    return temp.generateCapturingMoves(getOtherTeam(movedPieceTeam)).empty();
}

/*
 * True if BoardMove argument would win the game after being made, false otherwise 
 */
bool ChessBoardImpl::doesMoveWinGame(std::unique_ptr<BoardMove> const &boardMove) const {
    Team movedPieceTeam = getPieceDataAt(boardMove->getFromSquare()).value().team;
    ChessBoardImpl temp(*this);
    temp.makeMove(boardMove);

    return temp.isInCheckMate(getOtherTeam(movedPieceTeam));
}

/*
 * True if BoardMove argument would leave it's own team in check after being made, false otherwise
 */
bool ChessBoardImpl::doesMoveLeaveTeamInCheck(std::unique_ptr<BoardMove> const &boardMove) const {
    Team movedPieceTeam = getPieceDataAt(boardMove->getFromSquare()).value().team;
    ChessBoardImpl temp(*this);
    temp.makeMove(boardMove);

    return temp.isInCheck(movedPieceTeam);
} 


#pragma mark - ChessBoard Interface Implementation

/*
 * Create PieceData Optional
 * - value if Piece exists at BoardSquare argument
 * - nullopt otherwise
 */
std::optional<PieceData> ChessBoardImpl::getPieceDataAtImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && grid[boardSquare.boardRow][boardSquare.boardCol] != nullptr
        ? std::make_optional<PieceData>(grid[boardSquare.boardRow][boardSquare.boardCol]->getPieceData())
        : std::nullopt;
}

/*
 * Create PieceInfo Optional
 * - value if Piece exists at BoardSquare argument
 * - nullopt otherwise
 */
std::optional<PieceInfo> ChessBoardImpl::getPieceInfoAtImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && grid[boardSquare.boardRow][boardSquare.boardCol] != nullptr
        ? std::make_optional<PieceInfo>(grid[boardSquare.boardRow][boardSquare.boardCol]->getPieceInfo())
        : std::nullopt;
}

/*
 * True if BoardSquare argument is a valid BoardSquare on the ChessBoard, false otherwise
 */
bool ChessBoardImpl::isSquareOnBoardImpl(BoardSquare const &boardSquare) const {
    int boardRow = boardSquare.boardRow;
    int boardCol = boardSquare.boardCol;

    return 
        boardRow >= 0 && 
        boardRow < getNumRowsOnBoard() && 
        boardCol >= 0 && 
        boardCol < getNumColsOnBoard();
}

/*
 * True if BoardSquare argument is a valid BoardSquare on the ChessBoard and there is no Piece at that location, false otherwise
 */
bool ChessBoardImpl::isSquareEmptyImpl(BoardSquare const &boardSquare) const {
    return 
        isSquareOnBoard(boardSquare) && 
        !getPieceInfoAt(boardSquare).has_value();
}

/*
 * True if BoardSquare argument is a valid BoardSquare on the ChessBoard and the Team of The Piece at that location is equal to the Team argument, false otherwise
 */
bool ChessBoardImpl::isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::optional<PieceData> pieceDataAtSquare = getPieceDataAt(boardSquare);
        if (pieceDataAtSquare.has_value() && pieceDataAtSquare.value().team == ownTeam) {
            return true;
        }
    }
    return false;
}

/*
 * True if BoardSquare argument is a valid BoardSquare on the ChessBoard and the Team of The Piece at that location is not equal to the Team argument, false otherwise
 */
bool ChessBoardImpl::isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::optional<PieceData> pieceDataAtSquare = getPieceDataAt(boardSquare);
        if (pieceDataAtSquare && pieceDataAtSquare.value().team == getOtherTeam(ownTeam)) {
            return true;
        }
    }
    return false;
}

/*
 * True if BoardSquare argument is a valid BoardSquare on the ChessBoard and that location is attacked by the Team opposite to the Team argument, false otherwise
 */
bool ChessBoardImpl::isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::vector<std::unique_ptr<BoardMove>> attackingBoardMoves = generateAllPseudoLegalMoves(getOtherTeam(ownTeam), true);
        for (std::unique_ptr<BoardMove> const& boardMove : attackingBoardMoves) {
            if (boardMove->getCaptureSquare() == boardSquare) {
                return true;
            }
        }
    }
    return false;
}

/*
 * True if Team argument is in check, false otherwise
 */
bool ChessBoardImpl::isInCheckImpl(Team team) const {
    for (ChessBoard::BoardSquareIterator it = this->cbegin(); it != this->cend(); ++it) {
        std::optional<PieceData> pieceData = getPieceDataAt(*it);
        if (pieceData.has_value() && pieceData.value().pieceType == PieceType::KING && pieceData.value().team == team) {
            if (isSquareAttacked(*it, team)) {
                return true;
            }
        }
    }
    return false;
}

/*
 * True if Team argument is in checkmate, false otherwise
 */
bool ChessBoardImpl::isInCheckMateImpl(Team team) const {
    return isInCheck(team) && !canMakeMove(team);
}

/*
 * True if Team argument is in stalemate, false otherwise
 */
bool ChessBoardImpl::isInStaleMateImpl(Team team) const {
    return !canMakeMove(team) && !isInCheck(team);
}

/*
 * Generate all legal moves originating from the BoardSquare argument
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const {
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> pseudoLegalBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, false);
    for (std::unique_ptr<BoardMove> &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(std::move(pseudoLegalBoardMove));
        }
    }
    return legalBoardMoves;
}

/*
 * Generate all legal moves that can be made by the Team argument
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllLegalMovesImpl(Team team) const { 
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> pseudoLegalBoardMoves = generateAllPseudoLegalMoves(team, false);
    for (std::unique_ptr<BoardMove> &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(std::move(pseudoLegalBoardMove));
        }
    }
    return legalBoardMoves;
}

/*
 * Generate all legal moves that apply check that can be made by the Team argument
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateCheckApplyingMovesImpl(Team team) const {
    std::vector<std::unique_ptr<BoardMove>> checkApplyingBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMoves(team);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (doesMoveApplyCheck(legalBoardMove)) {
            checkApplyingBoardMoves.emplace_back(std::move(legalBoardMove));
        }
    }
    return checkApplyingBoardMoves;
}

/*
 * Generate all legal moves that capture a Piece that can be made by the Team argument
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateCapturingMovesImpl(Team team) const { 
    std::vector<std::unique_ptr<BoardMove>> capturingBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMoves(team);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (doesMoveCapturePiece(legalBoardMove)) {
            capturingBoardMoves.emplace_back(std::move(legalBoardMove));
        }
    }
    return capturingBoardMoves;
}

/*
 * Generate all legal moves that don't leave a Piece of it's own Team in a position to be captured that can be made by the Team argument
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateCaptureAvoidingMovesImpl(Team team) const {
    std::vector<std::unique_ptr<BoardMove>> captureAvoidingBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMoves(team);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (!doesMoveLeavePieceAttacked(legalBoardMove)) {
            captureAvoidingBoardMoves.emplace_back(std::move(legalBoardMove));
        }
    }
    return captureAvoidingBoardMoves;
}

/*
 * Generate all legal moves that win the game that can be made by the Team argument
 */
std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateWinningMovesImpl(Team team) const {
    std::vector<std::unique_ptr<BoardMove>> winningBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMoves(team);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (doesMoveWinGame(legalBoardMove)) {
            winningBoardMoves.emplace_back(std::move(legalBoardMove));
        }
    }
    return winningBoardMoves;
}

/*
 * Set the Piece at the BoardSquare argument location based on the PieceData argument
 */
void ChessBoardImpl::setPositionImpl(BoardSquare const &boardSquare, PieceData const &pieceData) {
    grid[boardSquare.boardRow][boardSquare.boardCol] = PieceFactory::createPiece(pieceData);
}

/*
 * Clear the BoardSqure argument location of any Pieces
 */
void ChessBoardImpl::clearPositionImpl(BoardSquare const &boardSquare) {
    grid[boardSquare.boardRow][boardSquare.boardCol] = nullptr;
}

/*
 * Clear the entire ChessBoard of any pieces
 */
void ChessBoardImpl::clearBoardImpl() {
    for (ChessBoard::BoardSquareIterator it = this->begin(); it != this->end(); ++it) {
        clearPosition(*it);
    }
}

/*
 * Create BoardMove Optional
 * - value if arguments match a legal BoardMove with the current ChessBoard state
 * - nullopt otherwise 
 */
std::optional<std::unique_ptr<BoardMove>> ChessBoardImpl::createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { 
    if (!isSquareOnBoard(fromSquare)) {
        return std::nullopt;
    }

    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMovesAtSquare(fromSquare);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (fromSquare == legalBoardMove->getFromSquare() && 
            toSquare == legalBoardMove->getToSquare() && 
            promotionPieceType == legalBoardMove->getPromotionPieceType()) {

            return std::move(legalBoardMove);
        }
    }
    return std::nullopt;
}

/*
 * True if the BoardMove argument is a legal move with the current ChessBoard state, false otherwise
 */
bool ChessBoardImpl::isMoveLegalImpl(std::unique_ptr<BoardMove> const &boardMove) const {
    if (isSquareOnBoard(boardMove->getFromSquare())) {
        std::vector<std::unique_ptr<BoardMove>> pieceBoardMoves = generateAllLegalMovesAtSquare(boardMove->getFromSquare());
        if (std::find_if(pieceBoardMoves.begin(), pieceBoardMoves.end(), [&boardMove](std::unique_ptr<BoardMove> const& pieceBoardMove) { return *pieceBoardMove == *boardMove; }) != pieceBoardMoves.end()) {
            return true;
        }
    }
    return false;
}

/*
 * Apply the BoardMove argument to the ChessBoard
 */
void ChessBoardImpl::makeMoveImpl(std::unique_ptr<BoardMove> const &boardMove) {
    boardMove->makeBoardMove(*this);                                                // Apply the move
    completedMoves.emplace_back(boardMove->clone());                                // Track it for undoing 
    clearRedoMoves();                                                               // Clear redo moves (can't redo after making a move)
}

/*
 * Undo the last made move
 * - True if move available to be undone
 * - False otherwise (and BoardState remains unchanged)
 */
bool ChessBoardImpl::undoMoveImpl() {
    if (completedMoves.empty()) {
        return false;
    } else {
        std::unique_ptr<BoardMove> lastMove = std::move(completedMoves.back());     // Get the last made move
        completedMoves.pop_back();                                                  // Pop it off the completed moves stack
        lastMove->undoBoardMove(*this);                                             // Undo the move
        redoMoves.emplace_back(std::move(lastMove));                                // Push it to the redo moves stack
        return true;
    }
}

/*
 * Redo the last undone move
 * - True if move available to be redone
 * - False otherwise (and BoardState remains unchanged)
 */
bool ChessBoardImpl::redoMoveImpl() {
    if (redoMoves.empty()) {
        return false;
    } else {
        std::unique_ptr<BoardMove> lastUndoneMove = std::move(redoMoves.back());    // Get the last move to be undone
        redoMoves.pop_back();                                                       // Pop it off the redo moves stack
        lastUndoneMove->makeBoardMove(*this);                                       // Apply the move
        completedMoves.emplace_back(std::move(lastUndoneMove));                     // Push it to the completed moves stack
        return true;
    }
}

/* Getters */
std::vector<std::unique_ptr<BoardMove>> const& ChessBoardImpl::getCompletedMovesImpl() const { return completedMoves; }
Team ChessBoardImpl::getTeamOneImpl() const {  return teamOne; }
Team ChessBoardImpl::getTeamTwoImpl() const  { return teamTwo; }
int ChessBoardImpl::getNumRowsOnBoardImpl() const { return grid.size(); }
int ChessBoardImpl::getNumColsOnBoardImpl() const { return grid.size() >= 1 ? grid[0].size() : 0; }

/* BoardSquareIterator */
ChessBoard::BoardSquareIterator ChessBoardImpl::beginImpl() { return createBoardSquareIterator(0, 0, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::BoardSquareIterator ChessBoardImpl::beginImpl() const { return createBoardSquareIterator(0, 0, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::BoardSquareIterator ChessBoardImpl::cbeginImpl() const { return createBoardSquareIterator(0, 0, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::BoardSquareIterator ChessBoardImpl::endImpl() { return createBoardSquareIterator(getNumRowsOnBoard(), 0, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::BoardSquareIterator ChessBoardImpl::endImpl() const { return createBoardSquareIterator(getNumRowsOnBoard(), 0, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::BoardSquareIterator ChessBoardImpl::cendImpl() const { return createBoardSquareIterator(getNumRowsOnBoard(), 0, getNumRowsOnBoard(), getNumColsOnBoard()); }

/* ReverseBoardSquareIterator */
ChessBoard::ReverseBoardSquareIterator ChessBoardImpl::rbeginImpl() { return createReverseBoardSquareIterator(getNumRowsOnBoard() - 1, getNumColsOnBoard() - 1, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::ReverseBoardSquareIterator ChessBoardImpl::rbeginImpl() const { return createReverseBoardSquareIterator(getNumRowsOnBoard() - 1, getNumColsOnBoard() - 1, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::ReverseBoardSquareIterator ChessBoardImpl::crbeginImpl() const { return createReverseBoardSquareIterator(getNumRowsOnBoard() - 1, getNumColsOnBoard() - 1, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::ReverseBoardSquareIterator ChessBoardImpl::rendImpl() { return createReverseBoardSquareIterator(-1, getNumColsOnBoard() - 1, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::ReverseBoardSquareIterator ChessBoardImpl::rendImpl() const { return createReverseBoardSquareIterator(-1, getNumColsOnBoard() - 1, getNumRowsOnBoard(), getNumColsOnBoard()); }
ChessBoard::ReverseBoardSquareIterator ChessBoardImpl::crendImpl() const { return createReverseBoardSquareIterator(-1, getNumColsOnBoard() - 1, getNumRowsOnBoard(), getNumColsOnBoard()); }
