// PieceInfo.h

#ifndef PieceInfo_h
#define PieceInfo_h


/**
 * PieceInfo Struct
 * Represents all the data pertaining to a Piece that is not modifiable at construction time
 */
struct PieceInfo final {
    int pieceScore;
    char32_t image;

    explicit PieceInfo(int pieceScore, char32_t image);
    PieceInfo(PieceInfo const &other);
    PieceInfo(PieceInfo &&other) noexcept;
    PieceInfo& operator=(const PieceInfo& other);
    PieceInfo& operator=(PieceInfo&& other) noexcept;
    ~PieceInfo() = default;

    bool operator==(PieceInfo const &other) const;
    bool operator!=(PieceInfo const &other) const;
};


#endif /* PieceInfo_h */
